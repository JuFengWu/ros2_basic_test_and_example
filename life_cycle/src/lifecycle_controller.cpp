#include<iostream>
#include <chrono>
#include <memory>
#include <string>
#include <thread>

#include "lifecycle_msgs/msg/state.hpp"
#include "lifecycle_msgs/msg/transition.hpp"
#include "lifecycle_msgs/srv/change_state.hpp"
#include "lifecycle_msgs/srv/get_state.hpp"

#include "rclcpp/rclcpp.hpp"

class LifeCycleController : public rclcpp::Node{
private:
  std::shared_ptr<rclcpp::Client<lifecycle_msgs::srv::GetState>> getState;
  std::shared_ptr<rclcpp::Client<lifecycle_msgs::srv::ChangeState>> changeState;
  const std::string getTalkerStateTopic = "life_cycyle_talker/get_state";
  const std::string changeTalkerStateTopic = "life_cycyle_talker/change_state";
  const std::string lifecycleNodeName = "life_cycyle_talker";
public:
  static const int CONFIGURE = 1;
  static const int ACTIVATE = 2;
  static const int DEACTIVATE = 3;
  static const int CLEANUP = 4;
  static const int UNCONFIGURED_SHUTDOWN = 5; 
  static const int LEAVE = 6;

  explicit LifeCycleController(const std::string & node_name): Node(node_name){
    getState = this->create_client<lifecycle_msgs::srv::GetState>(getTalkerStateTopic);
    changeState = this->create_client<lifecycle_msgs::srv::ChangeState>(changeTalkerStateTopic);
  }
  unsigned int get_state(std::chrono::seconds time_out =  std::chrono::seconds(3)){
    auto request = std::make_shared<lifecycle_msgs::srv::GetState::Request>();// modify to make unique?
    if (!getState->wait_for_service(time_out)) {
      RCLCPP_ERROR(get_logger(),"Service %s is not available.",getState->get_service_name());
      return lifecycle_msgs::msg::State::PRIMARY_STATE_UNKNOWN;
    }
    auto result = getState->async_send_request(request);

    auto status = wait_for_result(result, time_out);

    if (status != std::future_status::ready){
      RCLCPP_ERROR(get_logger(), "Failed to get current state for node %s", lifecycleNodeName);
      return lifecycle_msgs::msg::State::PRIMARY_STATE_UNKNOWN;
    }
    // We have an succesful answer. So let's print the current state.
    if (result.get()) {
      RCLCPP_INFO(get_logger(), "Node %s has current state %s.",lifecycleNodeName, result.get()->current_state.label.c_str());
      return result.get()->current_state.id;
    } else {
      RCLCPP_ERROR(get_logger(), "Failed to get current state for node %s", lifecycleNodeName);
      return lifecycle_msgs::msg::State::PRIMARY_STATE_UNKNOWN;
    }
  }
  template<typename FutureT, typename WaitTimeT> 
    std::future_status wait_for_result(FutureT & future, WaitTimeT time_to_wait){
    auto end = std::chrono::steady_clock::now() + time_to_wait;
    std::chrono::milliseconds wait_period(100);
    std::future_status status = std::future_status::timeout;
    do {
      auto now = std::chrono::steady_clock::now();
      auto time_left = end - now;
      if (time_left <= std::chrono::seconds(0)) {break;}
      status = future.wait_for((time_left < wait_period) ? time_left : wait_period);
    } while (rclcpp::ok() && status != std::future_status::ready);
    return status;
  }
  bool change_state(std::uint8_t transition, std::chrono::seconds time_out = std::chrono::seconds(3))
  {
    auto request = std::make_shared<lifecycle_msgs::srv::ChangeState::Request>();
    request->transition.id = transition;

    if (!changeState->wait_for_service(time_out)) {
      RCLCPP_ERROR(get_logger(),"Service %s is not available.",changeState->get_service_name());
      return false;
    }

    auto result = changeState->async_send_request(request);

    auto status = wait_for_result(result, time_out);

    if (status != std::future_status::ready) {
      RCLCPP_ERROR(get_logger(), "Server time out while getting current state for node %s", lifecycleNodeName);
      return false;
    }

    if (result.get()->success) {
      RCLCPP_INFO(get_logger(), "Transition %d successfully triggered.", static_cast<int>(transition));
      return true;
    } else {
      RCLCPP_WARN(get_logger(), "Failed to trigger transition %u", static_cast<unsigned int>(transition));
      return false;
    }
  }

  bool configure_state(){
    if (!this->change_state(lifecycle_msgs::msg::Transition::TRANSITION_CONFIGURE)) {
      return false;
    }
    if (!this->get_state()) {
      return false;
    }
    return true;
  }
  bool activite_state(){
    if (!rclcpp::ok()) {
      return false;
    }
    if (!this->change_state(lifecycle_msgs::msg::Transition::TRANSITION_ACTIVATE)) {
      return false;
    }
    if (!this->get_state()) {
      return false;
    }
    return true;
  }
  bool deactivite_state(){
    if (!rclcpp::ok()) {
      return false;
    }
    if (!this->change_state(lifecycle_msgs::msg::Transition::TRANSITION_DEACTIVATE)) {
      return false;
    }
    if (!this->get_state()) {
      return false;
    }
    return true;
  }
  bool clean_up_state(){
    if (!rclcpp::ok()) {
      return false;
    }
    if (!this->change_state(lifecycle_msgs::msg::Transition::TRANSITION_CLEANUP)) {
      return false;
    }
    if (!this->get_state()) {
      return false;
    }
    return true;
  }
  bool unconfigured_shutdown_state(){
    if (!rclcpp::ok()) {
      return false;
    }
    if (!this->change_state(lifecycle_msgs::msg::Transition::TRANSITION_UNCONFIGURED_SHUTDOWN))
    {
      return false;
    }
    if (!this->get_state()) {
      return false;
    }
    return true;
  }
};

void print_control_state(){
  std::cout<<"please enter the control state:"<<std::endl;
  std::cout<<"1 is CONFIGURE"<<std::endl;
  std::cout<<"2 is ACTIVATE"<<std::endl;
  std::cout<<"3 is DEACTIVATE"<<std::endl;
  std::cout<<"4 is CLEANUP"<<std::endl;
  std::cout<<"5 is UNCONFIGURED_SHUTDOWN"<<std::endl;
  std::cout<<"6 is leave the test"<<std::endl;
}

void life_cycle_control(std::shared_ptr<LifeCycleController> controller){
  int controlState;
  bool noError = true;

  rclcpp::WallRate time_between_state_changes(0.5);  // 2s
  do{
    print_control_state();
    std::cin>>controlState;
    switch (controlState)
    {
      case LifeCycleController::CONFIGURE:
        noError = controller->configure_state();
      break;
      case LifeCycleController::ACTIVATE:
        noError = controller->activite_state();
      break;
      case LifeCycleController::DEACTIVATE:
        noError = controller->deactivite_state();
      break;
      case LifeCycleController::CLEANUP:
        noError = controller->clean_up_state();
      break;
      case LifeCycleController::UNCONFIGURED_SHUTDOWN:
        noError = controller->unconfigured_shutdown_state();
      break;
      case LifeCycleController::LEAVE:
        noError = false;
      break;
      default:
        std::cout<<"please enter correct number!"<<std::endl;
        break;
    }
    time_between_state_changes.sleep();
  }while(noError);
}

int main(int argc, char ** argv){
  rclcpp::init(argc, argv);

  auto controller = std::make_shared<LifeCycleController>("controller");

  rclcpp::executors::SingleThreadedExecutor exe;
  exe.add_node(controller);

  std::shared_future<void> script = std::async(std::launch::async,std::bind(life_cycle_control, controller));
  exe.spin_until_future_complete(script);

  rclcpp::shutdown();

  return 0;
}
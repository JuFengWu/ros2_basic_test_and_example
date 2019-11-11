#include <chrono>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <utility>

#include "lifecycle_msgs/msg/transition.hpp"

#include "rclcpp/rclcpp.hpp"
#include "rclcpp/publisher.hpp"

#include "rclcpp_lifecycle/lifecycle_node.hpp"
#include "rclcpp_lifecycle/lifecycle_publisher.hpp"

#include "rcutils/logging_macros.h"

#include "my_msgs/msg/robot_status.hpp" 

class LifecycleTalker : public rclcpp_lifecycle::LifecycleNode{
private:
  std::shared_ptr<rclcpp_lifecycle::LifecyclePublisher<my_msgs::msg::RobotStatus>> pub_;
  std::shared_ptr<rclcpp::TimerBase> timer_;
  int counter = 0;
public:
  explicit LifecycleTalker(const std::string & node_name, bool intra_process_comms = false): rclcpp_lifecycle::LifecycleNode(node_name,
      rclcpp::NodeOptions().use_intra_process_comms(intra_process_comms)){}


  void publish(){
    
    auto message = std::make_unique<my_msgs::msg::RobotStatus>();
    message->current_joint_position.clear();
    message->current_joint_velocity.clear();
    message->current_joint_force.clear();

    message->current_joint_position.push_back(2.5);
    message->current_joint_position.push_back(counter+2);
    message->current_joint_velocity.push_back(5.3);
    message->current_joint_velocity.push_back(counter+4);
    message->current_joint_force.push_back(3.7);
    message->current_joint_force.push_back(counter);
    

    if (!pub_->is_activated()) {
      RCLCPP_INFO(get_logger(), "Lifecycle publisher is currently inactive. Messages are not published.");
    } else {
      RCLCPP_INFO(get_logger(), "Lifecycle publisher is active");
    }
    // Only if the publisher is in an active state, the message transfer is enabled and the message actually published.
    counter++;
    pub_->publish(std::move(message));
  }

  rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn on_configure(const rclcpp_lifecycle::State &){
    pub_ = this->create_publisher<my_msgs::msg::RobotStatus>("lifecycle_chatter", 10);
    timer_ = this->create_wall_timer(std::chrono::seconds(1), std::bind(&LifecycleTalker::publish, this));

    RCLCPP_INFO(get_logger(), "on_configure() is called.");
    return rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn::SUCCESS;
  }

  rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn on_activate(const rclcpp_lifecycle::State &){
    pub_->on_activate();

    RCUTILS_LOG_INFO_NAMED(get_name(), "on_activate() is called.");

    // Let's sleep for 2 seconds.
    // We emulate we are doing important work in the activating phase.
    std::this_thread::sleep_for(std::chrono::seconds(2));

    return rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn::SUCCESS;
  }

  rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn on_deactivate(const rclcpp_lifecycle::State &){

    pub_->on_deactivate();

    RCUTILS_LOG_INFO_NAMED(get_name(), "on_deactivate() is called.");

    return rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn::SUCCESS;
  }
  rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn on_cleanup(const rclcpp_lifecycle::State &)
  {
    timer_.reset();
    pub_.reset();
    counter = 0;

    RCUTILS_LOG_INFO_NAMED(get_name(), "on cleanup is called.");

    return rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn::SUCCESS;
  }
  rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn on_shutdown(const rclcpp_lifecycle::State & state)
  {
    // In our cleanup phase, we release the shared pointers to the
    // timer and publisher. These entities are no longer available
    // and our node is "clean".
    timer_.reset();
    pub_.reset();

    RCUTILS_LOG_INFO_NAMED(get_name(),"on shutdown is called from state %s.",state.label().c_str());

    return rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn::SUCCESS;
  }
  rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn on_error(const rclcpp_lifecycle::State & state){

      RCUTILS_LOG_INFO_NAMED(get_name(),"on error is called from state %s.",state.label().c_str());

      return rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn::FAILURE;
  }
};

int main(int argc, char * argv[])
{
  // force flush of the stdout buffer.
  // this ensures a correct sync of all prints
  // even when executed simultaneously within the launch file.
  setvbuf(stdout, NULL, _IONBF, BUFSIZ);

  rclcpp::init(argc, argv);

  rclcpp::executors::SingleThreadedExecutor exe;

  std::shared_ptr<LifecycleTalker> lc_node =
    std::make_shared<LifecycleTalker>("life_cycyle_talker");

  exe.add_node(lc_node->get_node_base_interface());

  exe.spin();

  rclcpp::shutdown();

  return 0;
}
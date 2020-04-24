#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;

class Talker : public rclcpp::Node{
 private:
  void timer_callback(){
    auto message = std_msgs::msg::String();
    message.data = "the argument is " + std::to_string(counter++);
    std::cout<<" sent from talker "<< talkerName <<std::endl;
    publisher->publish(message);
  }
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher;
  unsigned int counter;
  std::string talkerName;
public:
  Talker(std::string talkerName)
  : Node("talker"), counter(0),talkerName(talkerName){
    publisher = this->create_publisher<std_msgs::msg::String>("topic", 10);
    timer_ = this->create_wall_timer(
    500ms, std::bind(&Talker::timer_callback, this));
  }
};

int main(int argc, char * argv[]){
  rclcpp::init(argc, argv);
  int i;

  for (i = 0; i<argc; i++){
    std::cout<<argv[i]<<std::endl;
  }
  
  rclcpp::spin(std::make_shared<Talker>(argv[1]));
  rclcpp::shutdown();
  return 0;
}
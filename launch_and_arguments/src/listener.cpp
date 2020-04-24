#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
using std::placeholders::_1;

class Listener : public rclcpp::Node{
 private:
  void topic_callback(const std_msgs::msg::String::SharedPtr msg) const{
    std::cout << "I heard:" << msg->data << std::endl;
  }
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription;

 public:
  Listener()
  : Node("minimal_subscriber"){
    subscription = this->create_subscription<std_msgs::msg::String>(
    "topic", 10, std::bind(&Listener::topic_callback, this, _1));
  }
};

int main(int argc, char * argv[]){
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Listener>());
  rclcpp::shutdown();
  return 0;
}
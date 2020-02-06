#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

#include <memory>
#include <thread> 
#include <iostream>

class PubSubToQt{
 private:
 bool isListen;
 rclcpp::Node::SharedPtr node;
 std::shared_ptr< rclcpp::Publisher <std_msgs::msg::String> > publisher;

 void listen_thread(rclcpp::Node::SharedPtr node);
 public:
  PubSubToQt();
  void pub(std_msgs::msg::String msg);
};

void PubSubToQt::listen_thread(rclcpp::Node::SharedPtr node){

  auto listen_from_qt = node->create_subscription<std_msgs::msg::String>(
		"from_qt",
		10,
		[&](const std_msgs::msg::String::SharedPtr msg) ->void {
		  std::cout<<"listen qt message which is: "<<msg->data<<std::endl;
		}
	);
  
/*
  rclcpp::WallRate loopRate(std::chrono::milliseconds(1));

  while(isListen)
  {
    rclcpp::spin_some(node);
    loopRate.sleep();
  }
*/
  rclcpp::spin(node);
  rclcpp::shutdown();

	  
  std::cout<<"end listen thread"<<std::endl;
  return ;
}

PubSubToQt::PubSubToQt(){
  isListen = true;
  node = rclcpp::Node::make_shared("qt_ros_pub_sub");
  publisher = node->create_publisher<std_msgs::msg::String>("to_qt", rclcpp::QoS(10));
  std::thread(&PubSubToQt::listen_thread, this,node).detach();
  
}

void PubSubToQt::pub(std_msgs::msg::String msg){
  publisher->publish(msg);
}

int main(int argc, char** argv){
  rclcpp::init(argc, argv);
  std::unique_ptr<PubSubToQt> pubSubToQt = std::make_unique<PubSubToQt>();

  rclcpp::WallRate loopRate(std::chrono::milliseconds(5000));//5 s

  while(rclcpp::ok())
  {
    std_msgs::msg::String msg;
    msg.data = "send to qt!";
    pubSubToQt->pub(msg);
    std::cout<<"sent!"<<std::endl;
    loopRate.sleep();
  }
}
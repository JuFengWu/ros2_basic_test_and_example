#include <iostream>
#include "rclcpp/rclcpp.hpp"
#include "my_msgs/msg/robot_status.hpp" 
#include <chrono>

using namespace std::chrono_literals;

int main(int argc, char **argv)
{
	rclcpp::init(argc, argv);
	auto node = rclcpp::Node::make_shared("test_msg_pub");
	auto publisher = node->create_publisher<my_msgs::msg::RobotStatus>("my_msg_test",rclcpp::QoS(10));
	auto message = std::make_shared<my_msgs::msg::RobotStatus>();
	
	rclcpp::WallRate loop_rate(1s);
	int counter=0;
	while(rclcpp::ok()){
    message->current_joint_position.clear();
    message->current_joint_velocity.clear();
    message->current_joint_force.clear();

    message->current_joint_position.push_back(2.5);
    message->current_joint_position.push_back(counter+2);
    message->current_joint_velocity.push_back(5.3);
    message->current_joint_velocity.push_back(counter+4);
    message->current_joint_force.push_back(3.7);
    message->current_joint_force.push_back(counter+6);
    counter++;
    RCLCPP_INFO(node->get_logger(),"Pub something");
    publisher->publish(*message);
    loop_rate.sleep();
  }
  rclcpp::shutdown();
  return 0;
}
#include <rclcpp/rclcpp.hpp>
#include "my_msgs/msg/robot_status.hpp" 

int main(int argc, char** argv){
	rclcpp::init(argc, argv);
	
	auto node = rclcpp::Node::make_shared("test_msg_sub");

	auto subscription = node->create_subscription<my_msgs::msg::RobotStatus>(
		"my_msg_test",
		10,
		[&](const my_msgs::msg::RobotStatus::SharedPtr robotStatus) ->void {
		  std::cout<<"current_joint_position is ";
          for(unsigned int i=0;i<robotStatus->current_joint_position.size();i++){
            std::cout<<","<<robotStatus->current_joint_position[i];
          }
		  std::cout<<std::endl;
		  std::cout<<"current_joint_velocity is ";
          for(unsigned int i=0;i<robotStatus->current_joint_velocity.size();i++){
            std::cout<<","<<robotStatus->current_joint_velocity[i];
          }
		  std::cout<<std::endl;
		  std::cout<<"current_joint_force is ";
          for(unsigned int i=0;i<robotStatus->current_joint_force.size();i++){
            std::cout<<","<<robotStatus->current_joint_force[i];
          }
		  std::cout<<std::endl;
		}
	);
	
	rclcpp::spin(node);
	rclcpp::shutdown();

	return 0;
}
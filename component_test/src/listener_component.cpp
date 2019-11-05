#include "listener_component.hpp"

#include <iostream>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "my_msgs/msg/robot_status.hpp" 

#include "rclcpp_components/register_node_macro.hpp"

namespace composition
{

  Listener::Listener(const rclcpp::NodeOptions & options)
  : Node("listener", options)
  {
    
    auto callback =
      [this](const typename my_msgs::msg::RobotStatus::SharedPtr robotStatus) -> void
      {
        std::string positionStr;
        positionStr.append("current_joint_position is ");
        
        for(unsigned int i=0;i<robotStatus->current_joint_position.size();i++){
          positionStr.append(std::to_string(robotStatus->current_joint_position[i]));
          positionStr.append(",");
        }
        RCLCPP_INFO(this->get_logger(), positionStr);

        std::string velocityStr;
        velocityStr.append("current_joint_velocity is ");
        
        for(unsigned int i=0;i<robotStatus->current_joint_velocity.size();i++){
          velocityStr.append(std::to_string(robotStatus->current_joint_velocity[i]));
          velocityStr.append(",");
        }
        RCLCPP_INFO(this->get_logger(),velocityStr);
        
        std::string forceStr;
        forceStr.append("current_joint_force is ");
        for(unsigned int i=0;i<robotStatus->current_joint_force.size();i++){
          forceStr.append(std::to_string(robotStatus->current_joint_force[i]));
          forceStr.append(",");
        }
        RCLCPP_INFO(this->get_logger(),forceStr);
        //std::flush(std::cout); it seems doesn't need this?
      };

    sub_ = create_subscription<my_msgs::msg::RobotStatus>("my_compose_test", 10, callback);
  }

}

// Register the component with class_loader.
// This acts as a sort of entry point, allowing the component to be discoverable when its library is being loaded into a running process.
RCLCPP_COMPONENTS_REGISTER_NODE(composition::Listener)

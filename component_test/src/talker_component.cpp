
#include "talker_component.hpp"

#include <chrono>
#include <iostream>
#include <memory>
#include <utility>

#include "rclcpp/rclcpp.hpp"
#include "my_msgs/msg/robot_status.hpp" 


#include "rclcpp_components/register_node_macro.hpp"

using namespace std::chrono_literals;

namespace composition
{

  // Components get built into shared libraries and as such do not write their own main functions.
  Talker::Talker(const rclcpp::NodeOptions & options)
  : Node("talker", options), counter(0)
  {
    publisher = create_publisher<my_msgs::msg::RobotStatus>("my_compose_test", 10);

    timer = create_wall_timer(1s, std::bind(&Talker::on_timer, this));
  }

  void Talker::on_timer()
  {
    auto message = std::make_unique<my_msgs::msg::RobotStatus>();
    message->current_joint_position.clear();
    message->current_joint_velocity.clear();
    message->current_joint_force.clear();

    message->current_joint_position.push_back(2.5);
    message->current_joint_position.push_back(counter+2);
    message->current_joint_velocity.push_back(5.3);
    message->current_joint_velocity.push_back(counter+4);
    message->current_joint_force.push_back(3.7);
    message->current_joint_force.push_back(counter+6);
    //std::flush(std::cout); //it seems doesn;t need this

    publisher->publish(std::move(message));
    counter++;
  }

}  // namespace composition


// Register the component with class_loader.
// This acts as a sort of entry point, allowing the component to be discoverable when its library is being loaded into a running process.
RCLCPP_COMPONENTS_REGISTER_NODE(composition::Talker)

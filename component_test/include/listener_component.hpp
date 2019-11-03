
#ifndef COMPOSITION__LISTENER_COMPONENT_HPP_
#define COMPOSITION__LISTENER_COMPONENT_HPP_

#include "visibility_control.h"
#include "rclcpp/rclcpp.hpp"
#include "my_msgs/msg/robot_status.hpp"

namespace composition
{

class Listener : public rclcpp::Node
{
public:
  COMPOSITION_PUBLIC
  explicit Listener(const rclcpp::NodeOptions & options);

private:
  rclcpp::Subscription<my_msgs::msg::RobotStatus>::SharedPtr sub_;
};

}  // namespace composition

#endif  // COMPOSITION__LISTENER_COMPONENT_HPP_

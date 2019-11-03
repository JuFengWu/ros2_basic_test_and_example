
#ifndef COMPOSITION__TALKER_COMPONENT_HPP_
#define COMPOSITION__TALKER_COMPONENT_HPP_

#include "visibility_control.h"
#include "rclcpp/rclcpp.hpp"
#include "my_msgs/msg/robot_status.hpp"

namespace composition
{

class Talker : public rclcpp::Node
{
public:
  COMPOSITION_PUBLIC
  explicit Talker(const rclcpp::NodeOptions & options);

protected:
  void on_timer();

private:
  size_t counter;
  rclcpp::Publisher<my_msgs::msg::RobotStatus>::SharedPtr publisher;
  rclcpp::TimerBase::SharedPtr timer;
};

}  // namespace composition

#endif  // COMPOSITION__TALKER_COMPONENT_HPP_

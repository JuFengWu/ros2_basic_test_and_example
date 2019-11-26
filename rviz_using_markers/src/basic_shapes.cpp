#include <rclcpp/rclcpp.hpp>
#include "visualization_msgs/msg/marker.hpp"
#include <chrono>

using namespace std::chrono_literals;

int main(int argc, char * argv[]){

  rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared("basic_shapes");
  auto publisher = node->create_publisher<visualization_msgs::msg::Marker>("visualization_marke",rclcpp::QoS(10));
  

  uint32_t shape = visualization_msgs::msg::Marker::CUBE;

  rclcpp::WallRate loopRate(1s);

  while(rclcpp::ok()){
    auto marker = std::make_shared<visualization_msgs::msg::Marker>();
    marker->header.frame_id = "/test_frame";
    //marker->header.stamp = rclcpp::Clock::now();

    marker->ns = "basic_shapes";
    marker->id = 0;
    marker->type = shape;
    marker->action = visualization_msgs::msg::Marker::ADD;

    marker->pose.position.x = 0;
    marker->pose.position.y = 0;
    marker->pose.position.z = 0;
    marker->pose.orientation.x = 0.0;
    marker->pose.orientation.y = 0.0;
    marker->pose.orientation.z = 0.0;
    marker->pose.orientation.w = 1.0;

    marker->scale.x = 1.0;
    marker->scale.y = 1.0;
    marker->scale.z = 1.0;

    marker->color.r = 0.0f;
    marker->color.g = 1.0f;
    marker->color.b = 0.0f;
    marker->color.a = 1.0;

    // Publish the marker
    while (publisher->get_subscription_count() < 1)
    {
      if (!rclcpp::ok())
      {
        return 0;
      }
      std::cout<<"Please create a subscriber to the marker"<<std::endl;
      loopRate.sleep();
    }
    publisher->publish(*marker);

    switch (shape)
    {
    case visualization_msgs::msg::Marker::CUBE:
      shape = visualization_msgs::msg::Marker::SPHERE;
      break;
    case visualization_msgs::msg::Marker::SPHERE:
      shape = visualization_msgs::msg::Marker::ARROW;
      break;
    case visualization_msgs::msg::Marker::ARROW:
      shape = visualization_msgs::msg::Marker::CYLINDER;
      break;
    case visualization_msgs::msg::Marker::CYLINDER:
      shape = visualization_msgs::msg::Marker::CUBE;
      break;
    }
    loopRate.sleep();
  }
  
}
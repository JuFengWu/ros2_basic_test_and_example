#include <rclcpp/rclcpp.hpp>
#include <chrono>
#include "my_msgs/srv/test_subtract.hpp"

int main(int argc, char * argv[]){
  using namespace std::chrono_literals;
  rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared("sub_client");
  auto client = node->create_client<my_msgs::srv::TestSubtract>("sub_srv");

  while(!client->wait_for_service(1s)){
    if(!rclcpp::ok()){
      RCLCPP_ERROR(node->get_logger(), "Client interrupted while waiting for service to appear.");
      return 1;
    }
    RCLCPP_INFO(node->get_logger(), "waiting for service...");
  }

  auto request = std::make_shared<my_msgs::srv::TestSubtract::Request>();
  request->a = 7;
  request->b = 24;

  auto res_future = client->async_send_request(request);
  if(rclcpp::spin_until_future_complete(node, res_future) != rclcpp::executor::FutureReturnCode::SUCCESS){
    RCLCPP_ERROR(node->get_logger(), "Service call failed.");
    return 1;
  }

  auto res = res_future.get();
  RCLCPP_INFO(node->get_logger(), "res: %lf", res->result);

  rclcpp::shutdown();
  return 0;
}

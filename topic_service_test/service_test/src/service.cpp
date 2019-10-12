#include <rclcpp/rclcpp.hpp>
#include "my_msgs/srv/test_subtract.hpp"

rclcpp::Node::SharedPtr node = nullptr;

void handleService(
  const std::shared_ptr<rmw_request_id_t> request_header,
  const std::shared_ptr<my_msgs::srv::TestSubtract::Request> request,
  const std::shared_ptr<my_msgs::srv::TestSubtract::Response> response
){
  (void)request_header;
  rclcpp::Rate loop_rate(1);
  loop_rate.sleep();
  RCLCPP_INFO(node->get_logger(),"srv.request:%lf,%lf", request->a, request->b);
  response->result = request->a - request->b;
}

int main(int argc, char * argv[]){


  rclcpp::init(argc, argv);
  node = rclcpp::Node::make_shared("sub_service");
  auto service = node->create_service<my_msgs::srv::TestSubtract>(
    "sub_srv",
    std::bind(handleService, std::placeholders::_1,std::placeholders::_2,std::placeholders::_3)
  );
  rclcpp::spin(node);
  rclcpp::shutdown();
  node = nullptr;
  return 0;
}

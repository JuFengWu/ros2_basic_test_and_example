#include <cstdio>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "opencv2/highgui/highgui.hpp"

#include "rclcpp/rclcpp.hpp"
#include "rclcpp_components/register_node_macro.hpp"
#include "sensor_msgs/msg/image.hpp"
#include "std_msgs/msg/bool.hpp"

#include <unistd.h>
#include <stdio.h>
#include <limits.h>



using namespace std::chrono_literals;
std::string mat_type2encoding(int mat_type)
  {
    switch (mat_type) {
      case CV_8UC1:
        return "mono8";
      case CV_8UC3:
        return "bgr8";
      case CV_16SC1:
        return "mono16";
      case CV_8UC4:
        return "rgba8";
      default:
        throw std::runtime_error("Unsupported encoding type");
    }
  }

void convert_frame_to_message(const cv::Mat & frame, size_t frame_id, sensor_msgs::msg::Image & msg)
  {
    // copy cv information into ros message
    msg.height = frame.rows;
    msg.width = frame.cols;
    msg.encoding = mat_type2encoding(frame.type());
    msg.step = static_cast<sensor_msgs::msg::Image::_step_type>(frame.step);
    size_t size = frame.step * frame.rows;
    msg.data.resize(size);
    memcpy(&msg.data[0], frame.data, size);
    msg.header.frame_id = std::to_string(frame_id);
  }

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared("test_image_pub");

  auto image1 = cv::imread("test.jpg", CV_LOAD_IMAGE_COLOR);
  std::cout<<"a"<<std::endl;
  cv::Mat image_fliped;
  cv::flip(image1, image_fliped, -1);  
  std::cout<<"b"<<std::endl;

  auto publisher = node->create_publisher<sensor_msgs::msg::Image>("my_image_test",rclcpp::QoS(10));
  std::cout<<"c"<<std::endl;
  auto message = std::make_shared<sensor_msgs::msg::Image>();
  std::cout<<"d"<<std::endl;
	
  rclcpp::WallRate loop_rate(1s);
  int counter=0;


  char cwd[1024];
  if (getcwd(cwd, sizeof(cwd)) != NULL) {
       printf("Current working dir: %s\n", cwd);
   }


  while(rclcpp::ok()){
    if(counter%2==0){
      convert_frame_to_message(image1, counter, *message);
      //cv::imshow("showimage",image1 );
    }
    else{
      convert_frame_to_message(image_fliped, counter, *message);
      //cv::imshow("showimage",image_fliped );
    }
    counter++;
    publisher->publish(*message);
    cv::waitKey(1);
    std::cout<<"counter is "<<counter<<std::endl;
    
    loop_rate.sleep();
  }
  rclcpp::shutdown();
  return 0;
}

#include<string>
#include "sensor_msgs/msg/joint_state.hpp"
#include "geometry_msgs/msg/pose.hpp"
#include "trajectory_msgs/msg/joint_trajectory.hpp"
#include "rclcpp/rclcpp.hpp"

using namespace std::chrono_literals;
class TestBridgeSendAndGet{
private:
  void listen_thread(rclcpp::Node::SharedPtr node){
    
    auto callBackCurrentPosition =[this](const trajectory_msgs::msg::JointTrajectory::SharedPtr msg) -> void{
        std::cout<<"Hear trajectory"<<std::endl;

        std::cout<<"trajectory.points size is"<<msg->points.size()<<std::endl; // error is there
        for(unsigned int i=0; i<msg->points[0].positions.size();i++){          // TODO: chnage hear way because sorted before
          std::cout<<"hope no error"<<std::endl;
          for(unsigned int j=0;i<msg->points.size();j++){
            std::cout<<"J"<<j<<":"<<msg->points[j].positions[i]<<",";
          }
        std::cout<<std::endl;
        }

    };

    auto callBackJointTrajector =[this](const geometry_msgs::msg::Pose::SharedPtr msg) -> void{
        std::cout<<"current position is hear!!"<<std::endl;
        std::cout<<"pose is x:"<< msg->position.x<<",y:"<< msg->position.y<<",z:"<<msg->position.z;
    };
    auto currentPositionSub = node->create_subscription<geometry_msgs::msg::Pose>("bridge_pose_to_ros2",10,callBackCurrentPosition);
        
    auto jointTrajectorySub = node->create_subscription<trajectory_msgs::msg::JointTrajectory>("bridge_trajectory_to_ros2", 10,callBackJointTrajector);

    rclcpp::spin(node);
    
    rclcpp::shutdown();
  }
  void talker_thread(rclcpp::Node::SharedPtr node){
    auto jointStatePublisher = node->create_publisher<sensor_msgs::msg::JointState>("bridge_jointState_to_ros1",rclcpp::QoS(10));
    auto cartesianPublisher = node->create_publisher<geometry_msgs::msg::Pose>("bridge_pose_to_ros1", rclcpp::QoS(10));
    rclcpp::WallRate loop_rate(2s);
	int counter=0;
    std::vector<double> jointTarget{0.0,0.0,0.0,0.0,0.0,0.0};
    
    sensor_msgs::msg::JointState jointStateMsg;

	while(rclcpp::ok()){
    for(int i=0;i<6;i++){
        jointTarget[i]=(double)counter;
    }    
    jointStateMsg.position = jointTarget;

    geometry_msgs::msg::Pose cmdPosition;
    cmdPosition.position.x +=0.5;
    cmdPosition.position.y +=0.5;
    cmdPosition.position.z +=0.5;

    counter++;
    if(counter==360){
        counter =0;
    }
    RCLCPP_INFO(node->get_logger(),"Pub something");
    jointStatePublisher->publish(jointStateMsg);
    cartesianPublisher->publish(cmdPosition);
    loop_rate.sleep();
  }
  }
public:
  TestBridgeSendAndGet(rclcpp::Node::SharedPtr node){
    std::thread(&TestBridgeSendAndGet::listen_thread, this,node).detach();
    std::thread(&TestBridgeSendAndGet::talker_thread, this,node).detach();
  }
};

int main(int argc, char **argv){
  rclcpp::init(argc, argv);
  
  auto node = rclcpp::Node::make_shared("test_msg_sub");
  std::unique_ptr<TestBridgeSendAndGet> testBridgeSendAndGet = std::make_unique<TestBridgeSendAndGet>(node);  

  rclcpp::spin(node);
    
}
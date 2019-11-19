# Ros2 basic test and example
This is a basic example and test for ros2

#### Preparing
1. Create a folder. If default path as ``~/jufengwu_ros2_test``, type ``mkdir ~/jufengwu_ros2_test/src``
2. Go to that folder. Type ``cd . ~/jufengwu_ros2_test/src`` 
3. Download this code. Type ``git clone https://github.com/JuFengWu/ros2_basic_test_and_example.git``
5. Make sure you have install Ros2 before. If yuo don't install before, please install by follow this [tutorial](https://index.ros.org/doc/ros2/Installation/). Currently, this example is for Ros2 Dashing versoin.
6. Type ``source /opt/ros/dashing/setup.bash ``.
7. Type ``colocn build``.

#### Run action
1. Type ``ros2 run action_cpp action_member_functions_server`` to create a action server.
2. Type ``ros2 run action_cpp not_composable_client`` to create a action client.
3. Yuo will see the action demon.

#### Run topic test
1. Open the first terminal and type ``ros2 run topic_test topic_sub_node``
2. Open the other terminal and typ ``ros2 run topic_test topic_pub_node``
3. You can see one terminal send message and the other listen message.

#### Run service test
1. Open the first terminal and type ``ros2 run service_test client_topic_node``
2. Open the other terminal and typ ``ros2 run service_test service_topic_node``
3. You can see one terminal send service and the other listen it and send result back.

#### Run image test
1. Go to source code folder. The default is ``cd ~/jufengwu_ros2_test/src/ros2_basic_test_and_example``.
2. Type ``ros2 run image_test pub_img ``
3. Open the other terminal and type ``ros2 run image_test sub_img``
4. You can see one terminal send image information and the other listen it and show the image

#### Run topic test in python 
1. Open the first terminal and type ``ros2 run topic_py listener``
2. Open the other terminal and type ``ros2 run topic_py talker``
3. You can see one terminal send message and the other listen message by python.

#### Run component
1. Open the first terminal and type ``ros2 run rclcpp_components component_container``
2. Open the second termianl and type ``ros2 component load /ComponentManager component_test composition::Talker``, the talker will start to work.
3. Using the second terminal again and type ``ros2 component load /ComponentManager component_test composition::Listener``, the listener will listen what the talker says.

#### Run life-cycle test
1. Open the first terminal and type ``ros2 run lifecycle lifecycle_listener`` 
2. Open the second terminal and type ``ros2 run lifecycle lifecycle_talker``
3. Open the third terminal and type ``ros2 run lifelifecycle_controller``
4. In the third terminal, you can choose which node state do you want to move.<br/>
:warning: Before choose the node state, please read the ros2 node life cycle design on [this page](http://design.ros2.org/articles/node_lifecycle.html). If you switch the node state without follow the rules, it will show up some errors or warnings.

#### Run the ros1 ros2 bridge test
:warning: Warning!!

1. This test will use ros1, please make sure you have insatll ros1 in your computer.
2. This test is not only use this project, but also use [this package](https://github.com/JuFengWu/tm_robot_ros2_ros1_bridge). Please follow the instruction to install the package. 
---
The steps are:
1. Build this project.
2. Open terminal and type ``ros2 run bridge_test test_send``
3. Open a new terminal to create ros2 ros1_bridge by typing those cmds
```
. /opt/ros/melodic/setup.bash
. /opt/ros/dashing/setup.bash
export ROS_MASTER_URI=http://localhost:11311
ros2 run ros1_bridge dynamic_bridge __log_disable_rosout:=true
```
4. Download [this project](https://github.com/JuFengWu/tm_robot_ros2_ros1_bridge) and follow this instruction to build and install this project.
5. Open the other terminal and type ``roslaunch ros2_send_command_test test_bridge.launch``


#### Others
comming soon!

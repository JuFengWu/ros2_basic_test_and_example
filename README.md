# Ros2 basic test and example
This is a basic example and test for ros2

#### run action
1. Type ``ros2 run action_cpp action_member_functions_server`` to create a action server.
2. Type ``ros2 run action_cpp not_composable_client`` to create a action client.
3. Yuo will see the action demon.

#### run topic test
1. Open the first terminal and type ``ros2 run topic_test topic_sub_node``
2. Open the other terminal and typ ``ros2 run topic_test topic_pub_node``
3. You can see one terminal send message and the other listen message.

#### run service test
1. Open the first terminal and type ``ros2 run service_test client_topic_node``
2. Open the other terminal and typ ``ros2 run service_test service_topic_node``
3. You can see one terminal send service and the other listen it and send result back.

#### others
comming soon!

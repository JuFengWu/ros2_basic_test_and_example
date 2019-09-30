cmake_minimum_required(VERSION 3.5)
project(action_cpp)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(example_interfaces REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_action REQUIRED)
find_package(action_test REQUIRED)

include_directories(include 
${action_test_INCLUDE_DIRS}
)


add_executable(not_composable_client src/not_composable_client.cpp)
ament_target_dependencies(not_composable_client
  "rclcpp"
  "rclcpp_action"
  "example_interfaces"
  "action_test")

add_executable(action_member_functions_server src/member_function_server.cpp)
ament_target_dependencies(action_member_functions_server
  "rclcpp"
  "rclcpp_action"
  "example_interfaces"
  "action_test")

install(TARGETS
  not_composable_client
  action_member_functions_server
  DESTINATION lib/${PROJECT_NAME})

ament_package()

cmake_minimum_required(VERSION 3.5)

project(lifecycle)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp_lifecycle REQUIRED)
find_package(lifecycle_msgs REQUIRED)
find_package(rclcpp REQUIRED)
find_package(my_msgs REQUIRED)

include_directories(
  include
  ${lifecycle_msgs_INCLUDE_DIRS}
  ${rclcpp_lifecycle_INCLUDE_DIRS}
  ${rclcpp_INCLUDE_DIRS})

### demos
add_executable(lifecycle_talker
  src/talker.cpp)

ament_target_dependencies(lifecycle_talker
	"my_msgs"
	"rclcpp_lifecycle"
)
#target_link_libraries(lifecycle_talker
#  ${rclcpp_lifecycle_LIBRARIES}
#  ${my_msgs_LIBRARIES}
#)
add_executable(lifecycle_listener
  src/listener.cpp)


ament_target_dependencies(lifecycle_listener
	"my_msgs"
	"rclcpp_lifecycle"
)
#target_link_libraries(lifecycle_listener
#  ${rclcpp_lifecycle_LIBRARIES}
#  ${my_msgs_LIBRARIES}
#)
add_executable(lifecycle_controller
  src/lifecycle_controller.cpp)


ament_target_dependencies(lifecycle_controller
	"my_msgs"
	"rclcpp_lifecycle"
)
#target_link_libraries(lifecycle_controller
#  ${rclcpp_lifecycle_LIBRARIES}
#  ${my_msgs_LIBRARIES}
#)

install(TARGETS
  lifecycle_talker
  lifecycle_listener
  lifecycle_controller
  DESTINATION lib/${PROJECT_NAME})

ament_package()

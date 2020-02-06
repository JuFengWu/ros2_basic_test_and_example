cmake_minimum_required(VERSION 3.5)
project(qt_test)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Quick REQUIRED)
find_package(Qt5Widgets REQUIRED)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # uncomment the line when a copyright and license is not present in all source files
  #set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # uncomment the line when this package is not in a git repo
  #set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(
	${rclcpp_INCLUDE_DIRS}
	${std_msgs_INCLUDE_DIRS}
	${Qt5Core_INCLUDE_DIRS}
	${Qt5Quick_INCLUDE_DIRS}
        ${Qt5Widgets_INCLUDE_DIRS}
	)
link_directories(${catkin_LIBRARY_DIRS})

qt5_wrap_ui(UIC_FILES src/ui/qttest.ui)
set(HEADERS
  include/qttest.h
)

add_executable(my_qt_test src/qttest.cpp src/main.cpp ${UIC_FILES} ${HEADERS})

ament_target_dependencies(my_qt_test
	rclcpp
	std_msgs
)

target_link_libraries(my_qt_test
	Qt5::Core
	Qt5::Quick
        Qt5::Widgets
        ${catkin_LIBRARIES}
	)

install(TARGETS
	my_qt_test
	DESTINATION lib/${PROJECT_NAME}
)

add_executable(ros_to_qt src/ros_pub_sub_to_qt.cpp)
ament_target_dependencies(ros_to_qt
	"std_msgs"
	"rclcpp"
)

install(TARGETS
ros_to_qt
DESTINATION lib/${PROJECT_NAME}
)

ament_package()

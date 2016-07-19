cmake_minimum_required(VERSION 2.8.3)
project(third_gpio_control)

find_package(catkin REQUIRED COMPONENTS roscpp std_msgs)

catkin_package(
)

add_executable(third_gpio_control_node src/third_gpio_control_node.cpp)

target_link_libraries(third_gpio_control_node
	${catkin_LIBRARIES}
)

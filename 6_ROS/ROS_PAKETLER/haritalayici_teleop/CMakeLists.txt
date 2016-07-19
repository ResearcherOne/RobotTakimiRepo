cmake_minimum_required(VERSION 2.8.3)
project(haritalayici_teleop)

find_package(catkin REQUIRED COMPONENTS roscpp keyboard std_msgs)

catkin_package(
)

add_executable(haritalayici_teleop_node src/haritalayici_teleop_node.cpp)

target_link_libraries(haritalayici_teleop_node
	${catkin_LIBRARIES}
)

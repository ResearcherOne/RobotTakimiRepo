cmake_minimum_required(VERSION 2.8.3)
project(little_mapper_teleop)

find_package(catkin REQUIRED roscpp keyboard)

catkin_package(
)
add_executable(little_mapper_teleop_node src/little_mapper_teleop_node.cpp)

target_link_libraries(little_mapper_teleop_node
   ${catkin_LIBRARIES}
 )

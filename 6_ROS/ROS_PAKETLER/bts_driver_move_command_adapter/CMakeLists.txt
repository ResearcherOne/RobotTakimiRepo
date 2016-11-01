cmake_minimum_required(VERSION 2.8.3)
project(bts_driver_move_command_adapter)

find_package(catkin REQUIRED roscpp std_msgs)

catkin_package(
)

add_executable(bts_driver_move_command_adapter_node src/bts_driver_move_command_adapter_node.cpp)

target_link_libraries(bts_driver_move_command_adapter_node
   ${catkin_LIBRARIES}
 )

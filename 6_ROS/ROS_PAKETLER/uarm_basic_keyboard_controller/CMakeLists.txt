cmake_minimum_required(VERSION 2.8.3)
project(uarm_basic_keyboard_controller)

find_package(catkin REQUIRED COMPONENTS roscpp keyboard std_msgs)

catkin_package(
)

add_executable(uarm_basic_keyboard_controller_node src/uarm_basic_keyboard_controller_node.cpp)

target_link_libraries(uarm_basic_keyboard_controller_node
        ${catkin_LIBRARIES}
)


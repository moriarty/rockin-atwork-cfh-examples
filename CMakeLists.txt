
cmake_minimum_required (VERSION 2.8.7)
project (rockin-atwork-cfh-examples)

add_definitions("-std=c++0x")

add_subdirectory(protobuf/msgs/)
add_subdirectory(libs/)

include_directories(${INCLUDE_DIRS})

add_executable(peer src/peer.cpp)
target_link_libraries(peer cfh_msgs protobuf_comm)

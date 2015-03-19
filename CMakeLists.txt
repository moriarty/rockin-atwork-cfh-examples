
cmake_minimum_required (VERSION 2.8.7)
project (rockin-atwork-cfh-examples)

add_definitions("-std=c++0x")

add_subdirectory(cfh_msgs/)
add_subdirectory(protobuf_comm/)

include_directories(${INCLUDE_DIRS} rockin-cfh/src/libs)

add_executable(peer src/peer.cpp)
target_link_libraries(peer cfh_msgs protobuf_comm)

add_executable(peer-beacon src/peer-beacon.cpp)
target_link_libraries(peer-beacon cfh_msgs protobuf_comm)

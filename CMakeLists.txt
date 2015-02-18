
cmake_minimum_required (VERSION 2.8.7)
project (rockin-atwork-cfh-examples)

#find_package(Protobuf REQUIRED)
#include_directories(${PROTOBUF_INCLUDE_DIRS})


#file(GLOB RAW_REFBOX_MSGS_PROTOS protobuf/msgs/*.proto)
#protobuf_generate_cpp(REFBOX_PROTO_SRCS REFBOX_PROTO_HDRS ${RAW_REFBOX_MSGS_PROTOS})
#add_library(${DISAMBIGUATION}raw_refbox_msgs ${REFBOX_PROTO_SRCS})
#target_link_libraries(${DISAMBIGUATION}raw_refbox_msgs ${PROTOBUF_LIBRARIES})


##set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
##set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

add_definitions("-Wall")
add_definitions("-std=c++0x")

add_subdirectory(protobuf/msgs/)
add_subdirectory(libs/)



##add_subdirectory(include/)
include_directories(${INCLUDE_DIRS})
##add_executable(capture_comm src/capture_comm.cpp)
##target_link_libraries(capture_comm roah_rsbb_msgs protobuf_comm)

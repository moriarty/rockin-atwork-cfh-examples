#
# The file ( copy ... ) statement must be commented out the first time this is run.
#
find_package(Protobuf REQUIRED)
include_directories(${PROTOBUF_INCLUDE_DIRS})

file(GLOB CFH_PROTOS ${CMAKE_CURRENT_SOURCE_DIR}/*.proto)

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${CFH_PROTOS})
add_library(${DISAMBIGUATION}cfh_msgs ${PROTO_SRCS})
target_link_libraries(${DISAMBIGUATION}cfh_msgs ${PROTOBUF_LIBRARIES})
set(CFH_MSGS_HPP "${CMAKE_CURRENT_BINARY_DIR}/../cfh_msgs.h")
file(REMOVE ${CFH_MSGS_HPP})
foreach(PB_H ${PROTO_HDRS})
get_filename_component(FILE_PB_H ${PB_H} NAME)
file(APPEND ${CFH_MSGS_HPP} "#include \"raw_refbox_msgs/${FILE_PB_H}\"\n")
endforeach()

#file(
#COPY ${REFBOX_PROTO_HDRS} DESTINATION ${CATKIN_DEVEL_PREFIX}/${CATKIN_GLOBAL_INCLUDE_DESTINATION}/${PROJECT_NAME}
#)


include_directories(${CMAKE_CURRENT_BINARY_DIR}/../)
set(INCLUDE_DIRS ${INCLUDE_DIRS} ${CMAKE_CURRENT_BINARY_DIR}/../ PARENT_SCOPE)

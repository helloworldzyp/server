#cmake_minimum_required (VERSION 2.8)
cmake_minimum_required(VERSION 3.5)

project (demo)

set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# 查找 Protocol Buffers 库
find_package(Protobuf REQUIRED)

# 添加生成的源文件的路径
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# 生成 Protocol Buffers 源文件
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS include/proto/msg.proto)

aux_source_directory (src/client CLIENT_SRC_LIST)

aux_source_directory (src/server SERVER_SRC_LIST)

aux_source_directory (src/test TEST_SRC_LIST)

aux_source_directory (include/proto PROTO_SRC_LIST)

include_directories (include)
include_directories (include/proto)

message("123 proto src" ${PROTO_SRCS})
message("123 proto dir" ${PROTO_HDRS})

add_executable (client ${CLIENT_SRC_LIST} ${PROTO_SRCS} ${PROTO_HDRS})

add_executable (server ${SERVER_SRC_LIST} ${PROTO_SRCS} ${PROTO_HDRS})

add_executable (test ${TEST_SRC_LIST})

target_link_libraries(test PRIVATE pthread)

# 链接 Protocol Buffers 库
target_link_libraries(client ${PROTOBUF_LIBRARIES})

target_link_libraries(server ${PROTOBUF_LIBRARIES})
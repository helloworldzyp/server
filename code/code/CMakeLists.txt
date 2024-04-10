cmake_minimum_required (VERSION 2.8)

project (demo)

set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0")

aux_source_directory (src/client CLIENT_SRC_LIST)

aux_source_directory (src/server SERVER_SRC_LIST)

aux_source_directory (src/test TEST_SRC_LIST)

include_directories (include)

add_executable (client ${CLIENT_SRC_LIST})

add_executable (server ${SERVER_SRC_LIST})

add_executable (test ${TEST_SRC_LIST})
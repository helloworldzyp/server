aux_source_directory(. SRC_LIST)
#file(GLOB files ${PROJECT_SOURCE_DIR}/message/*)
#set(SRC_LIST "main.cpp" ${files})

SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS}  -Wall -g -ggdb  -std=c++11")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

message("PROJECT_SOURCE_DIR" ${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/lib/include)
add_executable(testserver ${SRC_LIST})
target_link_libraries(testserver  net)
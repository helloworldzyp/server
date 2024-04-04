cmake_minimum_required(VERSION 3.8)
project(socketcode)
add_subdirectory(lib)
add_subdirectory(server)
#add_subdirectory(client)

SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS}  -Wall -g -ggdb -std=c++11")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
####
###test
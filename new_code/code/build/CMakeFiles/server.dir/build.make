# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/zyp/src/code

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zyp/src/code/build

# Include any dependencies generated for this target.
include CMakeFiles/server.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/server.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/server.dir/flags.make

msg.pb.h: ../include/proto/msg.proto
msg.pb.h: /usr/bin/protoc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/zyp/src/code/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Running cpp protocol buffer compiler on include/proto/msg.proto"
	/usr/bin/protoc --cpp_out /home/zyp/src/code/build -I /home/zyp/src/code/include/proto /home/zyp/src/code/include/proto/msg.proto

msg.pb.cc: msg.pb.h
	@$(CMAKE_COMMAND) -E touch_nocreate msg.pb.cc

CMakeFiles/server.dir/src/server/server.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/src/server/server.cpp.o: ../src/server/server.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zyp/src/code/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/server.dir/src/server/server.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/src/server/server.cpp.o -c /home/zyp/src/code/src/server/server.cpp

CMakeFiles/server.dir/src/server/server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/src/server/server.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zyp/src/code/src/server/server.cpp > CMakeFiles/server.dir/src/server/server.cpp.i

CMakeFiles/server.dir/src/server/server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/src/server/server.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zyp/src/code/src/server/server.cpp -o CMakeFiles/server.dir/src/server/server.cpp.s

CMakeFiles/server.dir/msg.pb.cc.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/msg.pb.cc.o: msg.pb.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zyp/src/code/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/server.dir/msg.pb.cc.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/msg.pb.cc.o -c /home/zyp/src/code/build/msg.pb.cc

CMakeFiles/server.dir/msg.pb.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/msg.pb.cc.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zyp/src/code/build/msg.pb.cc > CMakeFiles/server.dir/msg.pb.cc.i

CMakeFiles/server.dir/msg.pb.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/msg.pb.cc.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zyp/src/code/build/msg.pb.cc -o CMakeFiles/server.dir/msg.pb.cc.s

# Object files for target server
server_OBJECTS = \
"CMakeFiles/server.dir/src/server/server.cpp.o" \
"CMakeFiles/server.dir/msg.pb.cc.o"

# External object files for target server
server_EXTERNAL_OBJECTS =

../bin/server: CMakeFiles/server.dir/src/server/server.cpp.o
../bin/server: CMakeFiles/server.dir/msg.pb.cc.o
../bin/server: CMakeFiles/server.dir/build.make
../bin/server: /usr/lib/x86_64-linux-gnu/libprotobuf.so
../bin/server: CMakeFiles/server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/zyp/src/code/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable ../bin/server"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/server.dir/build: ../bin/server

.PHONY : CMakeFiles/server.dir/build

CMakeFiles/server.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/server.dir/cmake_clean.cmake
.PHONY : CMakeFiles/server.dir/clean

CMakeFiles/server.dir/depend: msg.pb.h
CMakeFiles/server.dir/depend: msg.pb.cc
	cd /home/zyp/src/code/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zyp/src/code /home/zyp/src/code /home/zyp/src/code/build /home/zyp/src/code/build /home/zyp/src/code/build/CMakeFiles/server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/server.dir/depend

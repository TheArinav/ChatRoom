# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /tmp/tmp.Deqbg4Y2sX

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /tmp/tmp.Deqbg4Y2sX/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/ChatRoom.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/ChatRoom.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/ChatRoom.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ChatRoom.dir/flags.make

CMakeFiles/ChatRoom.dir/main.cpp.o: CMakeFiles/ChatRoom.dir/flags.make
CMakeFiles/ChatRoom.dir/main.cpp.o: ../main.cpp
CMakeFiles/ChatRoom.dir/main.cpp.o: CMakeFiles/ChatRoom.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/tmp/tmp.Deqbg4Y2sX/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ChatRoom.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ChatRoom.dir/main.cpp.o -MF CMakeFiles/ChatRoom.dir/main.cpp.o.d -o CMakeFiles/ChatRoom.dir/main.cpp.o -c /tmp/tmp.Deqbg4Y2sX/main.cpp

CMakeFiles/ChatRoom.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ChatRoom.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /tmp/tmp.Deqbg4Y2sX/main.cpp > CMakeFiles/ChatRoom.dir/main.cpp.i

CMakeFiles/ChatRoom.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ChatRoom.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /tmp/tmp.Deqbg4Y2sX/main.cpp -o CMakeFiles/ChatRoom.dir/main.cpp.s

# Object files for target ChatRoom
ChatRoom_OBJECTS = \
"CMakeFiles/ChatRoom.dir/main.cpp.o"

# External object files for target ChatRoom
ChatRoom_EXTERNAL_OBJECTS =

ChatRoom: CMakeFiles/ChatRoom.dir/main.cpp.o
ChatRoom: CMakeFiles/ChatRoom.dir/build.make
ChatRoom: CMakeFiles/ChatRoom.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/tmp/tmp.Deqbg4Y2sX/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ChatRoom"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ChatRoom.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ChatRoom.dir/build: ChatRoom
.PHONY : CMakeFiles/ChatRoom.dir/build

CMakeFiles/ChatRoom.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ChatRoom.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ChatRoom.dir/clean

CMakeFiles/ChatRoom.dir/depend:
	cd /tmp/tmp.Deqbg4Y2sX/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /tmp/tmp.Deqbg4Y2sX /tmp/tmp.Deqbg4Y2sX /tmp/tmp.Deqbg4Y2sX/cmake-build-debug /tmp/tmp.Deqbg4Y2sX/cmake-build-debug /tmp/tmp.Deqbg4Y2sX/cmake-build-debug/CMakeFiles/ChatRoom.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ChatRoom.dir/depend


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
CMAKE_SOURCE_DIR = /tmp/ChatRoom

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /tmp/ChatRoom/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/CPP.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/CPP.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/CPP.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/CPP.dir/flags.make

CMakeFiles/CPP.dir/src/main.cpp.o: CMakeFiles/CPP.dir/flags.make
CMakeFiles/CPP.dir/src/main.cpp.o: ../src/main.cpp
CMakeFiles/CPP.dir/src/main.cpp.o: CMakeFiles/CPP.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/tmp/ChatRoom/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/CPP.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/CPP.dir/src/main.cpp.o -MF CMakeFiles/CPP.dir/src/main.cpp.o.d -o CMakeFiles/CPP.dir/src/main.cpp.o -c /tmp/ChatRoom/src/main.cpp

CMakeFiles/CPP.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CPP.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /tmp/ChatRoom/src/main.cpp > CMakeFiles/CPP.dir/src/main.cpp.i

CMakeFiles/CPP.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CPP.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /tmp/ChatRoom/src/main.cpp -o CMakeFiles/CPP.dir/src/main.cpp.s

CMakeFiles/CPP.dir/src/Classes/GeneralTypes/ServerAction.cpp.o: CMakeFiles/CPP.dir/flags.make
CMakeFiles/CPP.dir/src/Classes/GeneralTypes/ServerAction.cpp.o: ../src/Classes/GeneralTypes/ServerAction.cpp
CMakeFiles/CPP.dir/src/Classes/GeneralTypes/ServerAction.cpp.o: CMakeFiles/CPP.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/tmp/ChatRoom/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/CPP.dir/src/Classes/GeneralTypes/ServerAction.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/CPP.dir/src/Classes/GeneralTypes/ServerAction.cpp.o -MF CMakeFiles/CPP.dir/src/Classes/GeneralTypes/ServerAction.cpp.o.d -o CMakeFiles/CPP.dir/src/Classes/GeneralTypes/ServerAction.cpp.o -c /tmp/ChatRoom/src/Classes/GeneralTypes/ServerAction.cpp

CMakeFiles/CPP.dir/src/Classes/GeneralTypes/ServerAction.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CPP.dir/src/Classes/GeneralTypes/ServerAction.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /tmp/ChatRoom/src/Classes/GeneralTypes/ServerAction.cpp > CMakeFiles/CPP.dir/src/Classes/GeneralTypes/ServerAction.cpp.i

CMakeFiles/CPP.dir/src/Classes/GeneralTypes/ServerAction.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CPP.dir/src/Classes/GeneralTypes/ServerAction.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /tmp/ChatRoom/src/Classes/GeneralTypes/ServerAction.cpp -o CMakeFiles/CPP.dir/src/Classes/GeneralTypes/ServerAction.cpp.s

CMakeFiles/CPP.dir/src/Classes/Backend/BackendComms.cpp.o: CMakeFiles/CPP.dir/flags.make
CMakeFiles/CPP.dir/src/Classes/Backend/BackendComms.cpp.o: ../src/Classes/Backend/BackendComms.cpp
CMakeFiles/CPP.dir/src/Classes/Backend/BackendComms.cpp.o: CMakeFiles/CPP.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/tmp/ChatRoom/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/CPP.dir/src/Classes/Backend/BackendComms.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/CPP.dir/src/Classes/Backend/BackendComms.cpp.o -MF CMakeFiles/CPP.dir/src/Classes/Backend/BackendComms.cpp.o.d -o CMakeFiles/CPP.dir/src/Classes/Backend/BackendComms.cpp.o -c /tmp/ChatRoom/src/Classes/Backend/BackendComms.cpp

CMakeFiles/CPP.dir/src/Classes/Backend/BackendComms.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CPP.dir/src/Classes/Backend/BackendComms.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /tmp/ChatRoom/src/Classes/Backend/BackendComms.cpp > CMakeFiles/CPP.dir/src/Classes/Backend/BackendComms.cpp.i

CMakeFiles/CPP.dir/src/Classes/Backend/BackendComms.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CPP.dir/src/Classes/Backend/BackendComms.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /tmp/ChatRoom/src/Classes/Backend/BackendComms.cpp -o CMakeFiles/CPP.dir/src/Classes/Backend/BackendComms.cpp.s

CMakeFiles/CPP.dir/src/Classes/Backend/RegisteredClient.cpp.o: CMakeFiles/CPP.dir/flags.make
CMakeFiles/CPP.dir/src/Classes/Backend/RegisteredClient.cpp.o: ../src/Classes/Backend/RegisteredClient.cpp
CMakeFiles/CPP.dir/src/Classes/Backend/RegisteredClient.cpp.o: CMakeFiles/CPP.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/tmp/ChatRoom/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/CPP.dir/src/Classes/Backend/RegisteredClient.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/CPP.dir/src/Classes/Backend/RegisteredClient.cpp.o -MF CMakeFiles/CPP.dir/src/Classes/Backend/RegisteredClient.cpp.o.d -o CMakeFiles/CPP.dir/src/Classes/Backend/RegisteredClient.cpp.o -c /tmp/ChatRoom/src/Classes/Backend/RegisteredClient.cpp

CMakeFiles/CPP.dir/src/Classes/Backend/RegisteredClient.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CPP.dir/src/Classes/Backend/RegisteredClient.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /tmp/ChatRoom/src/Classes/Backend/RegisteredClient.cpp > CMakeFiles/CPP.dir/src/Classes/Backend/RegisteredClient.cpp.i

CMakeFiles/CPP.dir/src/Classes/Backend/RegisteredClient.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CPP.dir/src/Classes/Backend/RegisteredClient.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /tmp/ChatRoom/src/Classes/Backend/RegisteredClient.cpp -o CMakeFiles/CPP.dir/src/Classes/Backend/RegisteredClient.cpp.s

CMakeFiles/CPP.dir/src/Classes/GeneralTypes/MessageQueue.cpp.o: CMakeFiles/CPP.dir/flags.make
CMakeFiles/CPP.dir/src/Classes/GeneralTypes/MessageQueue.cpp.o: ../src/Classes/GeneralTypes/MessageQueue.cpp
CMakeFiles/CPP.dir/src/Classes/GeneralTypes/MessageQueue.cpp.o: CMakeFiles/CPP.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/tmp/ChatRoom/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/CPP.dir/src/Classes/GeneralTypes/MessageQueue.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/CPP.dir/src/Classes/GeneralTypes/MessageQueue.cpp.o -MF CMakeFiles/CPP.dir/src/Classes/GeneralTypes/MessageQueue.cpp.o.d -o CMakeFiles/CPP.dir/src/Classes/GeneralTypes/MessageQueue.cpp.o -c /tmp/ChatRoom/src/Classes/GeneralTypes/MessageQueue.cpp

CMakeFiles/CPP.dir/src/Classes/GeneralTypes/MessageQueue.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CPP.dir/src/Classes/GeneralTypes/MessageQueue.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /tmp/ChatRoom/src/Classes/GeneralTypes/MessageQueue.cpp > CMakeFiles/CPP.dir/src/Classes/GeneralTypes/MessageQueue.cpp.i

CMakeFiles/CPP.dir/src/Classes/GeneralTypes/MessageQueue.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CPP.dir/src/Classes/GeneralTypes/MessageQueue.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /tmp/ChatRoom/src/Classes/GeneralTypes/MessageQueue.cpp -o CMakeFiles/CPP.dir/src/Classes/GeneralTypes/MessageQueue.cpp.s

CMakeFiles/CPP.dir/src/Classes/GeneralTypes/Message.cpp.o: CMakeFiles/CPP.dir/flags.make
CMakeFiles/CPP.dir/src/Classes/GeneralTypes/Message.cpp.o: ../src/Classes/GeneralTypes/Message.cpp
CMakeFiles/CPP.dir/src/Classes/GeneralTypes/Message.cpp.o: CMakeFiles/CPP.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/tmp/ChatRoom/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/CPP.dir/src/Classes/GeneralTypes/Message.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/CPP.dir/src/Classes/GeneralTypes/Message.cpp.o -MF CMakeFiles/CPP.dir/src/Classes/GeneralTypes/Message.cpp.o.d -o CMakeFiles/CPP.dir/src/Classes/GeneralTypes/Message.cpp.o -c /tmp/ChatRoom/src/Classes/GeneralTypes/Message.cpp

CMakeFiles/CPP.dir/src/Classes/GeneralTypes/Message.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CPP.dir/src/Classes/GeneralTypes/Message.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /tmp/ChatRoom/src/Classes/GeneralTypes/Message.cpp > CMakeFiles/CPP.dir/src/Classes/GeneralTypes/Message.cpp.i

CMakeFiles/CPP.dir/src/Classes/GeneralTypes/Message.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CPP.dir/src/Classes/GeneralTypes/Message.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /tmp/ChatRoom/src/Classes/GeneralTypes/Message.cpp -o CMakeFiles/CPP.dir/src/Classes/GeneralTypes/Message.cpp.s

# Object files for target CPP
CPP_OBJECTS = \
"CMakeFiles/CPP.dir/src/main.cpp.o" \
"CMakeFiles/CPP.dir/src/Classes/GeneralTypes/ServerAction.cpp.o" \
"CMakeFiles/CPP.dir/src/Classes/Backend/BackendComms.cpp.o" \
"CMakeFiles/CPP.dir/src/Classes/Backend/RegisteredClient.cpp.o" \
"CMakeFiles/CPP.dir/src/Classes/GeneralTypes/MessageQueue.cpp.o" \
"CMakeFiles/CPP.dir/src/Classes/GeneralTypes/Message.cpp.o"

# External object files for target CPP
CPP_EXTERNAL_OBJECTS =

CPP: CMakeFiles/CPP.dir/src/main.cpp.o
CPP: CMakeFiles/CPP.dir/src/Classes/GeneralTypes/ServerAction.cpp.o
CPP: CMakeFiles/CPP.dir/src/Classes/Backend/BackendComms.cpp.o
CPP: CMakeFiles/CPP.dir/src/Classes/Backend/RegisteredClient.cpp.o
CPP: CMakeFiles/CPP.dir/src/Classes/GeneralTypes/MessageQueue.cpp.o
CPP: CMakeFiles/CPP.dir/src/Classes/GeneralTypes/Message.cpp.o
CPP: CMakeFiles/CPP.dir/build.make
CPP: CMakeFiles/CPP.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/tmp/ChatRoom/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable CPP"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/CPP.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/CPP.dir/build: CPP
.PHONY : CMakeFiles/CPP.dir/build

CMakeFiles/CPP.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/CPP.dir/cmake_clean.cmake
.PHONY : CMakeFiles/CPP.dir/clean

CMakeFiles/CPP.dir/depend:
	cd /tmp/ChatRoom/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /tmp/ChatRoom /tmp/ChatRoom /tmp/ChatRoom/cmake-build-debug /tmp/ChatRoom/cmake-build-debug /tmp/ChatRoom/cmake-build-debug/CMakeFiles/CPP.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/CPP.dir/depend


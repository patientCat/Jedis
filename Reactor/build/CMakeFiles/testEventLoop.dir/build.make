# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/jmx/project/Jedis/Reactor

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jmx/project/Jedis/Reactor/build

# Include any dependencies generated for this target.
include CMakeFiles/testEventLoop.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/testEventLoop.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/testEventLoop.dir/flags.make

CMakeFiles/testEventLoop.dir/testEventLoop.cc.o: CMakeFiles/testEventLoop.dir/flags.make
CMakeFiles/testEventLoop.dir/testEventLoop.cc.o: ../testEventLoop.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jmx/project/Jedis/Reactor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/testEventLoop.dir/testEventLoop.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/testEventLoop.dir/testEventLoop.cc.o -c /home/jmx/project/Jedis/Reactor/testEventLoop.cc

CMakeFiles/testEventLoop.dir/testEventLoop.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testEventLoop.dir/testEventLoop.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jmx/project/Jedis/Reactor/testEventLoop.cc > CMakeFiles/testEventLoop.dir/testEventLoop.cc.i

CMakeFiles/testEventLoop.dir/testEventLoop.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testEventLoop.dir/testEventLoop.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jmx/project/Jedis/Reactor/testEventLoop.cc -o CMakeFiles/testEventLoop.dir/testEventLoop.cc.s

CMakeFiles/testEventLoop.dir/testEventLoop.cc.o.requires:

.PHONY : CMakeFiles/testEventLoop.dir/testEventLoop.cc.o.requires

CMakeFiles/testEventLoop.dir/testEventLoop.cc.o.provides: CMakeFiles/testEventLoop.dir/testEventLoop.cc.o.requires
	$(MAKE) -f CMakeFiles/testEventLoop.dir/build.make CMakeFiles/testEventLoop.dir/testEventLoop.cc.o.provides.build
.PHONY : CMakeFiles/testEventLoop.dir/testEventLoop.cc.o.provides

CMakeFiles/testEventLoop.dir/testEventLoop.cc.o.provides.build: CMakeFiles/testEventLoop.dir/testEventLoop.cc.o


CMakeFiles/testEventLoop.dir/EventLoop.cc.o: CMakeFiles/testEventLoop.dir/flags.make
CMakeFiles/testEventLoop.dir/EventLoop.cc.o: ../EventLoop.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jmx/project/Jedis/Reactor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/testEventLoop.dir/EventLoop.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/testEventLoop.dir/EventLoop.cc.o -c /home/jmx/project/Jedis/Reactor/EventLoop.cc

CMakeFiles/testEventLoop.dir/EventLoop.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testEventLoop.dir/EventLoop.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jmx/project/Jedis/Reactor/EventLoop.cc > CMakeFiles/testEventLoop.dir/EventLoop.cc.i

CMakeFiles/testEventLoop.dir/EventLoop.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testEventLoop.dir/EventLoop.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jmx/project/Jedis/Reactor/EventLoop.cc -o CMakeFiles/testEventLoop.dir/EventLoop.cc.s

CMakeFiles/testEventLoop.dir/EventLoop.cc.o.requires:

.PHONY : CMakeFiles/testEventLoop.dir/EventLoop.cc.o.requires

CMakeFiles/testEventLoop.dir/EventLoop.cc.o.provides: CMakeFiles/testEventLoop.dir/EventLoop.cc.o.requires
	$(MAKE) -f CMakeFiles/testEventLoop.dir/build.make CMakeFiles/testEventLoop.dir/EventLoop.cc.o.provides.build
.PHONY : CMakeFiles/testEventLoop.dir/EventLoop.cc.o.provides

CMakeFiles/testEventLoop.dir/EventLoop.cc.o.provides.build: CMakeFiles/testEventLoop.dir/EventLoop.cc.o


CMakeFiles/testEventLoop.dir/Event.cc.o: CMakeFiles/testEventLoop.dir/flags.make
CMakeFiles/testEventLoop.dir/Event.cc.o: ../Event.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jmx/project/Jedis/Reactor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/testEventLoop.dir/Event.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/testEventLoop.dir/Event.cc.o -c /home/jmx/project/Jedis/Reactor/Event.cc

CMakeFiles/testEventLoop.dir/Event.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testEventLoop.dir/Event.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jmx/project/Jedis/Reactor/Event.cc > CMakeFiles/testEventLoop.dir/Event.cc.i

CMakeFiles/testEventLoop.dir/Event.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testEventLoop.dir/Event.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jmx/project/Jedis/Reactor/Event.cc -o CMakeFiles/testEventLoop.dir/Event.cc.s

CMakeFiles/testEventLoop.dir/Event.cc.o.requires:

.PHONY : CMakeFiles/testEventLoop.dir/Event.cc.o.requires

CMakeFiles/testEventLoop.dir/Event.cc.o.provides: CMakeFiles/testEventLoop.dir/Event.cc.o.requires
	$(MAKE) -f CMakeFiles/testEventLoop.dir/build.make CMakeFiles/testEventLoop.dir/Event.cc.o.provides.build
.PHONY : CMakeFiles/testEventLoop.dir/Event.cc.o.provides

CMakeFiles/testEventLoop.dir/Event.cc.o.provides.build: CMakeFiles/testEventLoop.dir/Event.cc.o


CMakeFiles/testEventLoop.dir/Poller.cc.o: CMakeFiles/testEventLoop.dir/flags.make
CMakeFiles/testEventLoop.dir/Poller.cc.o: ../Poller.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jmx/project/Jedis/Reactor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/testEventLoop.dir/Poller.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/testEventLoop.dir/Poller.cc.o -c /home/jmx/project/Jedis/Reactor/Poller.cc

CMakeFiles/testEventLoop.dir/Poller.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testEventLoop.dir/Poller.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jmx/project/Jedis/Reactor/Poller.cc > CMakeFiles/testEventLoop.dir/Poller.cc.i

CMakeFiles/testEventLoop.dir/Poller.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testEventLoop.dir/Poller.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jmx/project/Jedis/Reactor/Poller.cc -o CMakeFiles/testEventLoop.dir/Poller.cc.s

CMakeFiles/testEventLoop.dir/Poller.cc.o.requires:

.PHONY : CMakeFiles/testEventLoop.dir/Poller.cc.o.requires

CMakeFiles/testEventLoop.dir/Poller.cc.o.provides: CMakeFiles/testEventLoop.dir/Poller.cc.o.requires
	$(MAKE) -f CMakeFiles/testEventLoop.dir/build.make CMakeFiles/testEventLoop.dir/Poller.cc.o.provides.build
.PHONY : CMakeFiles/testEventLoop.dir/Poller.cc.o.provides

CMakeFiles/testEventLoop.dir/Poller.cc.o.provides.build: CMakeFiles/testEventLoop.dir/Poller.cc.o


CMakeFiles/testEventLoop.dir/Socket.cc.o: CMakeFiles/testEventLoop.dir/flags.make
CMakeFiles/testEventLoop.dir/Socket.cc.o: ../Socket.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jmx/project/Jedis/Reactor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/testEventLoop.dir/Socket.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/testEventLoop.dir/Socket.cc.o -c /home/jmx/project/Jedis/Reactor/Socket.cc

CMakeFiles/testEventLoop.dir/Socket.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testEventLoop.dir/Socket.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jmx/project/Jedis/Reactor/Socket.cc > CMakeFiles/testEventLoop.dir/Socket.cc.i

CMakeFiles/testEventLoop.dir/Socket.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testEventLoop.dir/Socket.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jmx/project/Jedis/Reactor/Socket.cc -o CMakeFiles/testEventLoop.dir/Socket.cc.s

CMakeFiles/testEventLoop.dir/Socket.cc.o.requires:

.PHONY : CMakeFiles/testEventLoop.dir/Socket.cc.o.requires

CMakeFiles/testEventLoop.dir/Socket.cc.o.provides: CMakeFiles/testEventLoop.dir/Socket.cc.o.requires
	$(MAKE) -f CMakeFiles/testEventLoop.dir/build.make CMakeFiles/testEventLoop.dir/Socket.cc.o.provides.build
.PHONY : CMakeFiles/testEventLoop.dir/Socket.cc.o.provides

CMakeFiles/testEventLoop.dir/Socket.cc.o.provides.build: CMakeFiles/testEventLoop.dir/Socket.cc.o


# Object files for target testEventLoop
testEventLoop_OBJECTS = \
"CMakeFiles/testEventLoop.dir/testEventLoop.cc.o" \
"CMakeFiles/testEventLoop.dir/EventLoop.cc.o" \
"CMakeFiles/testEventLoop.dir/Event.cc.o" \
"CMakeFiles/testEventLoop.dir/Poller.cc.o" \
"CMakeFiles/testEventLoop.dir/Socket.cc.o"

# External object files for target testEventLoop
testEventLoop_EXTERNAL_OBJECTS =

testEventLoop: CMakeFiles/testEventLoop.dir/testEventLoop.cc.o
testEventLoop: CMakeFiles/testEventLoop.dir/EventLoop.cc.o
testEventLoop: CMakeFiles/testEventLoop.dir/Event.cc.o
testEventLoop: CMakeFiles/testEventLoop.dir/Poller.cc.o
testEventLoop: CMakeFiles/testEventLoop.dir/Socket.cc.o
testEventLoop: CMakeFiles/testEventLoop.dir/build.make
testEventLoop: CMakeFiles/testEventLoop.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jmx/project/Jedis/Reactor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable testEventLoop"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/testEventLoop.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/testEventLoop.dir/build: testEventLoop

.PHONY : CMakeFiles/testEventLoop.dir/build

CMakeFiles/testEventLoop.dir/requires: CMakeFiles/testEventLoop.dir/testEventLoop.cc.o.requires
CMakeFiles/testEventLoop.dir/requires: CMakeFiles/testEventLoop.dir/EventLoop.cc.o.requires
CMakeFiles/testEventLoop.dir/requires: CMakeFiles/testEventLoop.dir/Event.cc.o.requires
CMakeFiles/testEventLoop.dir/requires: CMakeFiles/testEventLoop.dir/Poller.cc.o.requires
CMakeFiles/testEventLoop.dir/requires: CMakeFiles/testEventLoop.dir/Socket.cc.o.requires

.PHONY : CMakeFiles/testEventLoop.dir/requires

CMakeFiles/testEventLoop.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/testEventLoop.dir/cmake_clean.cmake
.PHONY : CMakeFiles/testEventLoop.dir/clean

CMakeFiles/testEventLoop.dir/depend:
	cd /home/jmx/project/Jedis/Reactor/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jmx/project/Jedis/Reactor /home/jmx/project/Jedis/Reactor /home/jmx/project/Jedis/Reactor/build /home/jmx/project/Jedis/Reactor/build /home/jmx/project/Jedis/Reactor/build/CMakeFiles/testEventLoop.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/testEventLoop.dir/depend


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
CMAKE_SOURCE_DIR = /home/jmx/project/Jedis/RedisServer_0.3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jmx/project/Jedis/RedisServer_0.3/tmp_build

# Include any dependencies generated for this target.
include CMakeFiles/jedis.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/jedis.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/jedis.dir/flags.make

CMakeFiles/jedis.dir/jedis.cc.o: CMakeFiles/jedis.dir/flags.make
CMakeFiles/jedis.dir/jedis.cc.o: ../jedis.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jmx/project/Jedis/RedisServer_0.3/tmp_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/jedis.dir/jedis.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/jedis.dir/jedis.cc.o -c /home/jmx/project/Jedis/RedisServer_0.3/jedis.cc

CMakeFiles/jedis.dir/jedis.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/jedis.dir/jedis.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jmx/project/Jedis/RedisServer_0.3/jedis.cc > CMakeFiles/jedis.dir/jedis.cc.i

CMakeFiles/jedis.dir/jedis.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/jedis.dir/jedis.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jmx/project/Jedis/RedisServer_0.3/jedis.cc -o CMakeFiles/jedis.dir/jedis.cc.s

CMakeFiles/jedis.dir/jedis.cc.o.requires:

.PHONY : CMakeFiles/jedis.dir/jedis.cc.o.requires

CMakeFiles/jedis.dir/jedis.cc.o.provides: CMakeFiles/jedis.dir/jedis.cc.o.requires
	$(MAKE) -f CMakeFiles/jedis.dir/build.make CMakeFiles/jedis.dir/jedis.cc.o.provides.build
.PHONY : CMakeFiles/jedis.dir/jedis.cc.o.provides

CMakeFiles/jedis.dir/jedis.cc.o.provides.build: CMakeFiles/jedis.dir/jedis.cc.o


CMakeFiles/jedis.dir/Buffer.cc.o: CMakeFiles/jedis.dir/flags.make
CMakeFiles/jedis.dir/Buffer.cc.o: ../Buffer.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jmx/project/Jedis/RedisServer_0.3/tmp_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/jedis.dir/Buffer.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/jedis.dir/Buffer.cc.o -c /home/jmx/project/Jedis/RedisServer_0.3/Buffer.cc

CMakeFiles/jedis.dir/Buffer.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/jedis.dir/Buffer.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jmx/project/Jedis/RedisServer_0.3/Buffer.cc > CMakeFiles/jedis.dir/Buffer.cc.i

CMakeFiles/jedis.dir/Buffer.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/jedis.dir/Buffer.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jmx/project/Jedis/RedisServer_0.3/Buffer.cc -o CMakeFiles/jedis.dir/Buffer.cc.s

CMakeFiles/jedis.dir/Buffer.cc.o.requires:

.PHONY : CMakeFiles/jedis.dir/Buffer.cc.o.requires

CMakeFiles/jedis.dir/Buffer.cc.o.provides: CMakeFiles/jedis.dir/Buffer.cc.o.requires
	$(MAKE) -f CMakeFiles/jedis.dir/build.make CMakeFiles/jedis.dir/Buffer.cc.o.provides.build
.PHONY : CMakeFiles/jedis.dir/Buffer.cc.o.provides

CMakeFiles/jedis.dir/Buffer.cc.o.provides.build: CMakeFiles/jedis.dir/Buffer.cc.o


CMakeFiles/jedis.dir/EventLoop.cc.o: CMakeFiles/jedis.dir/flags.make
CMakeFiles/jedis.dir/EventLoop.cc.o: ../EventLoop.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jmx/project/Jedis/RedisServer_0.3/tmp_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/jedis.dir/EventLoop.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/jedis.dir/EventLoop.cc.o -c /home/jmx/project/Jedis/RedisServer_0.3/EventLoop.cc

CMakeFiles/jedis.dir/EventLoop.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/jedis.dir/EventLoop.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jmx/project/Jedis/RedisServer_0.3/EventLoop.cc > CMakeFiles/jedis.dir/EventLoop.cc.i

CMakeFiles/jedis.dir/EventLoop.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/jedis.dir/EventLoop.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jmx/project/Jedis/RedisServer_0.3/EventLoop.cc -o CMakeFiles/jedis.dir/EventLoop.cc.s

CMakeFiles/jedis.dir/EventLoop.cc.o.requires:

.PHONY : CMakeFiles/jedis.dir/EventLoop.cc.o.requires

CMakeFiles/jedis.dir/EventLoop.cc.o.provides: CMakeFiles/jedis.dir/EventLoop.cc.o.requires
	$(MAKE) -f CMakeFiles/jedis.dir/build.make CMakeFiles/jedis.dir/EventLoop.cc.o.provides.build
.PHONY : CMakeFiles/jedis.dir/EventLoop.cc.o.provides

CMakeFiles/jedis.dir/EventLoop.cc.o.provides.build: CMakeFiles/jedis.dir/EventLoop.cc.o


CMakeFiles/jedis.dir/Event.cc.o: CMakeFiles/jedis.dir/flags.make
CMakeFiles/jedis.dir/Event.cc.o: ../Event.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jmx/project/Jedis/RedisServer_0.3/tmp_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/jedis.dir/Event.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/jedis.dir/Event.cc.o -c /home/jmx/project/Jedis/RedisServer_0.3/Event.cc

CMakeFiles/jedis.dir/Event.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/jedis.dir/Event.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jmx/project/Jedis/RedisServer_0.3/Event.cc > CMakeFiles/jedis.dir/Event.cc.i

CMakeFiles/jedis.dir/Event.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/jedis.dir/Event.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jmx/project/Jedis/RedisServer_0.3/Event.cc -o CMakeFiles/jedis.dir/Event.cc.s

CMakeFiles/jedis.dir/Event.cc.o.requires:

.PHONY : CMakeFiles/jedis.dir/Event.cc.o.requires

CMakeFiles/jedis.dir/Event.cc.o.provides: CMakeFiles/jedis.dir/Event.cc.o.requires
	$(MAKE) -f CMakeFiles/jedis.dir/build.make CMakeFiles/jedis.dir/Event.cc.o.provides.build
.PHONY : CMakeFiles/jedis.dir/Event.cc.o.provides

CMakeFiles/jedis.dir/Event.cc.o.provides.build: CMakeFiles/jedis.dir/Event.cc.o


CMakeFiles/jedis.dir/Logging.cc.o: CMakeFiles/jedis.dir/flags.make
CMakeFiles/jedis.dir/Logging.cc.o: ../Logging.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jmx/project/Jedis/RedisServer_0.3/tmp_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/jedis.dir/Logging.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/jedis.dir/Logging.cc.o -c /home/jmx/project/Jedis/RedisServer_0.3/Logging.cc

CMakeFiles/jedis.dir/Logging.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/jedis.dir/Logging.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jmx/project/Jedis/RedisServer_0.3/Logging.cc > CMakeFiles/jedis.dir/Logging.cc.i

CMakeFiles/jedis.dir/Logging.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/jedis.dir/Logging.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jmx/project/Jedis/RedisServer_0.3/Logging.cc -o CMakeFiles/jedis.dir/Logging.cc.s

CMakeFiles/jedis.dir/Logging.cc.o.requires:

.PHONY : CMakeFiles/jedis.dir/Logging.cc.o.requires

CMakeFiles/jedis.dir/Logging.cc.o.provides: CMakeFiles/jedis.dir/Logging.cc.o.requires
	$(MAKE) -f CMakeFiles/jedis.dir/build.make CMakeFiles/jedis.dir/Logging.cc.o.provides.build
.PHONY : CMakeFiles/jedis.dir/Logging.cc.o.provides

CMakeFiles/jedis.dir/Logging.cc.o.provides.build: CMakeFiles/jedis.dir/Logging.cc.o


CMakeFiles/jedis.dir/LogStream.cc.o: CMakeFiles/jedis.dir/flags.make
CMakeFiles/jedis.dir/LogStream.cc.o: ../LogStream.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jmx/project/Jedis/RedisServer_0.3/tmp_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/jedis.dir/LogStream.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/jedis.dir/LogStream.cc.o -c /home/jmx/project/Jedis/RedisServer_0.3/LogStream.cc

CMakeFiles/jedis.dir/LogStream.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/jedis.dir/LogStream.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jmx/project/Jedis/RedisServer_0.3/LogStream.cc > CMakeFiles/jedis.dir/LogStream.cc.i

CMakeFiles/jedis.dir/LogStream.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/jedis.dir/LogStream.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jmx/project/Jedis/RedisServer_0.3/LogStream.cc -o CMakeFiles/jedis.dir/LogStream.cc.s

CMakeFiles/jedis.dir/LogStream.cc.o.requires:

.PHONY : CMakeFiles/jedis.dir/LogStream.cc.o.requires

CMakeFiles/jedis.dir/LogStream.cc.o.provides: CMakeFiles/jedis.dir/LogStream.cc.o.requires
	$(MAKE) -f CMakeFiles/jedis.dir/build.make CMakeFiles/jedis.dir/LogStream.cc.o.provides.build
.PHONY : CMakeFiles/jedis.dir/LogStream.cc.o.provides

CMakeFiles/jedis.dir/LogStream.cc.o.provides.build: CMakeFiles/jedis.dir/LogStream.cc.o


CMakeFiles/jedis.dir/Poller.cc.o: CMakeFiles/jedis.dir/flags.make
CMakeFiles/jedis.dir/Poller.cc.o: ../Poller.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jmx/project/Jedis/RedisServer_0.3/tmp_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/jedis.dir/Poller.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/jedis.dir/Poller.cc.o -c /home/jmx/project/Jedis/RedisServer_0.3/Poller.cc

CMakeFiles/jedis.dir/Poller.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/jedis.dir/Poller.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jmx/project/Jedis/RedisServer_0.3/Poller.cc > CMakeFiles/jedis.dir/Poller.cc.i

CMakeFiles/jedis.dir/Poller.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/jedis.dir/Poller.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jmx/project/Jedis/RedisServer_0.3/Poller.cc -o CMakeFiles/jedis.dir/Poller.cc.s

CMakeFiles/jedis.dir/Poller.cc.o.requires:

.PHONY : CMakeFiles/jedis.dir/Poller.cc.o.requires

CMakeFiles/jedis.dir/Poller.cc.o.provides: CMakeFiles/jedis.dir/Poller.cc.o.requires
	$(MAKE) -f CMakeFiles/jedis.dir/build.make CMakeFiles/jedis.dir/Poller.cc.o.provides.build
.PHONY : CMakeFiles/jedis.dir/Poller.cc.o.provides

CMakeFiles/jedis.dir/Poller.cc.o.provides.build: CMakeFiles/jedis.dir/Poller.cc.o


CMakeFiles/jedis.dir/Socket.cc.o: CMakeFiles/jedis.dir/flags.make
CMakeFiles/jedis.dir/Socket.cc.o: ../Socket.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jmx/project/Jedis/RedisServer_0.3/tmp_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/jedis.dir/Socket.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/jedis.dir/Socket.cc.o -c /home/jmx/project/Jedis/RedisServer_0.3/Socket.cc

CMakeFiles/jedis.dir/Socket.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/jedis.dir/Socket.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jmx/project/Jedis/RedisServer_0.3/Socket.cc > CMakeFiles/jedis.dir/Socket.cc.i

CMakeFiles/jedis.dir/Socket.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/jedis.dir/Socket.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jmx/project/Jedis/RedisServer_0.3/Socket.cc -o CMakeFiles/jedis.dir/Socket.cc.s

CMakeFiles/jedis.dir/Socket.cc.o.requires:

.PHONY : CMakeFiles/jedis.dir/Socket.cc.o.requires

CMakeFiles/jedis.dir/Socket.cc.o.provides: CMakeFiles/jedis.dir/Socket.cc.o.requires
	$(MAKE) -f CMakeFiles/jedis.dir/build.make CMakeFiles/jedis.dir/Socket.cc.o.provides.build
.PHONY : CMakeFiles/jedis.dir/Socket.cc.o.provides

CMakeFiles/jedis.dir/Socket.cc.o.provides.build: CMakeFiles/jedis.dir/Socket.cc.o


CMakeFiles/jedis.dir/TcpConnection.cc.o: CMakeFiles/jedis.dir/flags.make
CMakeFiles/jedis.dir/TcpConnection.cc.o: ../TcpConnection.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jmx/project/Jedis/RedisServer_0.3/tmp_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/jedis.dir/TcpConnection.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/jedis.dir/TcpConnection.cc.o -c /home/jmx/project/Jedis/RedisServer_0.3/TcpConnection.cc

CMakeFiles/jedis.dir/TcpConnection.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/jedis.dir/TcpConnection.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jmx/project/Jedis/RedisServer_0.3/TcpConnection.cc > CMakeFiles/jedis.dir/TcpConnection.cc.i

CMakeFiles/jedis.dir/TcpConnection.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/jedis.dir/TcpConnection.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jmx/project/Jedis/RedisServer_0.3/TcpConnection.cc -o CMakeFiles/jedis.dir/TcpConnection.cc.s

CMakeFiles/jedis.dir/TcpConnection.cc.o.requires:

.PHONY : CMakeFiles/jedis.dir/TcpConnection.cc.o.requires

CMakeFiles/jedis.dir/TcpConnection.cc.o.provides: CMakeFiles/jedis.dir/TcpConnection.cc.o.requires
	$(MAKE) -f CMakeFiles/jedis.dir/build.make CMakeFiles/jedis.dir/TcpConnection.cc.o.provides.build
.PHONY : CMakeFiles/jedis.dir/TcpConnection.cc.o.provides

CMakeFiles/jedis.dir/TcpConnection.cc.o.provides.build: CMakeFiles/jedis.dir/TcpConnection.cc.o


# Object files for target jedis
jedis_OBJECTS = \
"CMakeFiles/jedis.dir/jedis.cc.o" \
"CMakeFiles/jedis.dir/Buffer.cc.o" \
"CMakeFiles/jedis.dir/EventLoop.cc.o" \
"CMakeFiles/jedis.dir/Event.cc.o" \
"CMakeFiles/jedis.dir/Logging.cc.o" \
"CMakeFiles/jedis.dir/LogStream.cc.o" \
"CMakeFiles/jedis.dir/Poller.cc.o" \
"CMakeFiles/jedis.dir/Socket.cc.o" \
"CMakeFiles/jedis.dir/TcpConnection.cc.o"

# External object files for target jedis
jedis_EXTERNAL_OBJECTS =

../bin/jedis: CMakeFiles/jedis.dir/jedis.cc.o
../bin/jedis: CMakeFiles/jedis.dir/Buffer.cc.o
../bin/jedis: CMakeFiles/jedis.dir/EventLoop.cc.o
../bin/jedis: CMakeFiles/jedis.dir/Event.cc.o
../bin/jedis: CMakeFiles/jedis.dir/Logging.cc.o
../bin/jedis: CMakeFiles/jedis.dir/LogStream.cc.o
../bin/jedis: CMakeFiles/jedis.dir/Poller.cc.o
../bin/jedis: CMakeFiles/jedis.dir/Socket.cc.o
../bin/jedis: CMakeFiles/jedis.dir/TcpConnection.cc.o
../bin/jedis: CMakeFiles/jedis.dir/build.make
../bin/jedis: CMakeFiles/jedis.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jmx/project/Jedis/RedisServer_0.3/tmp_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking CXX executable ../bin/jedis"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/jedis.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/jedis.dir/build: ../bin/jedis

.PHONY : CMakeFiles/jedis.dir/build

CMakeFiles/jedis.dir/requires: CMakeFiles/jedis.dir/jedis.cc.o.requires
CMakeFiles/jedis.dir/requires: CMakeFiles/jedis.dir/Buffer.cc.o.requires
CMakeFiles/jedis.dir/requires: CMakeFiles/jedis.dir/EventLoop.cc.o.requires
CMakeFiles/jedis.dir/requires: CMakeFiles/jedis.dir/Event.cc.o.requires
CMakeFiles/jedis.dir/requires: CMakeFiles/jedis.dir/Logging.cc.o.requires
CMakeFiles/jedis.dir/requires: CMakeFiles/jedis.dir/LogStream.cc.o.requires
CMakeFiles/jedis.dir/requires: CMakeFiles/jedis.dir/Poller.cc.o.requires
CMakeFiles/jedis.dir/requires: CMakeFiles/jedis.dir/Socket.cc.o.requires
CMakeFiles/jedis.dir/requires: CMakeFiles/jedis.dir/TcpConnection.cc.o.requires

.PHONY : CMakeFiles/jedis.dir/requires

CMakeFiles/jedis.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/jedis.dir/cmake_clean.cmake
.PHONY : CMakeFiles/jedis.dir/clean

CMakeFiles/jedis.dir/depend:
	cd /home/jmx/project/Jedis/RedisServer_0.3/tmp_build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jmx/project/Jedis/RedisServer_0.3 /home/jmx/project/Jedis/RedisServer_0.3 /home/jmx/project/Jedis/RedisServer_0.3/tmp_build /home/jmx/project/Jedis/RedisServer_0.3/tmp_build /home/jmx/project/Jedis/RedisServer_0.3/tmp_build/CMakeFiles/jedis.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/jedis.dir/depend


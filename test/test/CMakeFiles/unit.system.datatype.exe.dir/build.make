# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/gravil/workspace/TER/mmm

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/gravil/workspace/TER/mmm/test

# Include any dependencies generated for this target.
include test/CMakeFiles/unit.system.datatype.exe.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include test/CMakeFiles/unit.system.datatype.exe.dir/compiler_depend.make

# Include the progress variables for this target.
include test/CMakeFiles/unit.system.datatype.exe.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/unit.system.datatype.exe.dir/flags.make

test/CMakeFiles/unit.system.datatype.exe.dir/unit/system/datatype.cpp.o: test/CMakeFiles/unit.system.datatype.exe.dir/flags.make
test/CMakeFiles/unit.system.datatype.exe.dir/unit/system/datatype.cpp.o: unit/system/datatype.cpp
test/CMakeFiles/unit.system.datatype.exe.dir/unit/system/datatype.cpp.o: test/CMakeFiles/unit.system.datatype.exe.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gravil/workspace/TER/mmm/test/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/unit.system.datatype.exe.dir/unit/system/datatype.cpp.o"
	cd /home/gravil/workspace/TER/mmm/test/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT test/CMakeFiles/unit.system.datatype.exe.dir/unit/system/datatype.cpp.o -MF CMakeFiles/unit.system.datatype.exe.dir/unit/system/datatype.cpp.o.d -o CMakeFiles/unit.system.datatype.exe.dir/unit/system/datatype.cpp.o -c /home/gravil/workspace/TER/mmm/test/unit/system/datatype.cpp

test/CMakeFiles/unit.system.datatype.exe.dir/unit/system/datatype.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/unit.system.datatype.exe.dir/unit/system/datatype.cpp.i"
	cd /home/gravil/workspace/TER/mmm/test/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gravil/workspace/TER/mmm/test/unit/system/datatype.cpp > CMakeFiles/unit.system.datatype.exe.dir/unit/system/datatype.cpp.i

test/CMakeFiles/unit.system.datatype.exe.dir/unit/system/datatype.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/unit.system.datatype.exe.dir/unit/system/datatype.cpp.s"
	cd /home/gravil/workspace/TER/mmm/test/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gravil/workspace/TER/mmm/test/unit/system/datatype.cpp -o CMakeFiles/unit.system.datatype.exe.dir/unit/system/datatype.cpp.s

# Object files for target unit.system.datatype.exe
unit_system_datatype_exe_OBJECTS = \
"CMakeFiles/unit.system.datatype.exe.dir/unit/system/datatype.cpp.o"

# External object files for target unit.system.datatype.exe
unit_system_datatype_exe_EXTERNAL_OBJECTS =

unit/unit.system.datatype.exe: test/CMakeFiles/unit.system.datatype.exe.dir/unit/system/datatype.cpp.o
unit/unit.system.datatype.exe: test/CMakeFiles/unit.system.datatype.exe.dir/build.make
unit/unit.system.datatype.exe: /usr/lib/libmpi_cxx.so
unit/unit.system.datatype.exe: /usr/lib/libmpi.so
unit/unit.system.datatype.exe: test/CMakeFiles/unit.system.datatype.exe.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/gravil/workspace/TER/mmm/test/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../unit/unit.system.datatype.exe"
	cd /home/gravil/workspace/TER/mmm/test/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/unit.system.datatype.exe.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/unit.system.datatype.exe.dir/build: unit/unit.system.datatype.exe
.PHONY : test/CMakeFiles/unit.system.datatype.exe.dir/build

test/CMakeFiles/unit.system.datatype.exe.dir/clean:
	cd /home/gravil/workspace/TER/mmm/test/test && $(CMAKE_COMMAND) -P CMakeFiles/unit.system.datatype.exe.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/unit.system.datatype.exe.dir/clean

test/CMakeFiles/unit.system.datatype.exe.dir/depend:
	cd /home/gravil/workspace/TER/mmm/test && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gravil/workspace/TER/mmm /home/gravil/workspace/TER/mmm/test /home/gravil/workspace/TER/mmm/test /home/gravil/workspace/TER/mmm/test/test /home/gravil/workspace/TER/mmm/test/test/CMakeFiles/unit.system.datatype.exe.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/unit.system.datatype.exe.dir/depend


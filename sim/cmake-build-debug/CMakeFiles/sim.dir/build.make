# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

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
CMAKE_COMMAND = /cygdrive/c/Users/Ethan/.CLion2018.2/system/cygwin_cmake/bin/cmake.exe

# The command to remove a file.
RM = /cygdrive/c/Users/Ethan/.CLion2018.2/system/cygwin_cmake/bin/cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /cygdrive/c/Users/Ethan/CLionProjects/sim

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /cygdrive/c/Users/Ethan/CLionProjects/sim/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/sim.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/sim.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/sim.dir/flags.make

CMakeFiles/sim.dir/simulator.c.o: CMakeFiles/sim.dir/flags.make
CMakeFiles/sim.dir/simulator.c.o: ../simulator.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cygdrive/c/Users/Ethan/CLionProjects/sim/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/sim.dir/simulator.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/sim.dir/simulator.c.o   -c /cygdrive/c/Users/Ethan/CLionProjects/sim/simulator.c

CMakeFiles/sim.dir/simulator.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/sim.dir/simulator.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /cygdrive/c/Users/Ethan/CLionProjects/sim/simulator.c > CMakeFiles/sim.dir/simulator.c.i

CMakeFiles/sim.dir/simulator.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/sim.dir/simulator.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /cygdrive/c/Users/Ethan/CLionProjects/sim/simulator.c -o CMakeFiles/sim.dir/simulator.c.s

CMakeFiles/sim.dir/bstr.c.o: CMakeFiles/sim.dir/flags.make
CMakeFiles/sim.dir/bstr.c.o: ../bstr.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cygdrive/c/Users/Ethan/CLionProjects/sim/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/sim.dir/bstr.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/sim.dir/bstr.c.o   -c /cygdrive/c/Users/Ethan/CLionProjects/sim/bstr.c

CMakeFiles/sim.dir/bstr.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/sim.dir/bstr.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /cygdrive/c/Users/Ethan/CLionProjects/sim/bstr.c > CMakeFiles/sim.dir/bstr.c.i

CMakeFiles/sim.dir/bstr.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/sim.dir/bstr.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /cygdrive/c/Users/Ethan/CLionProjects/sim/bstr.c -o CMakeFiles/sim.dir/bstr.c.s

CMakeFiles/sim.dir/comp.c.o: CMakeFiles/sim.dir/flags.make
CMakeFiles/sim.dir/comp.c.o: ../comp.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cygdrive/c/Users/Ethan/CLionProjects/sim/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/sim.dir/comp.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/sim.dir/comp.c.o   -c /cygdrive/c/Users/Ethan/CLionProjects/sim/comp.c

CMakeFiles/sim.dir/comp.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/sim.dir/comp.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /cygdrive/c/Users/Ethan/CLionProjects/sim/comp.c > CMakeFiles/sim.dir/comp.c.i

CMakeFiles/sim.dir/comp.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/sim.dir/comp.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /cygdrive/c/Users/Ethan/CLionProjects/sim/comp.c -o CMakeFiles/sim.dir/comp.c.s

# Object files for target sim
sim_OBJECTS = \
"CMakeFiles/sim.dir/simulator.c.o" \
"CMakeFiles/sim.dir/bstr.c.o" \
"CMakeFiles/sim.dir/comp.c.o"

# External object files for target sim
sim_EXTERNAL_OBJECTS =

sim.exe: CMakeFiles/sim.dir/simulator.c.o
sim.exe: CMakeFiles/sim.dir/bstr.c.o
sim.exe: CMakeFiles/sim.dir/comp.c.o
sim.exe: CMakeFiles/sim.dir/build.make
sim.exe: CMakeFiles/sim.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/cygdrive/c/Users/Ethan/CLionProjects/sim/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable sim.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sim.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/sim.dir/build: sim.exe

.PHONY : CMakeFiles/sim.dir/build

CMakeFiles/sim.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/sim.dir/cmake_clean.cmake
.PHONY : CMakeFiles/sim.dir/clean

CMakeFiles/sim.dir/depend:
	cd /cygdrive/c/Users/Ethan/CLionProjects/sim/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /cygdrive/c/Users/Ethan/CLionProjects/sim /cygdrive/c/Users/Ethan/CLionProjects/sim /cygdrive/c/Users/Ethan/CLionProjects/sim/cmake-build-debug /cygdrive/c/Users/Ethan/CLionProjects/sim/cmake-build-debug /cygdrive/c/Users/Ethan/CLionProjects/sim/cmake-build-debug/CMakeFiles/sim.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/sim.dir/depend


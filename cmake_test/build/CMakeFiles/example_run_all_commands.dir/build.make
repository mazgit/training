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


# Produce verbose output by default.
VERBOSE = 1

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
CMAKE_COMMAND = /opt/cmake-3.5.0/bin/cmake

# The command to remove a file.
RM = /opt/cmake-3.5.0/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /sw/agarcha/home/tmp/cmake_test

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /sw/agarcha/home/tmp/cmake_test/build

# Utility rule file for example_run_all_commands.

# Include the progress variables for this target.
include CMakeFiles/example_run_all_commands.dir/progress.make

CMakeFiles/example_run_all_commands: ../\ example_post_process_src_example_c\ example_post_process_src_blah1_c\ example_post_process_src_blah2_c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/sw/agarcha/home/tmp/cmake_test/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "RUN ALL COMMANDS"

example_run_all_commands: CMakeFiles/example_run_all_commands
example_run_all_commands: CMakeFiles/example_run_all_commands.dir/build.make

.PHONY : example_run_all_commands

# Rule to build all files generated by this target.
CMakeFiles/example_run_all_commands.dir/build: example_run_all_commands

.PHONY : CMakeFiles/example_run_all_commands.dir/build

CMakeFiles/example_run_all_commands.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/example_run_all_commands.dir/cmake_clean.cmake
.PHONY : CMakeFiles/example_run_all_commands.dir/clean

CMakeFiles/example_run_all_commands.dir/depend:
	cd /sw/agarcha/home/tmp/cmake_test/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /sw/agarcha/home/tmp/cmake_test /sw/agarcha/home/tmp/cmake_test /sw/agarcha/home/tmp/cmake_test/build /sw/agarcha/home/tmp/cmake_test/build /sw/agarcha/home/tmp/cmake_test/build/CMakeFiles/example_run_all_commands.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/example_run_all_commands.dir/depend


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
CMAKE_SOURCE_DIR = /mnt/d/Dev/c/lab1_crypto

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/d/Dev/c/lab1_crypto/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/lab1_crypto.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/lab1_crypto.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/lab1_crypto.dir/flags.make

CMakeFiles/lab1_crypto.dir/task1.c.o: CMakeFiles/lab1_crypto.dir/flags.make
CMakeFiles/lab1_crypto.dir/task1.c.o: ../task1.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/Dev/c/lab1_crypto/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/lab1_crypto.dir/task1.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/lab1_crypto.dir/task1.c.o   -c /mnt/d/Dev/c/lab1_crypto/task1.c

CMakeFiles/lab1_crypto.dir/task1.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lab1_crypto.dir/task1.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/d/Dev/c/lab1_crypto/task1.c > CMakeFiles/lab1_crypto.dir/task1.c.i

CMakeFiles/lab1_crypto.dir/task1.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lab1_crypto.dir/task1.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/d/Dev/c/lab1_crypto/task1.c -o CMakeFiles/lab1_crypto.dir/task1.c.s

# Object files for target lab1_crypto
lab1_crypto_OBJECTS = \
"CMakeFiles/lab1_crypto.dir/task1.c.o"

# External object files for target lab1_crypto
lab1_crypto_EXTERNAL_OBJECTS =

lab1_crypto: CMakeFiles/lab1_crypto.dir/task1.c.o
lab1_crypto: CMakeFiles/lab1_crypto.dir/build.make
lab1_crypto: CMakeFiles/lab1_crypto.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/d/Dev/c/lab1_crypto/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable lab1_crypto"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lab1_crypto.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/lab1_crypto.dir/build: lab1_crypto

.PHONY : CMakeFiles/lab1_crypto.dir/build

CMakeFiles/lab1_crypto.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/lab1_crypto.dir/cmake_clean.cmake
.PHONY : CMakeFiles/lab1_crypto.dir/clean

CMakeFiles/lab1_crypto.dir/depend:
	cd /mnt/d/Dev/c/lab1_crypto/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/d/Dev/c/lab1_crypto /mnt/d/Dev/c/lab1_crypto /mnt/d/Dev/c/lab1_crypto/cmake-build-debug /mnt/d/Dev/c/lab1_crypto/cmake-build-debug /mnt/d/Dev/c/lab1_crypto/cmake-build-debug/CMakeFiles/lab1_crypto.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/lab1_crypto.dir/depend

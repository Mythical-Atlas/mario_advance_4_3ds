# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.24

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\Ben\Documents\GitHub\mario_advance_4_3ds

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Ben\Documents\GitHub\mario_advance_4_3ds\build

# Include any dependencies generated for this target.
include CMakeFiles/mario.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/mario.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/mario.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mario.dir/flags.make

CMakeFiles/mario.dir/source/camera.cpp.obj: CMakeFiles/mario.dir/flags.make
CMakeFiles/mario.dir/source/camera.cpp.obj: CMakeFiles/mario.dir/includes_CXX.rsp
CMakeFiles/mario.dir/source/camera.cpp.obj: C:/Users/Ben/Documents/GitHub/mario_advance_4_3ds/source/camera.cpp
CMakeFiles/mario.dir/source/camera.cpp.obj: CMakeFiles/mario.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Ben\Documents\GitHub\mario_advance_4_3ds\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/mario.dir/source/camera.cpp.obj"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/mario.dir/source/camera.cpp.obj -MF CMakeFiles\mario.dir\source\camera.cpp.obj.d -o CMakeFiles\mario.dir\source\camera.cpp.obj -c C:\Users\Ben\Documents\GitHub\mario_advance_4_3ds\source\camera.cpp

CMakeFiles/mario.dir/source/camera.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mario.dir/source/camera.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Ben\Documents\GitHub\mario_advance_4_3ds\source\camera.cpp > CMakeFiles\mario.dir\source\camera.cpp.i

CMakeFiles/mario.dir/source/camera.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mario.dir/source/camera.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Ben\Documents\GitHub\mario_advance_4_3ds\source\camera.cpp -o CMakeFiles\mario.dir\source\camera.cpp.s

CMakeFiles/mario.dir/source/game.cpp.obj: CMakeFiles/mario.dir/flags.make
CMakeFiles/mario.dir/source/game.cpp.obj: CMakeFiles/mario.dir/includes_CXX.rsp
CMakeFiles/mario.dir/source/game.cpp.obj: C:/Users/Ben/Documents/GitHub/mario_advance_4_3ds/source/game.cpp
CMakeFiles/mario.dir/source/game.cpp.obj: CMakeFiles/mario.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Ben\Documents\GitHub\mario_advance_4_3ds\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/mario.dir/source/game.cpp.obj"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/mario.dir/source/game.cpp.obj -MF CMakeFiles\mario.dir\source\game.cpp.obj.d -o CMakeFiles\mario.dir\source\game.cpp.obj -c C:\Users\Ben\Documents\GitHub\mario_advance_4_3ds\source\game.cpp

CMakeFiles/mario.dir/source/game.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mario.dir/source/game.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Ben\Documents\GitHub\mario_advance_4_3ds\source\game.cpp > CMakeFiles\mario.dir\source\game.cpp.i

CMakeFiles/mario.dir/source/game.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mario.dir/source/game.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Ben\Documents\GitHub\mario_advance_4_3ds\source\game.cpp -o CMakeFiles\mario.dir\source\game.cpp.s

CMakeFiles/mario.dir/source/graphics.cpp.obj: CMakeFiles/mario.dir/flags.make
CMakeFiles/mario.dir/source/graphics.cpp.obj: CMakeFiles/mario.dir/includes_CXX.rsp
CMakeFiles/mario.dir/source/graphics.cpp.obj: C:/Users/Ben/Documents/GitHub/mario_advance_4_3ds/source/graphics.cpp
CMakeFiles/mario.dir/source/graphics.cpp.obj: CMakeFiles/mario.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Ben\Documents\GitHub\mario_advance_4_3ds\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/mario.dir/source/graphics.cpp.obj"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/mario.dir/source/graphics.cpp.obj -MF CMakeFiles\mario.dir\source\graphics.cpp.obj.d -o CMakeFiles\mario.dir\source\graphics.cpp.obj -c C:\Users\Ben\Documents\GitHub\mario_advance_4_3ds\source\graphics.cpp

CMakeFiles/mario.dir/source/graphics.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mario.dir/source/graphics.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Ben\Documents\GitHub\mario_advance_4_3ds\source\graphics.cpp > CMakeFiles\mario.dir\source\graphics.cpp.i

CMakeFiles/mario.dir/source/graphics.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mario.dir/source/graphics.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Ben\Documents\GitHub\mario_advance_4_3ds\source\graphics.cpp -o CMakeFiles\mario.dir\source\graphics.cpp.s

CMakeFiles/mario.dir/source/levelState.cpp.obj: CMakeFiles/mario.dir/flags.make
CMakeFiles/mario.dir/source/levelState.cpp.obj: CMakeFiles/mario.dir/includes_CXX.rsp
CMakeFiles/mario.dir/source/levelState.cpp.obj: C:/Users/Ben/Documents/GitHub/mario_advance_4_3ds/source/levelState.cpp
CMakeFiles/mario.dir/source/levelState.cpp.obj: CMakeFiles/mario.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Ben\Documents\GitHub\mario_advance_4_3ds\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/mario.dir/source/levelState.cpp.obj"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/mario.dir/source/levelState.cpp.obj -MF CMakeFiles\mario.dir\source\levelState.cpp.obj.d -o CMakeFiles\mario.dir\source\levelState.cpp.obj -c C:\Users\Ben\Documents\GitHub\mario_advance_4_3ds\source\levelState.cpp

CMakeFiles/mario.dir/source/levelState.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mario.dir/source/levelState.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Ben\Documents\GitHub\mario_advance_4_3ds\source\levelState.cpp > CMakeFiles\mario.dir\source\levelState.cpp.i

CMakeFiles/mario.dir/source/levelState.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mario.dir/source/levelState.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Ben\Documents\GitHub\mario_advance_4_3ds\source\levelState.cpp -o CMakeFiles\mario.dir\source\levelState.cpp.s

CMakeFiles/mario.dir/source/main.cpp.obj: CMakeFiles/mario.dir/flags.make
CMakeFiles/mario.dir/source/main.cpp.obj: CMakeFiles/mario.dir/includes_CXX.rsp
CMakeFiles/mario.dir/source/main.cpp.obj: C:/Users/Ben/Documents/GitHub/mario_advance_4_3ds/source/main.cpp
CMakeFiles/mario.dir/source/main.cpp.obj: CMakeFiles/mario.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Ben\Documents\GitHub\mario_advance_4_3ds\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/mario.dir/source/main.cpp.obj"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/mario.dir/source/main.cpp.obj -MF CMakeFiles\mario.dir\source\main.cpp.obj.d -o CMakeFiles\mario.dir\source\main.cpp.obj -c C:\Users\Ben\Documents\GitHub\mario_advance_4_3ds\source\main.cpp

CMakeFiles/mario.dir/source/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mario.dir/source/main.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Ben\Documents\GitHub\mario_advance_4_3ds\source\main.cpp > CMakeFiles\mario.dir\source\main.cpp.i

CMakeFiles/mario.dir/source/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mario.dir/source/main.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Ben\Documents\GitHub\mario_advance_4_3ds\source\main.cpp -o CMakeFiles\mario.dir\source\main.cpp.s

CMakeFiles/mario.dir/source/menuState.cpp.obj: CMakeFiles/mario.dir/flags.make
CMakeFiles/mario.dir/source/menuState.cpp.obj: CMakeFiles/mario.dir/includes_CXX.rsp
CMakeFiles/mario.dir/source/menuState.cpp.obj: C:/Users/Ben/Documents/GitHub/mario_advance_4_3ds/source/menuState.cpp
CMakeFiles/mario.dir/source/menuState.cpp.obj: CMakeFiles/mario.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Ben\Documents\GitHub\mario_advance_4_3ds\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/mario.dir/source/menuState.cpp.obj"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/mario.dir/source/menuState.cpp.obj -MF CMakeFiles\mario.dir\source\menuState.cpp.obj.d -o CMakeFiles\mario.dir\source\menuState.cpp.obj -c C:\Users\Ben\Documents\GitHub\mario_advance_4_3ds\source\menuState.cpp

CMakeFiles/mario.dir/source/menuState.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mario.dir/source/menuState.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Ben\Documents\GitHub\mario_advance_4_3ds\source\menuState.cpp > CMakeFiles\mario.dir\source\menuState.cpp.i

CMakeFiles/mario.dir/source/menuState.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mario.dir/source/menuState.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Ben\Documents\GitHub\mario_advance_4_3ds\source\menuState.cpp -o CMakeFiles\mario.dir\source\menuState.cpp.s

CMakeFiles/mario.dir/source/renderBuffer.cpp.obj: CMakeFiles/mario.dir/flags.make
CMakeFiles/mario.dir/source/renderBuffer.cpp.obj: CMakeFiles/mario.dir/includes_CXX.rsp
CMakeFiles/mario.dir/source/renderBuffer.cpp.obj: C:/Users/Ben/Documents/GitHub/mario_advance_4_3ds/source/renderBuffer.cpp
CMakeFiles/mario.dir/source/renderBuffer.cpp.obj: CMakeFiles/mario.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Ben\Documents\GitHub\mario_advance_4_3ds\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/mario.dir/source/renderBuffer.cpp.obj"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/mario.dir/source/renderBuffer.cpp.obj -MF CMakeFiles\mario.dir\source\renderBuffer.cpp.obj.d -o CMakeFiles\mario.dir\source\renderBuffer.cpp.obj -c C:\Users\Ben\Documents\GitHub\mario_advance_4_3ds\source\renderBuffer.cpp

CMakeFiles/mario.dir/source/renderBuffer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mario.dir/source/renderBuffer.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Ben\Documents\GitHub\mario_advance_4_3ds\source\renderBuffer.cpp > CMakeFiles\mario.dir\source\renderBuffer.cpp.i

CMakeFiles/mario.dir/source/renderBuffer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mario.dir/source/renderBuffer.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Ben\Documents\GitHub\mario_advance_4_3ds\source\renderBuffer.cpp -o CMakeFiles\mario.dir\source\renderBuffer.cpp.s

CMakeFiles/mario.dir/source/renderProgram.cpp.obj: CMakeFiles/mario.dir/flags.make
CMakeFiles/mario.dir/source/renderProgram.cpp.obj: CMakeFiles/mario.dir/includes_CXX.rsp
CMakeFiles/mario.dir/source/renderProgram.cpp.obj: C:/Users/Ben/Documents/GitHub/mario_advance_4_3ds/source/renderProgram.cpp
CMakeFiles/mario.dir/source/renderProgram.cpp.obj: CMakeFiles/mario.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Ben\Documents\GitHub\mario_advance_4_3ds\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/mario.dir/source/renderProgram.cpp.obj"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/mario.dir/source/renderProgram.cpp.obj -MF CMakeFiles\mario.dir\source\renderProgram.cpp.obj.d -o CMakeFiles\mario.dir\source\renderProgram.cpp.obj -c C:\Users\Ben\Documents\GitHub\mario_advance_4_3ds\source\renderProgram.cpp

CMakeFiles/mario.dir/source/renderProgram.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mario.dir/source/renderProgram.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Ben\Documents\GitHub\mario_advance_4_3ds\source\renderProgram.cpp > CMakeFiles\mario.dir\source\renderProgram.cpp.i

CMakeFiles/mario.dir/source/renderProgram.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mario.dir/source/renderProgram.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Ben\Documents\GitHub\mario_advance_4_3ds\source\renderProgram.cpp -o CMakeFiles\mario.dir\source\renderProgram.cpp.s

CMakeFiles/mario.dir/source/window.cpp.obj: CMakeFiles/mario.dir/flags.make
CMakeFiles/mario.dir/source/window.cpp.obj: CMakeFiles/mario.dir/includes_CXX.rsp
CMakeFiles/mario.dir/source/window.cpp.obj: C:/Users/Ben/Documents/GitHub/mario_advance_4_3ds/source/window.cpp
CMakeFiles/mario.dir/source/window.cpp.obj: CMakeFiles/mario.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Ben\Documents\GitHub\mario_advance_4_3ds\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/mario.dir/source/window.cpp.obj"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/mario.dir/source/window.cpp.obj -MF CMakeFiles\mario.dir\source\window.cpp.obj.d -o CMakeFiles\mario.dir\source\window.cpp.obj -c C:\Users\Ben\Documents\GitHub\mario_advance_4_3ds\source\window.cpp

CMakeFiles/mario.dir/source/window.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mario.dir/source/window.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Ben\Documents\GitHub\mario_advance_4_3ds\source\window.cpp > CMakeFiles\mario.dir\source\window.cpp.i

CMakeFiles/mario.dir/source/window.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mario.dir/source/window.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Ben\Documents\GitHub\mario_advance_4_3ds\source\window.cpp -o CMakeFiles\mario.dir\source\window.cpp.s

CMakeFiles/mario.dir/dependencies/glad/src/glad.c.obj: CMakeFiles/mario.dir/flags.make
CMakeFiles/mario.dir/dependencies/glad/src/glad.c.obj: CMakeFiles/mario.dir/includes_C.rsp
CMakeFiles/mario.dir/dependencies/glad/src/glad.c.obj: C:/Users/Ben/Documents/GitHub/mario_advance_4_3ds/dependencies/glad/src/glad.c
CMakeFiles/mario.dir/dependencies/glad/src/glad.c.obj: CMakeFiles/mario.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Ben\Documents\GitHub\mario_advance_4_3ds\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building C object CMakeFiles/mario.dir/dependencies/glad/src/glad.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/mario.dir/dependencies/glad/src/glad.c.obj -MF CMakeFiles\mario.dir\dependencies\glad\src\glad.c.obj.d -o CMakeFiles\mario.dir\dependencies\glad\src\glad.c.obj -c C:\Users\Ben\Documents\GitHub\mario_advance_4_3ds\dependencies\glad\src\glad.c

CMakeFiles/mario.dir/dependencies/glad/src/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mario.dir/dependencies/glad/src/glad.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\Ben\Documents\GitHub\mario_advance_4_3ds\dependencies\glad\src\glad.c > CMakeFiles\mario.dir\dependencies\glad\src\glad.c.i

CMakeFiles/mario.dir/dependencies/glad/src/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mario.dir/dependencies/glad/src/glad.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\Ben\Documents\GitHub\mario_advance_4_3ds\dependencies\glad\src\glad.c -o CMakeFiles\mario.dir\dependencies\glad\src\glad.c.s

# Object files for target mario
mario_OBJECTS = \
"CMakeFiles/mario.dir/source/camera.cpp.obj" \
"CMakeFiles/mario.dir/source/game.cpp.obj" \
"CMakeFiles/mario.dir/source/graphics.cpp.obj" \
"CMakeFiles/mario.dir/source/levelState.cpp.obj" \
"CMakeFiles/mario.dir/source/main.cpp.obj" \
"CMakeFiles/mario.dir/source/menuState.cpp.obj" \
"CMakeFiles/mario.dir/source/renderBuffer.cpp.obj" \
"CMakeFiles/mario.dir/source/renderProgram.cpp.obj" \
"CMakeFiles/mario.dir/source/window.cpp.obj" \
"CMakeFiles/mario.dir/dependencies/glad/src/glad.c.obj"

# External object files for target mario
mario_EXTERNAL_OBJECTS =

C:/Users/Ben/Documents/GitHub/mario_advance_4_3ds/mario.exe: CMakeFiles/mario.dir/source/camera.cpp.obj
C:/Users/Ben/Documents/GitHub/mario_advance_4_3ds/mario.exe: CMakeFiles/mario.dir/source/game.cpp.obj
C:/Users/Ben/Documents/GitHub/mario_advance_4_3ds/mario.exe: CMakeFiles/mario.dir/source/graphics.cpp.obj
C:/Users/Ben/Documents/GitHub/mario_advance_4_3ds/mario.exe: CMakeFiles/mario.dir/source/levelState.cpp.obj
C:/Users/Ben/Documents/GitHub/mario_advance_4_3ds/mario.exe: CMakeFiles/mario.dir/source/main.cpp.obj
C:/Users/Ben/Documents/GitHub/mario_advance_4_3ds/mario.exe: CMakeFiles/mario.dir/source/menuState.cpp.obj
C:/Users/Ben/Documents/GitHub/mario_advance_4_3ds/mario.exe: CMakeFiles/mario.dir/source/renderBuffer.cpp.obj
C:/Users/Ben/Documents/GitHub/mario_advance_4_3ds/mario.exe: CMakeFiles/mario.dir/source/renderProgram.cpp.obj
C:/Users/Ben/Documents/GitHub/mario_advance_4_3ds/mario.exe: CMakeFiles/mario.dir/source/window.cpp.obj
C:/Users/Ben/Documents/GitHub/mario_advance_4_3ds/mario.exe: CMakeFiles/mario.dir/dependencies/glad/src/glad.c.obj
C:/Users/Ben/Documents/GitHub/mario_advance_4_3ds/mario.exe: CMakeFiles/mario.dir/build.make
C:/Users/Ben/Documents/GitHub/mario_advance_4_3ds/mario.exe: CMakeFiles/mario.dir/linklibs.rsp
C:/Users/Ben/Documents/GitHub/mario_advance_4_3ds/mario.exe: CMakeFiles/mario.dir/objects1.rsp
C:/Users/Ben/Documents/GitHub/mario_advance_4_3ds/mario.exe: CMakeFiles/mario.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\Ben\Documents\GitHub\mario_advance_4_3ds\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Linking CXX executable C:\Users\Ben\Documents\GitHub\mario_advance_4_3ds\mario.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\mario.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mario.dir/build: C:/Users/Ben/Documents/GitHub/mario_advance_4_3ds/mario.exe
.PHONY : CMakeFiles/mario.dir/build

CMakeFiles/mario.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\mario.dir\cmake_clean.cmake
.PHONY : CMakeFiles/mario.dir/clean

CMakeFiles/mario.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Ben\Documents\GitHub\mario_advance_4_3ds C:\Users\Ben\Documents\GitHub\mario_advance_4_3ds C:\Users\Ben\Documents\GitHub\mario_advance_4_3ds\build C:\Users\Ben\Documents\GitHub\mario_advance_4_3ds\build C:\Users\Ben\Documents\GitHub\mario_advance_4_3ds\build\CMakeFiles\mario.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/mario.dir/depend

# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.27

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
CMAKE_SOURCE_DIR = C:\Stuff\Programming\Cpp\chess_engine3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Stuff\Programming\Cpp\Sky-Spectre\build

# Include any dependencies generated for this target.
include CMakeFiles/chess_engine.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/chess_engine.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/chess_engine.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/chess_engine.dir/flags.make

CMakeFiles/chess_engine.dir/src/main.cpp.obj: CMakeFiles/chess_engine.dir/flags.make
CMakeFiles/chess_engine.dir/src/main.cpp.obj: CMakeFiles/chess_engine.dir/includes_CXX.rsp
CMakeFiles/chess_engine.dir/src/main.cpp.obj: C:/Stuff/Programming/Cpp/chess_engine3/src/main.cpp
CMakeFiles/chess_engine.dir/src/main.cpp.obj: CMakeFiles/chess_engine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Stuff\Programming\Cpp\Sky-Spectre\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/chess_engine.dir/src/main.cpp.obj"
	C:\Users\awsom\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/chess_engine.dir/src/main.cpp.obj -MF CMakeFiles\chess_engine.dir\src\main.cpp.obj.d -o CMakeFiles\chess_engine.dir\src\main.cpp.obj -c C:\Stuff\Programming\Cpp\chess_engine3\src\main.cpp

CMakeFiles/chess_engine.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/chess_engine.dir/src/main.cpp.i"
	C:\Users\awsom\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Stuff\Programming\Cpp\chess_engine3\src\main.cpp > CMakeFiles\chess_engine.dir\src\main.cpp.i

CMakeFiles/chess_engine.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/chess_engine.dir/src/main.cpp.s"
	C:\Users\awsom\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Stuff\Programming\Cpp\chess_engine3\src\main.cpp -o CMakeFiles\chess_engine.dir\src\main.cpp.s

CMakeFiles/chess_engine.dir/src/display.cpp.obj: CMakeFiles/chess_engine.dir/flags.make
CMakeFiles/chess_engine.dir/src/display.cpp.obj: CMakeFiles/chess_engine.dir/includes_CXX.rsp
CMakeFiles/chess_engine.dir/src/display.cpp.obj: C:/Stuff/Programming/Cpp/chess_engine3/src/display.cpp
CMakeFiles/chess_engine.dir/src/display.cpp.obj: CMakeFiles/chess_engine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Stuff\Programming\Cpp\Sky-Spectre\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/chess_engine.dir/src/display.cpp.obj"
	C:\Users\awsom\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/chess_engine.dir/src/display.cpp.obj -MF CMakeFiles\chess_engine.dir\src\display.cpp.obj.d -o CMakeFiles\chess_engine.dir\src\display.cpp.obj -c C:\Stuff\Programming\Cpp\chess_engine3\src\display.cpp

CMakeFiles/chess_engine.dir/src/display.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/chess_engine.dir/src/display.cpp.i"
	C:\Users\awsom\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Stuff\Programming\Cpp\chess_engine3\src\display.cpp > CMakeFiles\chess_engine.dir\src\display.cpp.i

CMakeFiles/chess_engine.dir/src/display.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/chess_engine.dir/src/display.cpp.s"
	C:\Users\awsom\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Stuff\Programming\Cpp\chess_engine3\src\display.cpp -o CMakeFiles\chess_engine.dir\src\display.cpp.s

CMakeFiles/chess_engine.dir/src/moves.cpp.obj: CMakeFiles/chess_engine.dir/flags.make
CMakeFiles/chess_engine.dir/src/moves.cpp.obj: CMakeFiles/chess_engine.dir/includes_CXX.rsp
CMakeFiles/chess_engine.dir/src/moves.cpp.obj: C:/Stuff/Programming/Cpp/chess_engine3/src/moves.cpp
CMakeFiles/chess_engine.dir/src/moves.cpp.obj: CMakeFiles/chess_engine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Stuff\Programming\Cpp\Sky-Spectre\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/chess_engine.dir/src/moves.cpp.obj"
	C:\Users\awsom\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/chess_engine.dir/src/moves.cpp.obj -MF CMakeFiles\chess_engine.dir\src\moves.cpp.obj.d -o CMakeFiles\chess_engine.dir\src\moves.cpp.obj -c C:\Stuff\Programming\Cpp\chess_engine3\src\moves.cpp

CMakeFiles/chess_engine.dir/src/moves.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/chess_engine.dir/src/moves.cpp.i"
	C:\Users\awsom\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Stuff\Programming\Cpp\chess_engine3\src\moves.cpp > CMakeFiles\chess_engine.dir\src\moves.cpp.i

CMakeFiles/chess_engine.dir/src/moves.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/chess_engine.dir/src/moves.cpp.s"
	C:\Users\awsom\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Stuff\Programming\Cpp\chess_engine3\src\moves.cpp -o CMakeFiles\chess_engine.dir\src\moves.cpp.s

CMakeFiles/chess_engine.dir/src/references.cpp.obj: CMakeFiles/chess_engine.dir/flags.make
CMakeFiles/chess_engine.dir/src/references.cpp.obj: CMakeFiles/chess_engine.dir/includes_CXX.rsp
CMakeFiles/chess_engine.dir/src/references.cpp.obj: C:/Stuff/Programming/Cpp/chess_engine3/src/references.cpp
CMakeFiles/chess_engine.dir/src/references.cpp.obj: CMakeFiles/chess_engine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Stuff\Programming\Cpp\Sky-Spectre\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/chess_engine.dir/src/references.cpp.obj"
	C:\Users\awsom\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/chess_engine.dir/src/references.cpp.obj -MF CMakeFiles\chess_engine.dir\src\references.cpp.obj.d -o CMakeFiles\chess_engine.dir\src\references.cpp.obj -c C:\Stuff\Programming\Cpp\chess_engine3\src\references.cpp

CMakeFiles/chess_engine.dir/src/references.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/chess_engine.dir/src/references.cpp.i"
	C:\Users\awsom\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Stuff\Programming\Cpp\chess_engine3\src\references.cpp > CMakeFiles\chess_engine.dir\src\references.cpp.i

CMakeFiles/chess_engine.dir/src/references.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/chess_engine.dir/src/references.cpp.s"
	C:\Users\awsom\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Stuff\Programming\Cpp\chess_engine3\src\references.cpp -o CMakeFiles\chess_engine.dir\src\references.cpp.s

CMakeFiles/chess_engine.dir/src/evaluation.cpp.obj: CMakeFiles/chess_engine.dir/flags.make
CMakeFiles/chess_engine.dir/src/evaluation.cpp.obj: CMakeFiles/chess_engine.dir/includes_CXX.rsp
CMakeFiles/chess_engine.dir/src/evaluation.cpp.obj: C:/Stuff/Programming/Cpp/chess_engine3/src/evaluation.cpp
CMakeFiles/chess_engine.dir/src/evaluation.cpp.obj: CMakeFiles/chess_engine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Stuff\Programming\Cpp\Sky-Spectre\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/chess_engine.dir/src/evaluation.cpp.obj"
	C:\Users\awsom\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/chess_engine.dir/src/evaluation.cpp.obj -MF CMakeFiles\chess_engine.dir\src\evaluation.cpp.obj.d -o CMakeFiles\chess_engine.dir\src\evaluation.cpp.obj -c C:\Stuff\Programming\Cpp\chess_engine3\src\evaluation.cpp

CMakeFiles/chess_engine.dir/src/evaluation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/chess_engine.dir/src/evaluation.cpp.i"
	C:\Users\awsom\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Stuff\Programming\Cpp\chess_engine3\src\evaluation.cpp > CMakeFiles\chess_engine.dir\src\evaluation.cpp.i

CMakeFiles/chess_engine.dir/src/evaluation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/chess_engine.dir/src/evaluation.cpp.s"
	C:\Users\awsom\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Stuff\Programming\Cpp\chess_engine3\src\evaluation.cpp -o CMakeFiles\chess_engine.dir\src\evaluation.cpp.s

CMakeFiles/chess_engine.dir/src/search.cpp.obj: CMakeFiles/chess_engine.dir/flags.make
CMakeFiles/chess_engine.dir/src/search.cpp.obj: CMakeFiles/chess_engine.dir/includes_CXX.rsp
CMakeFiles/chess_engine.dir/src/search.cpp.obj: C:/Stuff/Programming/Cpp/chess_engine3/src/search.cpp
CMakeFiles/chess_engine.dir/src/search.cpp.obj: CMakeFiles/chess_engine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Stuff\Programming\Cpp\Sky-Spectre\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/chess_engine.dir/src/search.cpp.obj"
	C:\Users\awsom\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/chess_engine.dir/src/search.cpp.obj -MF CMakeFiles\chess_engine.dir\src\search.cpp.obj.d -o CMakeFiles\chess_engine.dir\src\search.cpp.obj -c C:\Stuff\Programming\Cpp\chess_engine3\src\search.cpp

CMakeFiles/chess_engine.dir/src/search.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/chess_engine.dir/src/search.cpp.i"
	C:\Users\awsom\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Stuff\Programming\Cpp\chess_engine3\src\search.cpp > CMakeFiles\chess_engine.dir\src\search.cpp.i

CMakeFiles/chess_engine.dir/src/search.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/chess_engine.dir/src/search.cpp.s"
	C:\Users\awsom\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Stuff\Programming\Cpp\chess_engine3\src\search.cpp -o CMakeFiles\chess_engine.dir\src\search.cpp.s

# Object files for target chess_engine
chess_engine_OBJECTS = \
"CMakeFiles/chess_engine.dir/src/main.cpp.obj" \
"CMakeFiles/chess_engine.dir/src/display.cpp.obj" \
"CMakeFiles/chess_engine.dir/src/moves.cpp.obj" \
"CMakeFiles/chess_engine.dir/src/references.cpp.obj" \
"CMakeFiles/chess_engine.dir/src/evaluation.cpp.obj" \
"CMakeFiles/chess_engine.dir/src/search.cpp.obj"

# External object files for target chess_engine
chess_engine_EXTERNAL_OBJECTS =

chess_engine.exe: CMakeFiles/chess_engine.dir/src/main.cpp.obj
chess_engine.exe: CMakeFiles/chess_engine.dir/src/display.cpp.obj
chess_engine.exe: CMakeFiles/chess_engine.dir/src/moves.cpp.obj
chess_engine.exe: CMakeFiles/chess_engine.dir/src/references.cpp.obj
chess_engine.exe: CMakeFiles/chess_engine.dir/src/evaluation.cpp.obj
chess_engine.exe: CMakeFiles/chess_engine.dir/src/search.cpp.obj
chess_engine.exe: CMakeFiles/chess_engine.dir/build.make
chess_engine.exe: CMakeFiles/chess_engine.dir/compiler_depend.ts
chess_engine.exe: _deps/raylib-build/raylib/libraylib.a
chess_engine.exe: _deps/raylib-build/raylib/external/glfw/src/libglfw3.a
chess_engine.exe: CMakeFiles/chess_engine.dir/linkLibs.rsp
chess_engine.exe: CMakeFiles/chess_engine.dir/objects1.rsp
chess_engine.exe: CMakeFiles/chess_engine.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:\Stuff\Programming\Cpp\Sky-Spectre\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable chess_engine.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\chess_engine.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/chess_engine.dir/build: chess_engine.exe
.PHONY : CMakeFiles/chess_engine.dir/build

CMakeFiles/chess_engine.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\chess_engine.dir\cmake_clean.cmake
.PHONY : CMakeFiles/chess_engine.dir/clean

CMakeFiles/chess_engine.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Stuff\Programming\Cpp\chess_engine3 C:\Stuff\Programming\Cpp\chess_engine3 C:\Stuff\Programming\Cpp\Sky-Spectre\build C:\Stuff\Programming\Cpp\Sky-Spectre\build C:\Stuff\Programming\Cpp\Sky-Spectre\build\CMakeFiles\chess_engine.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/chess_engine.dir/depend


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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/miguevr/GitHub/Practicas_ED/Practica6

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/miguevr/GitHub/Practicas_ED/Practica6/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/image.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/image.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/image.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/image.dir/flags.make

CMakeFiles/image.dir/rutas_aereas/src/imagen.cpp.o: CMakeFiles/image.dir/flags.make
CMakeFiles/image.dir/rutas_aereas/src/imagen.cpp.o: ../rutas_aereas/src/imagen.cpp
CMakeFiles/image.dir/rutas_aereas/src/imagen.cpp.o: CMakeFiles/image.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/miguevr/GitHub/Practicas_ED/Practica6/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/image.dir/rutas_aereas/src/imagen.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/image.dir/rutas_aereas/src/imagen.cpp.o -MF CMakeFiles/image.dir/rutas_aereas/src/imagen.cpp.o.d -o CMakeFiles/image.dir/rutas_aereas/src/imagen.cpp.o -c /home/miguevr/GitHub/Practicas_ED/Practica6/rutas_aereas/src/imagen.cpp

CMakeFiles/image.dir/rutas_aereas/src/imagen.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/image.dir/rutas_aereas/src/imagen.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/miguevr/GitHub/Practicas_ED/Practica6/rutas_aereas/src/imagen.cpp > CMakeFiles/image.dir/rutas_aereas/src/imagen.cpp.i

CMakeFiles/image.dir/rutas_aereas/src/imagen.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/image.dir/rutas_aereas/src/imagen.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/miguevr/GitHub/Practicas_ED/Practica6/rutas_aereas/src/imagen.cpp -o CMakeFiles/image.dir/rutas_aereas/src/imagen.cpp.s

CMakeFiles/image.dir/rutas_aereas/src/imagenES.cpp.o: CMakeFiles/image.dir/flags.make
CMakeFiles/image.dir/rutas_aereas/src/imagenES.cpp.o: ../rutas_aereas/src/imagenES.cpp
CMakeFiles/image.dir/rutas_aereas/src/imagenES.cpp.o: CMakeFiles/image.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/miguevr/GitHub/Practicas_ED/Practica6/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/image.dir/rutas_aereas/src/imagenES.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/image.dir/rutas_aereas/src/imagenES.cpp.o -MF CMakeFiles/image.dir/rutas_aereas/src/imagenES.cpp.o.d -o CMakeFiles/image.dir/rutas_aereas/src/imagenES.cpp.o -c /home/miguevr/GitHub/Practicas_ED/Practica6/rutas_aereas/src/imagenES.cpp

CMakeFiles/image.dir/rutas_aereas/src/imagenES.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/image.dir/rutas_aereas/src/imagenES.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/miguevr/GitHub/Practicas_ED/Practica6/rutas_aereas/src/imagenES.cpp > CMakeFiles/image.dir/rutas_aereas/src/imagenES.cpp.i

CMakeFiles/image.dir/rutas_aereas/src/imagenES.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/image.dir/rutas_aereas/src/imagenES.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/miguevr/GitHub/Practicas_ED/Practica6/rutas_aereas/src/imagenES.cpp -o CMakeFiles/image.dir/rutas_aereas/src/imagenES.cpp.s

CMakeFiles/image.dir/rutas_aereas/src/ruta_aerea.cpp.o: CMakeFiles/image.dir/flags.make
CMakeFiles/image.dir/rutas_aereas/src/ruta_aerea.cpp.o: ../rutas_aereas/src/ruta_aerea.cpp
CMakeFiles/image.dir/rutas_aereas/src/ruta_aerea.cpp.o: CMakeFiles/image.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/miguevr/GitHub/Practicas_ED/Practica6/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/image.dir/rutas_aereas/src/ruta_aerea.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/image.dir/rutas_aereas/src/ruta_aerea.cpp.o -MF CMakeFiles/image.dir/rutas_aereas/src/ruta_aerea.cpp.o.d -o CMakeFiles/image.dir/rutas_aereas/src/ruta_aerea.cpp.o -c /home/miguevr/GitHub/Practicas_ED/Practica6/rutas_aereas/src/ruta_aerea.cpp

CMakeFiles/image.dir/rutas_aereas/src/ruta_aerea.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/image.dir/rutas_aereas/src/ruta_aerea.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/miguevr/GitHub/Practicas_ED/Practica6/rutas_aereas/src/ruta_aerea.cpp > CMakeFiles/image.dir/rutas_aereas/src/ruta_aerea.cpp.i

CMakeFiles/image.dir/rutas_aereas/src/ruta_aerea.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/image.dir/rutas_aereas/src/ruta_aerea.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/miguevr/GitHub/Practicas_ED/Practica6/rutas_aereas/src/ruta_aerea.cpp -o CMakeFiles/image.dir/rutas_aereas/src/ruta_aerea.cpp.s

CMakeFiles/image.dir/rutas_aereas/src/punto.cpp.o: CMakeFiles/image.dir/flags.make
CMakeFiles/image.dir/rutas_aereas/src/punto.cpp.o: ../rutas_aereas/src/punto.cpp
CMakeFiles/image.dir/rutas_aereas/src/punto.cpp.o: CMakeFiles/image.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/miguevr/GitHub/Practicas_ED/Practica6/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/image.dir/rutas_aereas/src/punto.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/image.dir/rutas_aereas/src/punto.cpp.o -MF CMakeFiles/image.dir/rutas_aereas/src/punto.cpp.o.d -o CMakeFiles/image.dir/rutas_aereas/src/punto.cpp.o -c /home/miguevr/GitHub/Practicas_ED/Practica6/rutas_aereas/src/punto.cpp

CMakeFiles/image.dir/rutas_aereas/src/punto.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/image.dir/rutas_aereas/src/punto.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/miguevr/GitHub/Practicas_ED/Practica6/rutas_aereas/src/punto.cpp > CMakeFiles/image.dir/rutas_aereas/src/punto.cpp.i

CMakeFiles/image.dir/rutas_aereas/src/punto.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/image.dir/rutas_aereas/src/punto.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/miguevr/GitHub/Practicas_ED/Practica6/rutas_aereas/src/punto.cpp -o CMakeFiles/image.dir/rutas_aereas/src/punto.cpp.s

CMakeFiles/image.dir/rutas_aereas/src/ruta.cpp.o: CMakeFiles/image.dir/flags.make
CMakeFiles/image.dir/rutas_aereas/src/ruta.cpp.o: ../rutas_aereas/src/ruta.cpp
CMakeFiles/image.dir/rutas_aereas/src/ruta.cpp.o: CMakeFiles/image.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/miguevr/GitHub/Practicas_ED/Practica6/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/image.dir/rutas_aereas/src/ruta.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/image.dir/rutas_aereas/src/ruta.cpp.o -MF CMakeFiles/image.dir/rutas_aereas/src/ruta.cpp.o.d -o CMakeFiles/image.dir/rutas_aereas/src/ruta.cpp.o -c /home/miguevr/GitHub/Practicas_ED/Practica6/rutas_aereas/src/ruta.cpp

CMakeFiles/image.dir/rutas_aereas/src/ruta.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/image.dir/rutas_aereas/src/ruta.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/miguevr/GitHub/Practicas_ED/Practica6/rutas_aereas/src/ruta.cpp > CMakeFiles/image.dir/rutas_aereas/src/ruta.cpp.i

CMakeFiles/image.dir/rutas_aereas/src/ruta.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/image.dir/rutas_aereas/src/ruta.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/miguevr/GitHub/Practicas_ED/Practica6/rutas_aereas/src/ruta.cpp -o CMakeFiles/image.dir/rutas_aereas/src/ruta.cpp.s

CMakeFiles/image.dir/rutas_aereas/src/almacen.cpp.o: CMakeFiles/image.dir/flags.make
CMakeFiles/image.dir/rutas_aereas/src/almacen.cpp.o: ../rutas_aereas/src/almacen.cpp
CMakeFiles/image.dir/rutas_aereas/src/almacen.cpp.o: CMakeFiles/image.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/miguevr/GitHub/Practicas_ED/Practica6/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/image.dir/rutas_aereas/src/almacen.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/image.dir/rutas_aereas/src/almacen.cpp.o -MF CMakeFiles/image.dir/rutas_aereas/src/almacen.cpp.o.d -o CMakeFiles/image.dir/rutas_aereas/src/almacen.cpp.o -c /home/miguevr/GitHub/Practicas_ED/Practica6/rutas_aereas/src/almacen.cpp

CMakeFiles/image.dir/rutas_aereas/src/almacen.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/image.dir/rutas_aereas/src/almacen.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/miguevr/GitHub/Practicas_ED/Practica6/rutas_aereas/src/almacen.cpp > CMakeFiles/image.dir/rutas_aereas/src/almacen.cpp.i

CMakeFiles/image.dir/rutas_aereas/src/almacen.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/image.dir/rutas_aereas/src/almacen.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/miguevr/GitHub/Practicas_ED/Practica6/rutas_aereas/src/almacen.cpp -o CMakeFiles/image.dir/rutas_aereas/src/almacen.cpp.s

# Object files for target image
image_OBJECTS = \
"CMakeFiles/image.dir/rutas_aereas/src/imagen.cpp.o" \
"CMakeFiles/image.dir/rutas_aereas/src/imagenES.cpp.o" \
"CMakeFiles/image.dir/rutas_aereas/src/ruta_aerea.cpp.o" \
"CMakeFiles/image.dir/rutas_aereas/src/punto.cpp.o" \
"CMakeFiles/image.dir/rutas_aereas/src/ruta.cpp.o" \
"CMakeFiles/image.dir/rutas_aereas/src/almacen.cpp.o"

# External object files for target image
image_EXTERNAL_OBJECTS =

libimage.a: CMakeFiles/image.dir/rutas_aereas/src/imagen.cpp.o
libimage.a: CMakeFiles/image.dir/rutas_aereas/src/imagenES.cpp.o
libimage.a: CMakeFiles/image.dir/rutas_aereas/src/ruta_aerea.cpp.o
libimage.a: CMakeFiles/image.dir/rutas_aereas/src/punto.cpp.o
libimage.a: CMakeFiles/image.dir/rutas_aereas/src/ruta.cpp.o
libimage.a: CMakeFiles/image.dir/rutas_aereas/src/almacen.cpp.o
libimage.a: CMakeFiles/image.dir/build.make
libimage.a: CMakeFiles/image.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/miguevr/GitHub/Practicas_ED/Practica6/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX static library libimage.a"
	$(CMAKE_COMMAND) -P CMakeFiles/image.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/image.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/image.dir/build: libimage.a
.PHONY : CMakeFiles/image.dir/build

CMakeFiles/image.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/image.dir/cmake_clean.cmake
.PHONY : CMakeFiles/image.dir/clean

CMakeFiles/image.dir/depend:
	cd /home/miguevr/GitHub/Practicas_ED/Practica6/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/miguevr/GitHub/Practicas_ED/Practica6 /home/miguevr/GitHub/Practicas_ED/Practica6 /home/miguevr/GitHub/Practicas_ED/Practica6/cmake-build-debug /home/miguevr/GitHub/Practicas_ED/Practica6/cmake-build-debug /home/miguevr/GitHub/Practicas_ED/Practica6/cmake-build-debug/CMakeFiles/image.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/image.dir/depend


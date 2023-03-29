cmake_minimum_required(VERSION 3.24.2)
project(mario)

set(CMAKE_CXX_STANDARD 17)

add_executable(mario
	include/audio.hpp
	include/camera.hpp 			source/camera.cpp
	include/collision.hpp
	include/controller.hpp		source/controller.cpp
	include/game.hpp 			source/game.cpp
	include/graphics.hpp 		source/graphics.cpp
	include/levelState.hpp 		source/levelState.cpp
	include/main.hpp 			source/main.cpp
	include/mapState.hpp		source/mapState.cpp
	include/menuState.hpp 		source/menuState.cpp
	include/renderBuffer.hpp 	source/renderBuffer.cpp
	include/renderProgram.hpp 	source/renderProgram.cpp
	include/window.hpp 			source/window.cpp
	dependencies/glad/src/glad.c
)

set_target_properties(mario PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ../ RUNTIME_OUTPUT_DIRECTORY_RELEASE ../)

target_include_directories(mario PRIVATE include PUBLIC dependencies PUBLIC dependencies/glm-0.9.9.8/glm PUBLIC dependencies/glad/include PUBLIC dependencies/SDL2-2.26.4/include)
target_link_directories(mario PUBLIC dependencies/SDL2-2.26.4/lib)
target_link_libraries(mario SDL2main SDL2 psapi)

#target_compile_definitions(mario PUBLIC USE_OPENGL_4_3)

# todo
# animations
# tiles (single sprite?)
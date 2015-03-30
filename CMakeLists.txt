cmake_minimum_required(VERSION 3.1)
project(quick_game_cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

file(GLOB SOURCE_FILES src/*.cpp)
add_executable(quick_game_cpp ${SOURCE_FILES})
target_link_libraries(quick_game_cpp SDL2_ttf.lib)
target_link_libraries(quick_game_cpp SDL2_image.a)
target_link_libraries(quick_game_cpp SDL2main.lib)
target_link_libraries(quick_game_cpp SDL2.lib)
target_link_libraries(quick_game_cpp glew32s.lib)
target_link_libraries(quick_game_cpp opengl32)
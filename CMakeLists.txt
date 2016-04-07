cmake_minimum_required (VERSION 2.8.11)
project (game)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
add_executable(game main.cpp Input.cpp World.cpp Renderer.cpp GameObject.cpp)
target_link_libraries(game sfml-graphics sfml-window sfml-system)
cmake_minimum_required(VERSION 3.2)
project(AI_Project)

# includes cmake/FindSDL2.cmake
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

add_executable(main src/GUI.cpp)

target_link_libraries(main ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})

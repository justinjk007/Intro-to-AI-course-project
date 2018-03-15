cmake_minimum_required(VERSION 3.2)
project(AI_Project)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set compiler specific options
if (MSVC)
  add_compile_options(/MP /Gm- /W3) # Turn on some erros
else()
  add_compile_options(-Wall -Wextra -Wpedantic) # Turn on all errors
endif(MSVC)

# Supply cmake find module for finding SDL2 image when in UNIX
if(UNIX)
  set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")
endif(UNIX)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
if(UNIX)
      include_directories(${SDL2_IMAGE_INCLUDE_DIR})
else(UNIX)
  include_directories(${SDL2_IMAGE_INCLUDE_DIRS})
endif(UNIX)

# Move needed assets
if (MSVC)
  file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)
endif(MSVC)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets
  DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
message("-- Copied all the assets")

add_executable(main src/Simulation.cpp src/AI.cpp src/main.cpp)
add_executable(run_tests tests/tests.cpp)
target_link_libraries(main ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})

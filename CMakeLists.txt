cmake_minimum_required(VERSION 3.2)
project(AI_Project)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set compiler specific options
if (MSVC)
  add_compile_options(/MP /Gm- /W3) # Turn on some erros
else()
  add_compile_options(-Wall -Wextra -Wpedantic -g) # Turn on all errors
endif(MSVC)

# Supply cmake find module for finding SDL2 image when in UNIX
if(UNIX)
  set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")
endif(UNIX)

# SDL Setup
find_package(SDL2 REQUIRED)
message("-- SDL Library was found")
find_package(SDL2_image REQUIRED)
message("-- SDL Image Library was found")
include_directories(${SDL2_INCLUDE_DIRS})
if(UNIX)
  include_directories(${SDL2_IMAGE_INCLUDE_DIR})
else(UNIX)
  include_directories(${SDL2_IMAGE_INCLUDE_DIRS})
endif(UNIX)

# Qt config
find_package(Qt5 COMPONENTS Widgets REQUIRED)
message("-- Qt5 Library was found")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_INCLUDE_BINARY_DIR ON)

# Move needed assets
if (MSVC)
  file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)
endif(MSVC)
if (MSVC)
  file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release)
endif(MSVC)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets
  DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
message("-- Copied all the assets")

add_executable(run_AI_scenes src/Simulation.cpp src/AI.cpp src/Helpers.cpp src/main.cpp src/WorkerThread.cpp)
add_executable(run_tests tests/tests.cpp)
target_link_libraries(run_AI_scenes ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} Qt5::Widgets)

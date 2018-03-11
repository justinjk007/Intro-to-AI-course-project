cmake_minimum_required(VERSION 3.2)
project(AI_Project)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

# Move needed assets
if (MSVC)
  file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)
endif(MSVC)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets
  DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
message("-- Copied all the assets")

add_executable(main src/GUI.cpp)
target_link_libraries(main ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})

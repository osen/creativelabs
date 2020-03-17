cmake_minimum_required(VERSION 2.6)
project(SAMPLE)

include_directories(
  ${PROJECT_SOURCE_DIR}/src
)

add_executable(sample
  src/main.cpp
)
target_link_libraries(sample SDL2 GLEW GL)


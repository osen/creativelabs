cmake_minimum_required(VERSION 2.6)
project(GEPPY)

include_directories(src)

add_library(geppy
  src/geppy/Core.h
  src/geppy/Core.cpp
  src/geppy/Component.h
  src/geppy/Component.cpp
  src/geppy/Entity.h
  src/geppy/Entity.cpp
)
target_link_libraries(geppy SDL2 GLEW GL)

add_executable(sandbox
  src/sandbox/main.cpp
  src/sandbox/TriangleRenderer.cpp
)
target_link_libraries(sandbox geppy)

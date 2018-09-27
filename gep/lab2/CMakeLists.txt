cmake_minimum_required(VERSION 2.6)
project(MYENGINE)

include_directories(
  src
)

add_library(myengine
  src/myengine/Core.cpp
  src/myengine/Entity.cpp
  src/myengine/Component.cpp
)

add_executable(game
  src/game/main.cpp
)

target_link_libraries(game myengine)

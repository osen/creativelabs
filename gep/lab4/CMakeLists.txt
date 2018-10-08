cmake_minimum_required(VERSION 2.6)
project(MYENGINE)

include_directories(
  src
  contrib
)

if(MSVC)
  include_directories(
    contrib/msvc-windows-x86/glew/include
    contrib/msvc-windows-x86/SDL2/include
  )

  link_directories(
    ${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/SDL2/lib
    ${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/glew/lib
  )
else()
  include_directories(
    /usr/X11R6/include
    /usr/local/include
  )

  link_directories(
    /usr/X11R6/lib
    /usr/local/lib
  )
endif()

if(MSVC)
  add_definitions(-DSDL_MAIN_HANDLED)
endif()

add_library(myengine
  src/myengine/Component.cpp
  src/myengine/Core.cpp
  src/myengine/Entity.cpp
  src/myengine/MeshRenderer.cpp
  src/myengine/ShaderProgram.cpp
  src/myengine/VertexBuffer.cpp
  src/myengine/VertexArray.cpp
)

if(MSVC)
  target_link_libraries(myengine
    SDL2 glew32 opengl32
  )
else()
  target_link_libraries(myengine
    SDL2 GLU GLEW GL
  )
endif()

add_executable(game
  src/game/main.cpp
)

target_link_libraries(game myengine)

if(MSVC)
  add_custom_command(TARGET game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      "${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/SDL2/bin/SDL2.dll"
      "$<TARGET_FILE_DIR:game>"
  )

  add_custom_command(TARGET game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      "${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/glew/bin/glew32.dll"
      "$<TARGET_FILE_DIR:game>"
  )
endif()

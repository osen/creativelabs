cmake_minimum_required(VERSION 2.6)
project(TEXTURES)

include_directories(
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
endif()

if(MSVC)
  add_definitions(-DSDL_MAIN_HANDLED)
endif()

add_executable(textures
  src/main.cpp
  src/VertexBuffer.cpp
  src/VertexArray.cpp
  src/ShaderProgram.cpp
  contrib/stb_image/stb_image.cpp
)

if(MSVC)
  target_link_libraries(textures
    SDL2 glew32 opengl32
  )
else()
  target_link_libraries(textures
    SDL2 GLU GLEW GL
  )
endif()

if(MSVC)
  add_custom_command(TARGET textures POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      "${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/SDL2/bin/SDL2.dll"
      "$<TARGET_FILE_DIR:textures>"
  )

  add_custom_command(TARGET textures POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      "${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/glew/bin/glew32.dll"
      "$<TARGET_FILE_DIR:textures>"
  )
endif()
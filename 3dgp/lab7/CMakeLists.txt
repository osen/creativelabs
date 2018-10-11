cmake_minimum_required(VERSION 2.6)
project(CAMERA)

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

add_executable(camera
  src/main.cpp
  src/VertexBuffer.cpp
  src/VertexArray.cpp
  src/ShaderProgram.cpp
  src/Texture.cpp
  contrib/stb_image/stb_image.cpp
)

if(MSVC)
  target_link_libraries(camera
    SDL2 glew32 opengl32
  )
else()
  target_link_libraries(camera
    SDL2 GLU GLEW GL
  )
endif()

if(MSVC)
  add_custom_command(TARGET camera POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      "${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/SDL2/bin/SDL2.dll"
      "$<TARGET_FILE_DIR:camera>"
  )

  add_custom_command(TARGET camera POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      "${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/glew/bin/glew32.dll"
      "$<TARGET_FILE_DIR:camera>"
  )
endif()

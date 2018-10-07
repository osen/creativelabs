cmake_minimum_required(VERSION 2.6)
project(MODEL)

include_directories(
  contrib
)

if(MSVC)
  include_directories(
    contrib/msvc-windows-x86/glew/include
    contrib/msvc-windows-x86/SDL2/include
    contrib/msvc-windows-x86/SDL2_image/include
  )
else()
  include_directories(
    /usr/local/include
    /usr/X11R6/include
  )

  link_directories(
    /usr/local/lib
    /usr/X11R6/lib
  )
endif()

add_executable(model
  src/main.cpp
  src/VertexBuffer.cpp
  src/VertexArray.cpp
  src/ShaderProgram.cpp
  src/Texture.cpp
  contrib/stb_image/stb_image.cpp
)

target_link_libraries(model
  SDL2 GLU GLEW GL
)

#add_custom_command(TARGET triangle POST_BUILD
#  COMMAND ${CMAKE_COMMAND} -E copy_if_different
#    ${CONTRIB_SHARED_LIBRARIES}
#    $<TARGET_FILE_DIR:triangle>
#)

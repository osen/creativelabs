cmake_minimum_required(VERSION 2.6)
project(TEXTURES)

include_directories(
  contrib
)

if(MSVC)
  include_directories(
    contrib/msvc-windows-x86/glew/include
    contrib/msvc-windows-x86/SDL2/include
    contrib/msvc-windows-x86/SDL2_image/include
  )
endif()

add_executable(textures
  src/main.cpp
  src/VertexBuffer.cpp
  src/VertexArray.cpp
  src/ShaderProgram.cpp
  contrib/stb_image/stb_image.cpp
)

target_link_libraries(textures
  SDL2 GLU GLEW GL
)

#add_custom_command(TARGET triangle POST_BUILD
#  COMMAND ${CMAKE_COMMAND} -E copy_if_different
#    ${CONTRIB_SHARED_LIBRARIES}
#    $<TARGET_FILE_DIR:triangle>
#)

cmake_minimum_required(VERSION 3.12)

project(Pacman2D)

find_package(OpenGL REQUIRED)

add_subdirectory(glad)
add_subdirectory(glfw)
add_subdirectory(glm)

add_executable(Pacman2D
main.cpp
"shaders/shader.h"
"shaders/shaderpac.h"
"headers/Renderer.h"
"headers/Map.h" 
"headers/Map.cpp"
"headers/Libraries.h" 
"headers/Wall.h"
"headers/Wall.cpp"
"headers/Pellets.h"
"headers/Pellets.cpp"
"headers/Pacman.h" 
"headers/Pacman.cpp" 
"headers/Window.h" 
"headers/Window.cpp" 
"headers/Translate.h"
"headers/Translate.cpp"
"headers/Ghost.h"
"headers/Ghost.cpp" 
)

target_link_libraries(Pacman2D glfw glad glm OpenGL::GL)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/level0
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})


 target_include_directories(${PROJECT_NAME}
  PRIVATE
  ${CMAKE_SOURCE_DIR}/stb/include)

target_compile_definitions(${PROJECT_NAME}
  PRIVATE
  STB_IMAGE_IMPLEMENTATION)






add_custom_command(
  TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy
  ${CMAKE_CURRENT_SOURCE_DIR}/resources/textures/pacman.png
  ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources/textures/pacman.png)

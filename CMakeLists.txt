cmake_minimum_required(VERSION 3.20)
project(Cubic)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} src/main.cpp src/CubicGame.cpp include/CubicGame.h src/Texture2D.cpp include/Texture2D.h src/Shader.cpp include/Shader.h src/SpriteRenderer.cpp include/SpriteRenderer.h)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(lib/GLFW/)
target_link_libraries(${PROJECT_NAME} glfw)

add_subdirectory(lib/glad/)
target_link_libraries(${PROJECT_NAME} glad)

add_subdirectory(lib/glm)
target_link_libraries(${PROJECT_NAME} glm)

include_directories(lib/)

file(COPY Content/ DESTINATION Content/)
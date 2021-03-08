cmake_minimum_required(VERSION 3.3)
project(crinemaft)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/build/debug")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

find_package(glfw3 REQUIRED)

include_directories(${OPENGL_INCLUDE_DIR})

file(GLOB_RECURSE SOURCES src/*.cpp)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(CMAKE_CXX_FLAGS "-framework OpenGL -Wno-unused-command-line-argument")
else()
    find_package(OpenGL REQUIRED)
endif()

add_executable(crinemaft ${SOURCES})
target_include_directories(crinemaft PRIVATE src)
if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    target_link_libraries(crinemaft ${OPENGL_gl_LIBRARY} glfw)
else()
    target_link_libraries(crinemaft ${OPENGL_gl_LIBRARY} glfw OpenGL)
endif()

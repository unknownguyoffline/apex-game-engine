cmake_minimum_required(VERSION 3.16.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TOOL Debug)

project(engineWorkspace)

add_subdirectory(project)
add_subdirectory(engine)

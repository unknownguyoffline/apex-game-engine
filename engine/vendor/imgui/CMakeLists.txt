cmake_minimum_required(VERSION 3.16.0)

project(imgui)

include_directories(${PROJECT_SOURCE_DIR})

file(GLOB source
	"${PROJECT_SOURCE_DIR}/*.cpp"
	"${PROJECT_SOURCE_DIR}/backends/imgui_impl_glfw.cpp"
	"${PROJECT_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp"
	)

add_library(imgui STATIC ${source})

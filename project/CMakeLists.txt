cmake_minimum_required(VERSION 3.16.0)

set(CMAKE_BUILD_TYPE Debug)

project(app)

include_directories(${PROJECT_SOURCE_DIR}/../engine/)
include_directories(${PROJECT_SOURCE_DIR}/editor/imgui)
include_directories(${PROJECT_SOURCE_DIR}/../engine/vendor/glm/)
include_directories(${PROJECT_SOURCE_DIR}/../engine/vendor/glad/include/)
include_directories(${PROJECT_SOURCE_DIR}/../engine/vendor/glfw/include)
include_directories(${PROJECT_SOURCE_DIR}/../engine/vendor/glad/include)
include_directories("C:/msys64/clang64/include/c++/13.2.0/")

file(GLOB source
	"${PROJECT_SOURCE_DIR}/editor/*.cpp"
	"${PROJECT_SOURCE_DIR}/editor/imgui/*.cpp"
	"${PROJECT_SOURCE_DIR}/editor/imgui/backends/imgui_impl_glfw*.cpp"
	"${PROJECT_SOURCE_DIR}/editor/imgui/backends/imgui_impl_opengl3*.cpp"
	"${PROJECT_SOURCE_DIR}/editor/imgui/misc/cpp/*.cpp"
	)

add_executable(app ${source})
target_link_libraries(app engine)

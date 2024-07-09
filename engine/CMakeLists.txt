cmake_minimum_required(VERSION 3.16.0)

set(CMAKE_BUILD_TYPE Debug)
project(engine)

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/vendor/json/include)
add_subdirectory(vendor)

file(GLOB source
	"${PROJECT_SOURCE_DIR}/core/*.cpp"
	"${PROJECT_SOURCE_DIR}/renderer/*.cpp"
	"${PROJECT_SOURCE_DIR}/utility/*.cpp"
	"${PROJECT_SOURCE_DIR}/platform/linux/*.cpp"
	"${PROJECT_SOURCE_DIR}/platform/opengl/*.cpp"
	"${PROJECT_SOURCE_DIR}/assets/*.cpp"
	"${PROJECT_SOURCE_DIR}/entity_component_system/*.cpp"
	)

add_library(engine STATIC ${source})
target_link_libraries(engine glfw)
target_link_libraries(engine GL)
target_link_libraries(engine stb_image)

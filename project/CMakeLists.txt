cmake_minimum_required(VERSION 3.16.0)

set(CMAKE_BUILD_TYPE Debug)

project(app)

include_directories(${PROJECT_SOURCE_DIR}/../engine/)
include_directories(/usr/include/imgui)
include_directories(/usr/include/stb)

file(GLOB source
	"${PROJECT_SOURCE_DIR}/test/*.cpp"
	)

add_executable(app ${source})
target_link_libraries(app engine)
target_link_libraries(app imgui)
target_link_libraries(app stb)

cmake_minimum_required(VERSION 3.21)

project(SkyrimStartupMessageBox VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCE_FILES src/*.cpp src/*.h)

find_package(CommonLibSSE CONFIG REQUIRED)
add_commonlibsse_plugin(${PROJECT_NAME} SOURCES ${SOURCE_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "!!!SkyrimStartupMessageBox")
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)
target_precompile_headers(${PROJECT_NAME} PUBLIC src/PCH.h)

add_custom_command(
	TARGET "${PROJECT_NAME}"
	POST_BUILD
	COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_FILE:${PROJECT_NAME}>" "${PROJECT_SOURCE_DIR}/SKSE/Plugins/$<TARGET_FILE_NAME:${PROJECT_NAME}>"
	COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_PDB_FILE:${PROJECT_NAME}>" "${PROJECT_SOURCE_DIR}/SKSE/Plugins/$<TARGET_PDB_FILE_NAME:${PROJECT_NAME}>"
	VERBATIM
)

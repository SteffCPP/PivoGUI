cmake_minimum_required(VERSION 3.16)
project(EGUI LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

file(GLOB_RECURSE EGUI_SOURCES
    src/*.cpp
)
list(FILTER EGUI_SOURCES EXCLUDE REGEX ".*main\\.cpp$")

add_library(EGUI SHARED ${EGUI_SOURCES})

include_directories(
    ${PROJECT_SOURCE_DIR}/inc
    ${PROJECT_SOURCE_DIR}/inc/EGUI
	${PROJECT_SOURCE_DIR}/inc/SDL3
)

file(GLOB LIB_FILES "${PROJECT_SOURCE_DIR}/lib/*.a")

link_directories(${CMAKE_SOURCE_DIR}/lib)
target_link_libraries(EGUI PRIVATE ${LIB_FILES})

add_executable(main src/main.cpp)

target_link_libraries(main PRIVATE EGUI)
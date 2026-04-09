cmake_minimum_required(VERSION 3.16)

project(EGUI LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

find_package(SDL3 REQUIRED)

file(GLOB_RECURSE EGUI_SOURCES
    src/*.cpp
)

list(FILTER EGUI_SOURCES EXCLUDE REGEX ".*main\\.cpp$")

add_library(EGUI SHARED ${EGUI_SOURCES})

target_include_directories(EGUI PUBLIC
    ${PROJECT_SOURCE_DIR}/inc
    ${PROJECT_SOURCE_DIR}/inc/EGUI
)

target_link_libraries(EGUI
    PRIVATE SDL3::SDL3
)

add_executable(main src/main.cpp)

target_link_libraries(main
    PRIVATE EGUI
)
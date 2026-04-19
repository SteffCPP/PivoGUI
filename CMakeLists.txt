cmake_minimum_required(VERSION 3.16)

project(EGUI VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

find_package(SDL3 REQUIRED)
find_package(SDL3_mixer REQUIRED)
find_package(SDL3_ttf REQUIRED)
find_package(SDL3_image REQUIRED)

file(GLOB_RECURSE EGUI_SOURCES CONFIGURE_DEPENDS src/*.cpp)

add_library(EGUI SHARED ${EGUI_SOURCES})

target_include_directories(EGUI PUBLIC ${PROJECT_SOURCE_DIR}/inc/EGUI)

target_link_libraries(EGUI PRIVATE
    SDL3::SDL3
    SDL3_image::SDL3_image
    SDL3_ttf::SDL3_ttf
    SDL3_mixer::SDL3_mixer
)
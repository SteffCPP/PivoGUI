cmake_minimum_required(VERSION 3.16)

project(EGUI VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/test/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

find_package(SDL3 REQUIRED)
find_package(SDL3_mixer REQUIRED)
find_package(SDL3_ttf REQUIRED)
find_package(SDL3_image REQUIRED)

file(GLOB_RECURSE EGUI_SOURCES CONFIGURE_DEPENDS src/*.cpp)
file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS test/*.cpp)

add_library(EGUI SHARED ${EGUI_SOURCES})

target_include_directories(EGUI PUBLIC
    ${PROJECT_SOURCE_DIR}/inc
    ${PROJECT_SOURCE_DIR}/inc/EGUI
)

target_link_libraries(EGUI PRIVATE
    SDL3::SDL3
    SDL3_image::SDL3_image
    SDL3_ttf::SDL3_ttf
    SDL3_mixer::SDL3_mixer
)

set_target_properties(EGUI PROPERTIES
    WINDOWS_EXPORT_ALL_SYMBOLS ON
)

foreach(SOURCE_FILE ${TEST_SOURCES})

    get_filename_component(EXECUTABLE_NAME ${SOURCE_FILE} NAME_WE)

    add_executable(${EXECUTABLE_NAME} ${SOURCE_FILE})

    target_link_libraries(${EXECUTABLE_NAME} PRIVATE EGUI)

    if(UNIX AND NOT APPLE)
        set_target_properties(${EXECUTABLE_NAME} PROPERTIES
            BUILD_RPATH "$ORIGIN"
        )
    elseif(APPLE)
        set_target_properties(${EXECUTABLE_NAME} PROPERTIES
            BUILD_RPATH "@loader_path"
        )
    endif()

    if(WIN32)
        foreach(dep
            SDL3::SDL3
            SDL3_image::SDL3_image
            SDL3_ttf::SDL3_ttf
            SDL3_mixer::SDL3_mixer
            EGUI
        )
            add_custom_command(
                TARGET ${EXECUTABLE_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                    "$<TARGET_FILE:${dep}>"
                    "$<TARGET_FILE_DIR:${EXECUTABLE_NAME}>"
                VERBATIM
            )
        endforeach()
    endif()

endforeach()
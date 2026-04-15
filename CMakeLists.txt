cmake_minimum_required(VERSION 3.16)

project(EGUI LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/test/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

foreach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_SOURCE_DIR}/test/bin)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_SOURCE_DIR}/lib)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_SOURCE_DIR}/lib)
endforeach()

include(FetchContent)

function(add_dependency name repo tag)
    FetchContent_Declare(
        ${name}
        GIT_REPOSITORY ${repo}
        GIT_TAG ${tag}
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
    )
    FetchContent_MakeAvailable(${name})
endfunction()

add_dependency(SDL3 https://github.com/libsdl-org/SDL.git release-3.4.4)

set(SDL3IMAGE_INSTALL OFF CACHE BOOL "" FORCE)
set(SDL3IMAGE_VENDORED ON CACHE BOOL "" FORCE)

set(SDL3IMAGE_PNG ON CACHE BOOL "" FORCE)
set(SDL3IMAGE_JPG ON CACHE BOOL "" FORCE)
set(SDL3IMAGE_WEBP ON CACHE BOOL "" FORCE)
set(SDL3IMAGE_TIF ON CACHE BOOL "" FORCE)

add_dependency(SDL3_image https://github.com/libsdl-org/SDL_image.git release-3.4.2)

set(SDL3TTF_INSTALL OFF CACHE BOOL "" FORCE)
set(SDL3TTF_VENDORED ON CACHE BOOL "" FORCE)

add_dependency(SDL3_ttf https://github.com/libsdl-org/SDL_ttf.git release-3.2.2)

set(SDL3MIXER_INSTALL OFF CACHE BOOL "" FORCE)
set(SDL3MIXER_VENDORED ON CACHE BOOL "" FORCE)

add_dependency(SDL3_mixer https://github.com/libsdl-org/SDL_mixer.git release-3.2.0)

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
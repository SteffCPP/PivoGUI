cmake_minimum_required(VERSION 3.16)

project(EGUI LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_RPATH_USE_ORIGIN TRUE)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

include(FetchContent)

function(include_dependency libName gitURL gitTag)
    fetchcontent_declare(${libName}
        GIT_REPOSITORY ${gitURL}
        GIT_TAG ${gitTag}
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
    )
endfunction()

find_package(SDL3 QUIET)

if(NOT SDL3_FOUND)
    message(STATUS "Getting SDL3 from Github")
    include_dependency(SDL3 https://github.com/libsdl-org/SDL.git release-3.4.4)
	fetchcontent_makeavailable(SDL3)
else()
    message(STATUS "Using local SDL3")
endif()

file(GLOB_RECURSE EGUI_SOURCES CONFIGURE_DEPENDS src/*.cpp)
file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS test/*.cpp)

add_library(EGUI SHARED ${EGUI_SOURCES})
target_include_directories(EGUI PUBLIC
    ${PROJECT_SOURCE_DIR}/inc
    ${PROJECT_SOURCE_DIR}/inc/EGUI
)
target_include_directories(EGUI PUBLIC ${SDL3_INCLUDE_DIRS})
target_link_libraries(EGUI PRIVATE SDL3::SDL3)


foreach(SOURCE_FILE ${TEST_SOURCES})
    get_filename_component(EXECUTABLE_NAME ${SOURCE_FILE} NAME_WE)
    add_executable(${EXECUTABLE_NAME} ${SOURCE_FILE})
	set_target_properties(${EXECUTABLE_NAME} PROPERTIES
		BUILD_RPATH "$ORIGIN"
		INSTALL_RPATH "$ORIGIN"
	)
	target_link_libraries(${EXECUTABLE_NAME} PRIVATE EGUI)

	if(WIN32)
		add_custom_command(
			TARGET ${EXECUTABLE_NAME} POST_BUILD
			COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_FILE:SDL3::SDL3>" "$<TARGET_FILE_DIR:${EXECUTABLE_NAME}>"
			VERBATIM
		)
	endif()
endforeach()



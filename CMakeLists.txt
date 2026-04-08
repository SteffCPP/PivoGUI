cmake_minimum_required(VERSION 3.28)

project(EasyGUI LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 🔍 Cerca SOLO moduli
file(GLOB_RECURSE MODULE_FILES
    CONFIGURE_DEPENDS
    inc/*.cppm inc/*.ixx inc/*.mpp
    src/*.cppm src/*.ixx src/*.mpp
    lib/*.cppm lib/*.ixx lib/*.mpp
)

# Debug
message(STATUS "MODULE FILES: ${MODULE_FILES}")

# 🚨 Errore se non trova nulla
if(NOT MODULE_FILES)
    message(FATAL_ERROR "Nessun modulo trovato (.cppm/.ixx/.mpp)")
endif()

# 📚 Libreria (solo moduli)
add_library(EGUI STATIC)

target_sources(EGUI
    PUBLIC
        FILE_SET cxx_modules TYPE CXX_MODULES FILES
            ${MODULE_FILES}
)

target_include_directories(EGUI PUBLIC inc)

target_compile_options(EGUI PRIVATE -fmodules-ts)

# 🚀 Executable (usa main.cpp)
add_executable(EGUI_app src/main.cpp)

target_link_libraries(EGUI_app PRIVATE EGUI)

target_compile_options(EGUI_app PRIVATE -fmodules-ts)
cmake_minimum_required(VERSION 3.1)
project(lodashcpp VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)



# add_library(lodashcpp STATIC lodash.hpp)
# set_target_properties(lodashcpp PROPERTIES LINKER_LANGUAGE CXX)
add_library(lodashcpp INTERFACE)
target_sources(lodashcpp INTERFACE lodash.hpp) 

set(HEADER_BASE "${CMAKE_CURRENT_SOURCE_DIR}")

set(config_install_dir "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}")
set(include_install_dir "${CMAKE_INSTALL_INCLUDEDIR}")
set(targets_export_name "${PROJECT_NAME}Targets")

install(
    DIRECTORY "${HEADER_BASE}/${PROJECT_NAME}"
    DESTINATION "${include_install_dir}"
)

export(PACKAGE ${PROJECT_NAME})

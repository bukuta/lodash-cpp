cmake_minimum_required(VERSION 3.1)
project(lodash)

enable_testing()

file(STRINGS "${PROJECT_SOURCE_DIR}/include/lodash.hpp" lodash_version_defines
     REGEX "#define {lodash__VERSION_(MAJOR|MINOR|PATCH)")
foreach(ver ${lodash_version_defines})
    if(ver MATCHES "#define {lodash__VERSION_(MAJOR|MINOR|PATCH) +([^ ]+)$")
        set({lodash__VERSION_${CMAKE_MATCH_1} "${CMAKE_MATCH_2}" CACHE INTERNAL "")
    endif()
endforeach()
set(VERSION ${lodash__VERSION_MAJOR}.${lodash__VERSION_MINOR}.${lodash__VERSION_PATCH})

# set(VERSION "1.2.0")

option(lodash_BUILD_EXAMPLES "Set to ON to build examples" ON)
option(lodash_BUILD_TESTS "Set to ON to build tests" OFF)

# request c++11 without gnu extension for the whole project and enable more warnings
if (lodash_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD ${lodash_CXX_STANDARD})
else()
  set(CMAKE_CXX_STANDARD 11)
endif()

set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W2")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "[Cc]lang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -Wshadow")
endif()

add_library(lodash INTERFACE)

target_include_directories(lodash INTERFACE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    )

include(CMakePackageConfigHelpers)
set(lodash_CMAKE_DIR "lib/cmake/lodash" CACHE STRING
  "Installation directory for cmake files, relative to ${CMAKE_INSTALL_PREFIX}.")
set(version_config "${PROJECT_BINARY_DIR}/lodash-config-version.cmake")
set(project_config "${PROJECT_BINARY_DIR}/lodash-config.cmake")
set(targets_export_name lodash-targets)

# Generate the version, config and target files into the build directory.
write_basic_package_version_file(
    ${version_config}
    VERSION ${VERSION}
    COMPATIBILITY AnyNewerVersion)
configure_package_config_file(
    ${PROJECT_SOURCE_DIR}/lodash-config.cmake.in
    ${project_config}
    INSTALL_DESTINATION ${lodash_CMAKE_DIR})
export(TARGETS lodash NAMESPACE lodash::
    FILE ${PROJECT_BINARY_DIR}/${targets_export_name}.cmake)

# Install version, config and target files.
install(
    FILES ${project_config} ${version_config}
    DESTINATION ${lodash_CMAKE_DIR})
install(EXPORT ${targets_export_name} DESTINATION ${lodash_CMAKE_DIR}
    NAMESPACE lodash::)

# Install the header file and export the target
install(TARGETS lodash EXPORT ${targets_export_name} DESTINATION lib)
install(FILES ${PROJECT_SOURCE_DIR}/include/lodash.hpp DESTINATION include)

#add_subdirectory(src)
#add_subdirectory(test)

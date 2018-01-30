cmake_minimum_required(VERSION 3.10)
project(tdsp CXX)

# Set hard requirements for C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Warn on CMake API deprecations
set(CMAKE_WARN_DEPRECATED ON)

# Add the module directory to the list of paths
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/CMakeModules")

# Include boost
find_package(Boost 1.57.0 REQUIRED COMPONENTS system)
add_library(boost INTERFACE IMPORTED)
set_property(TARGET boost PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIRS})
set_property(TARGET boost PROPERTY INTERFACE_SYSTEM_INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIRS})
set_property(TARGET boost PROPERTY INTERFACE_LINK_LIBRARIES ${Boost_LIBRARIES})

enable_testing(true)
add_subdirectory(externals)
add_subdirectory(tdsp-lib)
add_subdirectory(tdsp-asm)
add_subdirectory(tests)

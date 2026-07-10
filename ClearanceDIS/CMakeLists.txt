# Standalone CMake build for the ClearanceDIS module. Lets the pure-C++
# wire-format library compile + test without an Unreal Engine install
# on the machine - so the CI pipeline can be a plain Windows / Linux
# runner instead of a UE-provisioned VM. Same source files are also
# consumed by the UE plugin via ClearanceDIS.Build.cs when running
# inside the editor. - TripleA
#
# Build recipe (from repo root):
#   cd Plugins/ClearanceSim/Source/ClearanceDIS
#   cmake -S . -B build -G Ninja
#   cmake --build build
#   ctest --test-dir build --output-on-failure

cmake_minimum_required(VERSION 3.15)
project(ClearanceDIS
    LANGUAGES CXX
    DESCRIPTION "IEEE 1278.1 DIS wire-format library extracted from CLEARANCE"
    VERSION 1.0.0
)

# Pure C++17 - matches the UE plugin's minimum standard. Nothing here
# reaches for C++20 features. - TripleA
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Warnings-as-errors on for the wire-format code: the library is the
# published spec-conformant surface, drift is not tolerated. Third-party
# code (there is none here) would be excluded. - TripleA
if(MSVC)
    add_compile_options(/W4 /WX /permissive-)
else()
    add_compile_options(-Wall -Wextra -Werror -pedantic)
endif()

# --- Library target -----------------------------------------------------
# Deliberately does NOT include ClearanceDISModule.cpp - that file has
# a UE-specific IMPLEMENT_MODULE bootstrap and only makes sense inside
# the editor. The wire-format code compiles standalone. - TripleA
add_library(ClearanceDIS STATIC
    Private/DISWireFormat.cpp
)

target_include_directories(ClearanceDIS
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Public>
        $<INSTALL_INTERFACE:include>
)

# Static build - the header's CLEARANCEDIS_API macro would resolve to
# dllimport on MSVC by default, which breaks static-lib linking.
# Force the macro empty for both the library compilation and every
# consumer that links against this target. - TripleA
target_compile_definitions(ClearanceDIS PUBLIC CLEARANCEDIS_API=)

# --- Tests --------------------------------------------------------------
enable_testing()
add_subdirectory(test)

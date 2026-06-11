cmake_minimum_required(VERSION 3.16)
project(left_behind LANGUAGES CXX)

set(CMAKE_OSX_SYSROOT
        "/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk"
        CACHE PATH "" FORCE
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Remove conflicting CommandLineTools SDK path that clashes with Xcode sysroot
if(APPLE)
    list(REMOVE_ITEM CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES
        "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include"
        "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/c++/v1")
    set(CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES
        "${CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES}" CACHE STRING "" FORCE)
endif()

set(CMAKE_OSX_ARCHITECTURES arm64)
set(CMAKE_OSX_DEPLOYMENT_TARGET "15.3.2")

find_package(spdlog REQUIRED)
find_package(fmt REQUIRED)
find_package(nlohmann_json REQUIRED)
# cpr pulls in FindCURL; without this, CURL often resolves to Command Line Tools SDK
# and adds -isystem .../CommandLineTools/.../usr/include, which breaks libc++ with Xcode -isysroot.
if(APPLE)
    unset(CURL_INCLUDE_DIR CACHE)
    unset(CURL_LIBRARY CACHE)
    unset(CURL_LIBRARY_RELEASE CACHE)
    set(CURL_ROOT "${CMAKE_OSX_SYSROOT}/usr" CACHE PATH "" FORCE)
endif()
find_package(cpr REQUIRED)
find_package(pugixml REQUIRED)
find_package(GTest REQUIRED)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS src/*.cpp)
file(GLOB_RECURSE TEST_FILES CONFIGURE_DEPENDS unit_tests/*.cpp)
file(GLOB_RECURSE UTILS_SRC CONFIGURE_DEPENDS utils/*.cpp)

set(PROJECT_SOURCES ""
        header/poker.hpp
        header/itinerary.hpp)
foreach(file ${SRC_FILES})
    if(NOT file MATCHES ".*main\\.cpp$")
        list(APPEND PROJECT_SOURCES ${file})
    endif()
endforeach()

add_library(project_lib
        ${PROJECT_SOURCES}
        ${UTILS_SRC}
)

target_include_directories(project_lib
        PUBLIC
        ${CMAKE_SOURCE_DIR}/header
        ${CMAKE_SOURCE_DIR}/utils
)

# Homebrew jako SYSTEM (żeby nie mieszało warningów i kolejności)
target_include_directories(project_lib
        SYSTEM PUBLIC
        /opt/homebrew/include
)

target_link_libraries(project_lib
        PUBLIC
        spdlog::spdlog
        fmt::fmt
        cpr::cpr
        nlohmann_json::nlohmann_json
        pugixml::pugixml
)

if(EXISTS "${CMAKE_SOURCE_DIR}/src/main.cpp")
    add_executable(left_behind src/main.cpp)
    target_link_libraries(left_behind PRIVATE project_lib)
    target_compile_definitions(left_behind PRIVATE "CONFIG_PATH=\"config/config.json\"")
endif()

enable_testing()
add_executable(test_environment ${TEST_FILES})
target_link_libraries(test_environment PRIVATE project_lib GTest::gtest_main)
add_test(NAME AllTests COMMAND test_environment)

# Dedicated test target for LRU v2 to avoid stale discovery/cache confusion.
if(EXISTS "${CMAKE_SOURCE_DIR}/unit_tests/test_lru_cache_v2.cpp")
    add_executable(lru_cache_v2_tests
            unit_tests/test_lru_cache_v2.cpp)
    target_link_libraries(lru_cache_v2_tests PRIVATE project_lib GTest::gtest_main)
    add_test(NAME LRUCacheV2TestsOnly COMMAND lru_cache_v2_tests)
endif()
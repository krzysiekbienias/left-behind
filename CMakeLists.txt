cmake_minimum_required(VERSION 3.16)
project(left_behind LANGUAGES CXX)

set(CMAKE_OSX_SYSROOT
        "/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk"
        CACHE PATH "" FORCE
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_OSX_ARCHITECTURES arm64)
set(CMAKE_OSX_DEPLOYMENT_TARGET "15.3.2")

find_package(spdlog REQUIRED)
find_package(fmt REQUIRED)
find_package(nlohmann_json REQUIRED)
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
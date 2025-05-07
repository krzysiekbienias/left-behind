cmake_minimum_required(VERSION 3.16)
project(left_behind)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_XCODE_GENERATE_SCHEME TRUE)
set(CMAKE_OSX_ARCHITECTURES arm64)
set(CMAKE_OSX_DEPLOYMENT_TARGET "15.3.2")

set(CMAKE_CONFIGURE_DEPENDS_NEW OFF CACHE INTERNAL "" FORCE)

include_directories(SYSTEM /opt/homebrew/include)

# Link libraries dynamically
find_package(spdlog REQUIRED)
find_package(fmt REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(cpr REQUIRED)


# === File Discovery ===
file(GLOB_RECURSE ALL_SRC CONFIGURE_DEPENDS src/*.cpp)
file(GLOB_RECURSE HEADER_FILES CONFIGURE_DEPENDS header/*.hpp)
file(GLOB_RECURSE TEST_FILES CONFIGURE_DEPENDS unit_tests/*.cpp)
file(GLOB_RECURSE UTILS_SRC CONFIGURE_DEPENDS utils/*.cpp)
file(GLOB_RECURSE UTILS_HEADERS CONFIGURE_DEPENDS utils/*.hpp)

# === Filter out main.cpp ===
set(SRC_FILES "")
foreach(file ${ALL_SRC})
    if(NOT file MATCHES ".*main\\.cpp$")
        list(APPEND SRC_FILES ${file})
    endif()
endforeach()

# === Add utils separately
list(APPEND ALL_SOURCES ${SRC_FILES} ${UTILS_SRC})
list(APPEND ALL_HEADERS ${HEADER_FILES} ${UTILS_HEADERS})




# === Source grouping (optional for Xcode) ===
source_group(TREE ${CMAKE_SOURCE_DIR}/src PREFIX "src" FILES ${SRC_FILES})
source_group(TREE ${CMAKE_SOURCE_DIR}/header PREFIX "header" FILES ${HEADER_FILES})
source_group(TREE ${CMAKE_SOURCE_DIR}/utils PREFIX "utils" FILES ${UTILS_SRC} ${UTILS_HEADERS})
source_group(TREE ${CMAKE_SOURCE_DIR}/unit_tests PREFIX "unit_tests" FILES ${TEST_FILES})


# === Shared Library ===
add_library(project_lib ${SRC_FILES} ${UTILS_SRC} ${HEADER_FILES} ${UTILS_HEADERS})
target_include_directories(project_lib PUBLIC header
utils
"/opt/homebrew/include"
)


# === Optional Main App ===
if(EXISTS "${CMAKE_SOURCE_DIR}/src/main.cpp")
    add_executable(left_behind src/main.cpp)
    target_link_libraries(left_behind PRIVATE project_lib)
endif()

# === Unit Tests ===
enable_testing()
find_package(GTest REQUIRED)

add_executable(test_environment ${TEST_FILES})
target_link_libraries(test_environment PRIVATE project_lib GTest::gtest_main)
target_include_directories(test_environment PRIVATE
 header
 utils)

add_test(NAME AllTests COMMAND test_environment)

# === Copy resources/ folder (e.g. config.json) ===
add_custom_command(TARGET left_behind POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:left_behind>/config
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/config.json
        $<TARGET_FILE_DIR:left_behind>/config/config.json
    COMMENT "Copying config.json to build output directory"
)

# === Optionally define config path for use in C++ ===
target_compile_definitions(left_behind PRIVATE "CONFIG_PATH=\"config/config.json\"")
target_link_libraries(left_behind PRIVATE
        cpr::cpr
        nlohmann_json::nlohmann_json
        fmt::fmt
        spdlog::spdlog
)

cmake_minimum_required(VERSION 3.16)
project(left_behind)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")

# Set debug flags properly
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

# Optionally enforce libc++ only if needed
add_compile_options("$<$<CONFIG:Debug>:-stdlib=libc++>")

# Xcode-specific
set(CMAKE_XCODE_GENERATE_SCHEME TRUE)
set(CMAKE_OSX_ARCHITECTURES arm64)
set(CMAKE_OSX_DEPLOYMENT_TARGET "15.3.2")
set(CMAKE_CONFIGURE_DEPENDS_NEW OFF CACHE INTERNAL "" FORCE)

# Third-party includes
include_directories(SYSTEM /opt/homebrew/include)

# External libraries
find_package(spdlog REQUIRED)
find_package(fmt REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(cpr REQUIRED)
find_package(pugixml REQUIRED)
find_package(GTest REQUIRED)

# === File Discovery ===
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS src/*.cpp)
file(GLOB_RECURSE TEST_FILES CONFIGURE_DEPENDS unit_tests/*.cpp)
file(GLOB_RECURSE UTILS_SRC CONFIGURE_DEPENDS utils/*.cpp)
file(GLOB_RECURSE HEADER_FILES CONFIGURE_DEPENDS header/*.hpp)
file(GLOB_RECURSE UTILS_HEADERS CONFIGURE_DEPENDS utils/*.hpp)

# Filter out main.cpp from the lib
set(PROJECT_SOURCES "")
foreach(file ${SRC_FILES})
    if(NOT file MATCHES ".*main\\.cpp$")
        list(APPEND PROJECT_SOURCES ${file})
    endif()
endforeach()

# === Project Library Target ===
add_library(project_lib)

# Attach all relevant source and header files
target_sources(project_lib
    PRIVATE
        ${PROJECT_SOURCES}
        ${UTILS_SRC}
        ${HEADER_FILES}
        ${UTILS_HEADERS}
)

target_include_directories(project_lib
    PUBLIC
        header
        utils
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

# === Optional Main Executable ===
if(EXISTS "${CMAKE_SOURCE_DIR}/src/main.cpp")
    add_executable(left_behind src/main.cpp)
    target_link_libraries(left_behind PRIVATE project_lib)

    target_compile_definitions(left_behind PRIVATE "CONFIG_PATH=\"config/config.json\"")

    add_custom_command(TARGET left_behind POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:left_behind>/config
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_SOURCE_DIR}/config.json
            $<TARGET_FILE_DIR:left_behind>/config/config.json
        COMMENT "Copying config.json to build output directory"
    )
endif()

# === Unit Tests ===
enable_testing()

add_executable(test_environment ${TEST_FILES})

target_link_libraries(test_environment
    PRIVATE
        project_lib
        GTest::gtest_main
)

target_include_directories(test_environment PRIVATE
    header
    utils
)

add_test(NAME AllTests COMMAND test_environment)

# === Optional: Source grouping in Xcode ===
source_group(TREE ${CMAKE_SOURCE_DIR}/src PREFIX "src" FILES ${SRC_FILES})
source_group(TREE ${CMAKE_SOURCE_DIR}/header PREFIX "header" FILES ${HEADER_FILES})
source_group(TREE ${CMAKE_SOURCE_DIR}/utils PREFIX "utils" FILES ${UTILS_SRC} ${UTILS_HEADERS})
source_group(TREE ${CMAKE_SOURCE_DIR}/unit_tests PREFIX "unit_tests" FILES ${TEST_FILES})

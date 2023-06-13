cmake_minimum_required(VERSION 3.25)
project(digdit)

set(CMAKE_CXX_STANDARD 20)
set(RAYLIB_VERSION 4.2.0)

add_subdirectory(vendor/raylib)
set(RAYLIB_STATIC ON)
set(BUILD_EXAMPLES OFF)
set(BUILD_GAMES OFF)

add_executable(digdit main.cpp src/StarBackground.cpp src/StarBackground.h)

target_link_libraries(digdit raylib)

# Copy the shaders folder to the build directory
add_custom_command(
        TARGET digdit POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/shaders ${CMAKE_BINARY_DIR}/shaders
)

# Copy the shaders folder to the build directory
add_custom_command(
        TARGET digdit POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/models ${CMAKE_BINARY_DIR}/models
)

# Copy the shaders folder to the build directory
add_custom_command(
        TARGET digdit POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/models-final ${CMAKE_BINARY_DIR}/models-final
)

# Web Configurations
if (${PLATFORM} STREQUAL "Web")
    # Tell Emscripten to build an example.html file.
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")
endif ()

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(digdit "-framework IOKit")
    target_link_libraries(digdit "-framework Cocoa")
    target_link_libraries(digdit "-framework OpenGL")
endif ()
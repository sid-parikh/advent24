cmake_minimum_required(VERSION 3.26)
project(advent24)

set(CMAKE_CXX_STANDARD 23)

add_executable(advent24 main.cpp)

target_include_directories(advent24 PRIVATE solutions)

add_custom_command(
        TARGET advent24 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/input
        $<TARGET_FILE_DIR:advent24>/input
)

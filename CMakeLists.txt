cmake_minimum_required(VERSION 2.8)

project(genesys)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(task
    queue.cpp
    task.cpp
)
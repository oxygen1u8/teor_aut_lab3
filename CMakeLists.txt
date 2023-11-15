cmake_minimum_required(VERSION 3.20)

set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(SRC_DIR ${ROOT_DIR}/src)

project(lab3)

add_executable(${PROJECT_NAME}
    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/pre_comp_table.cpp
    ${SRC_DIR}/s_couple.cpp
)

include_directories(
    ${SRC_DIR}
)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -c -Wall -ggdb")

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND cp ${PROJECT_NAME} ${ROOT_DIR}/${PROJECT_NAME}
    COMMENT "[post] Copy executable file ${PROJECT_NAME}"
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND cp compile_commands.json ${ROOT_DIR}/compile_commands.json
    COMMENT "[post] Copy compile_commands.json"
)

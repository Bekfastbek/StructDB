cmake_minimum_required(VERSION 4.1)
project(winapi_gui C)

set(CMAKE_C_STANDARD 11)

add_executable(winapi_gui main.c
        modules/window_handler.c
        include/window_handler.h
        modules/exit_diag.c
        include/exit_diag.h)

target_link_libraries(winapi_gui dwmapi)
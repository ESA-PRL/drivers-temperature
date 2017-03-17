cmake_minimum_required(VERSION 2.6)
find_package(Rock)

rock_init(temperature 0.1)
rock_standard_layout()

rock_executable(temperature_test src/main.cpp
    DEPS temperature)


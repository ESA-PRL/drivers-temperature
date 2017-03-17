rock_library(temperature
    SOURCES Dummy.cpp
    HEADERS Dummy.hpp)

rock_executable(temperature_bin Main.cpp
    DEPS temperature)


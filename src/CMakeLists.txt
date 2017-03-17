rock_library(temperature
    SOURCES Temperature.cpp
    HEADERS Temperature.hpp
	DEPS_PKGCONFIG iodrivers_base)

rock_executable(temperature_bin main.cpp
    DEPS temperature
    DEPS_PKGCONFIG iodrivers_base)


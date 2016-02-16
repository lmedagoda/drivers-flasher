rock_library(flasher
    SOURCES Driver.cpp
    HEADERS Driver.hpp
    DEPS_PKGCONFIG base-types iodrivers_base)

rock_executable(flasher_bin Main.cpp
    DEPS flasher)


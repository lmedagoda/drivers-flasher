rock_library(flasher
    SOURCES Dummy.cpp
    HEADERS Dummy.hpp)

rock_executable(flasher_bin Main.cpp
    DEPS flasher)


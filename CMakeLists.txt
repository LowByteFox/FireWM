cmake_minimum_required(VERSION 3.22)
project(FireWM VERSION 6.3 LANGUAGES C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS true)

# variables
set(PREFIX /usr/local)

# include dirs
include_directories(/usr/X11R6/include)
include_directories(/usr/include/freetype2)
include_directories(/usr/include/yajl)
link_directories(/usr/X11R6/lib)
link_directories(lib)

# compile definitions
add_compile_definitions(
    XINERAMA _DEFAULT_SOURCE
    _BSD_SOURCE _POSIX_C_SOURCE=200809L
    VERSION="6.3"
)

# C++ config
message("Configuring C++")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

FILE(GLOB SRC ./src/*)

# C config
message("Configuring C")
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED true)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -rdynamic -pedantic -Wall -Wno-deprecated-declarations ${CMAKE_CXX_FLAGS}")

# Applications
message("Configuring executables")
add_executable(firewm ${SRC})
target_link_libraries(firewm Xinerama fontconfig Xft X11 Xrender Xext Imlib2 FoxString json-c yajl pthread FoxBox)

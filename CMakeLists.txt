cmake_minimum_required(VERSION 3.22)
project(arcade)

set(CMAKE_CXX_STANDARD 20)
include_directories(.)
include_directories(src/Core)
include_directories(include)

# NCurses Library
add_library(arcade_ncurses SHARED
        src/NCurses/NCurses.cpp src/NCurses/NCurses.hpp src/NCurses/NCursesUtils.cpp src/NCurses/NCursesUtils.hpp)

target_link_libraries(arcade_ncurses ncurses)

# SDL2 Library
add_library(arcade_sdl2 SHARED
        src/Sdl2/Sdl2.cpp src/Sdl2/Sdl2.hpp)

find_package(SDL2 REQUIRED COMPONENTS SDL2)

if (APPLE)
    find_package(SDL2_image REQUIRED)
    find_package(SDL2_ttf REQUIRED)
    find_package(SDL2_mixer REQUIRED)
    include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS})
    target_link_libraries(arcade_sdl2 PRIVATE SDL2::SDL2 SDL2_image::SDL2_image SDL2_ttf::SDL2_ttf SDL2_mixer::SDL2_mixer)
else ()
    target_link_libraries(arcade_sdl2 SDL2 SDL2_image SDL2_ttf SDL2_mixer)
endif()

# SFML Library
add_library(arcade_sfml SHARED
        src/Sfml/Sfml.cpp src/Sfml/Sfml.hpp)

find_package(SFML 2.5 COMPONENTS graphics window system audio REQUIRED)
include_directories(${SFML_INCLUDE_DIR})
target_link_libraries(arcade_sfml sfml-graphics sfml-window sfml-system sfml-audio)

# Games :

# Pacman Library
add_library(arcade_pacman SHARED
        src/Pacman/PacmanCreation.cpp src/Pacman/Pacman.hpp src/Pacman/Pathfinder.cpp src/Pacman/Pathfinder.hpp src/Pacman/PacmanEntity.cpp src/Pacman/PacmanData.cpp src/Pacman/PacmanCollision.cpp src/Pacman/PacmanMob.cpp src/Pacman/PacmanAction.cpp src/Pacman/PacmanEngine.cpp)

# Snake Library
add_library(arcade_snake SHARED
        src/Snake/Snake.cpp src/Snake/Snake.hpp src/Snake/SnakeEntity.cpp src/Snake/SnakeData.cpp)

set_target_properties(arcade_ncurses PROPERTIES PREFIX "" SUFFIX .so LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set_target_properties(arcade_sfml PROPERTIES PREFIX "" SUFFIX .so LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set_target_properties(arcade_sdl2 PROPERTIES PREFIX "" SUFFIX .so LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set_target_properties(arcade_pacman PROPERTIES PREFIX "" SUFFIX .so LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set_target_properties(arcade_snake PROPERTIES PREFIX "" SUFFIX .so LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

# Core
if (UNIX AND NOT APPLE)
    add_compile_options(-fno-gnu-unique)
endif()
add_executable(arcade
        src/Main.cpp src/Core/Core.cpp src/Core/Core.hpp src/Core/Arcade.cpp src/Core/Arcade.hpp src/Core/DlLoader.cpp src/Core/DlLoader.hpp)
target_link_libraries(arcade dl)

set_target_properties(arcade PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
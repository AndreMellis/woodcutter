cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
project(woodsman VERSION 1.0)

include_directories("game/headers" 
                    "game/sources" 
                    "src/world/headers"
                    "src/world/sources"
                    "src/common/headers"
                    "src/common/sources")

#link sdl2 libraries
find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3)
find_package(SDL3_image REQUIRED)

set(SOURCES 
    game/sources/Builder.cpp
    game/sources/Game.cpp
    game/sources/Actions.cpp
    game/sources/ActionHandler.cpp
    game/sources/WorkerCharacter.cpp
    src/common/sources/TextureHandler.cpp
    src/common/sources/AStar.cpp
    src/common/sources/UserInterface.cpp
    src/common/sources/SaveLoader.cpp
    src/world/sources/Map.cpp
    src/world/sources/DayTime.cpp)

add_executable(woodsman.out main.cpp ${SOURCES})
target_link_libraries(woodsman.out PRIVATE SDL3::SDL3 SDL3_image)
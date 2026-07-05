cmake_minimum_required(VERSION 3.20)

project(LizuChess LANGUAGES CXX)

#c++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#sfml3 vcpkg
find_package(SFML CONFIG REQUIRED COMPONENTS Graphics Window System Audio)

#minden cpp auto bekerul
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_executable(LizuChess ${SOURCES} "src/theme/Theme.h" "src/theme/Theme.cpp" "src/theme/ThemeManager.h" "src/theme/ThemeManager.cpp" "src/move/Move.h" "src/move/Move.cpp" "src/position/Position.cpp" "src/position/Position.h" "src/engine/gamestate/GameState.h")

#include folders
target_include_directories(LizuChess PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

#sfml link
target_link_libraries(LizuChess PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
    SFML::Audio
)

#windows alatt kikapcsolni a release mode-ot
if(WIN32)
    set_target_properties(LizuChess PROPERTIES
        WIN32_EXECUTABLE $<$<CONFIG:Release>:TRUE>
    )
endif()


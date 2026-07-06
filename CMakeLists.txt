cmake_minimum_required(VERSION 3.20)

project(LizuChess LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(SFML CONFIG REQUIRED COMPONENTS Graphics Window System Audio)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_executable(LizuChess ${SOURCES} "src/engine/movegenerator/MoveGeneratorPawns.cpp" "src/engine/movegenerator/MoveGeneratorKnights.cpp" "src/engine/movegenerator/MoveGeneratorSliding.cpp" "src/engine/movegenerator/MoveGeneratorKing.cpp" "src/engine/movegenerator/MoveGeneratorBishop.cpp" "src/engine/movegenerator/MoveGeneratorRook.cpp" "src/engine/movegenerator/MoveGeneratorQueen.cpp")

target_include_directories(LizuChess PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

target_link_libraries(LizuChess PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
    SFML::Audio
)
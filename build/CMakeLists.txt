cmake_minimum_required(VERSION 3.16)

project(Testing LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Testing
    snake.h snake.cpp
    controls.h
)

# Busca a direcao da pasta
set(SFML_DIR "/home/yang/DevProjects/C++/Libraries/SFML-3.1.0/lib/cmake/SFML/")

# Encotra o pacote e define quais sao as pasta que serao usadas
find_package(SFML 3.1 REQUIRED COMPONENTS Graphics Window System Audio Network)

# Faz a compilador aplicar as funcao da biblitecas
target_link_libraries(Testing
    SFML::Graphics
    SFML::Window
    SFML::System
    SFML::Audio
    SFML::Network)

target_compile_options(Testing PRIVATE -lsfml-graphics -lsfml-window -lsfml-system)

include(GNUInstallDirs)
install(TARGETS Testing
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

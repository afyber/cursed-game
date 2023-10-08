# CMakeList.txt, main CMake config for Cursed
cmake_minimum_required(VERSION 3.13)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE
        "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "Vcpkg toolchain file")
endif()

project("cursed-game"
    LANGUAGES CXX
)

find_package(SDL2 CONFIG REQUIRED)
find_package(libtcod CONFIG REQUIRED)

file(GLOB SOURCES "src/*.cpp")

# Add source to this project's executable.
add_executable(${PROJECT_NAME} ${SOURCES})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE "/W4")
    target_compile_options(${PROJECT_NAME} PRIVATE "/utf-8")
    target_link_options(${PROJECT_NAME} PRIVATE "/SUBSYSTEM:WINDOWS")
else()
    target_compile_options(${PROJECT_NAME} PRIVATE "-Wall -Wextra")
endif()

target_link_libraries(${PROJECT_NAME}
    SDL2::SDL2
    SDL2::SDL2main
    libtcod::libtcod
)

install(TARGETS ${PROJECT_NAME} DESTINATION "install/")
install(DIRECTORY "data/" DESTINATION "install/")

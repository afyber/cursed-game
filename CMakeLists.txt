# CMakeList.txt, main CMake config for Cursed
cmake_minimum_required(VERSION 3.21)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE
        "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "Vcpkg toolchain file")
endif()

project("cursed-game"
    LANGUAGES CXX
)

find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)
find_package(libtcod CONFIG REQUIRED)

file(GLOB SOURCES "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

# Copy the resources into the binary folder after every build
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${PROJECT_SOURCE_DIR}/data"
    "${PROJECT_BINARY_DIR}/data"
)

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE "/W4" "/utf-8")
    target_link_options(${PROJECT_NAME} PRIVATE "/SUBSYSTEM:WINDOWS")
else()
    target_compile_options(${PROJECT_NAME} PRIVATE "-Wall" "-Wextra")
endif()

# For some insane reason SDL2_image (not SDL2) doesn't have an SDL2_image::SDL2_image style definition, but only on linux, so we need to do this
if(UNIX)
    target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_image_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_image_LIBRARIES})
else()
    target_link_libraries(${PROJECT_NAME} SDL2_image::SDL2_image)
endif()

target_link_libraries(${PROJECT_NAME}
    SDL2::SDL2
    SDL2::SDL2main
    libtcod::libtcod
)

install(TARGETS ${PROJECT_NAME} DESTINATION ".")
install(DIRECTORY "data/" DESTINATION "data/")

# TODO: Actually fix
file(GLOB DLLS ${PROJECT_BINARY_DIR}/*.dll)
# needed for the windows build to copy the .dll files into the install directory
install(CODE "file(INSTALL ${DLLS} DESTINATION ${CMAKE_INSTALL_PREFIX}/)")

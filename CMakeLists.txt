# CMakeList.txt, main CMake config for Cursed
cmake_minimum_required(VERSION 3.21)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE
        "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "Vcpkg toolchain file")
endif()

project("cursed-game"
    VERSION 0.1.0.0
    LANGUAGES CXX
)

# Don't continue unless all dependencies are present
find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)
find_package(libtcod CONFIG REQUIRED)

file(GLOB INCLUDES "src/*.hpp")
file(GLOB SOURCES "src/*.cpp")

add_executable(${PROJECT_NAME} ${INCLUDES} ${SOURCES})
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

# Copy the resources into the binary folder after every build to ensure they're up-to-date
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

target_link_libraries(${PROJECT_NAME}
    $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
    $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
    $<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,SDL2_image::SDL2_image,SDL2_image::SDL2_image-static>
    libtcod::libtcod
)

install(TARGETS ${PROJECT_NAME} DESTINATION ".")
install(DIRECTORY "data/" DESTINATION "data/")

# Needed for the windows build to copy the .dll files into the install directory
if (WIN32) 
    install(CODE "
    file(GLOB DLLS ${PROJECT_BINARY_DIR}/*.dll)
    file(INSTALL \${DLLS} DESTINATION ${CMAKE_INSTALL_PREFIX}/)
    ")
endif()
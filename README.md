# Cursed

Open-source roguelike made with libtcod and written in C++

## About

Just a personal project of mine, the basic idea being: what if you could never get hit in a roguelike?

## Contributing

Please fork and make a pull request with a clear description of what you are adding/changing.

## Building

Depends on: `libtcod`, `SDL2`, and `SDL2_image`

You need `git` or some other tool to get the source code, in order to follow along with the instructions below run open a console and run these commands:
```
git clone --recurse-submodules https://github.com/afyber/cursed-game.git
cd cursed-game
```

### Building on Windows

Requires: `Visual Studio` (recommended), or `CMake` and a build system

1. To setup vcpkg run `.\vcpkg\bootstrap-vcpkg.bat`
Alternatively, to use your own installation of vcpkg you can specify it with the `-DCMAKE_TOOLCHAIN_FILE=path/to/vcpkg/scripts/buildsystems/vcpkg.cmake` option on your CMake command in the next step or setting the `CMAKE_TOOLCHAIN_FILE` variable.
2. Use CMake to generate the build configuration either by opening `cursed-game` in Visual Studio or by creating a new directory and running `cmake ..` in the subdirectory.
Unless you specified a different installation this command will attempt to use the vcpkg submodule to find the dependencies.
3. Build the project using Visual Studio or the build system you specified for CMake, which will copile the executable `cursed-game.exe`.
4. (Optional) Run the install configuration, which will put the files needed to run the game into the installation folder (Which for Visual Studio is `cursed-game\out\install\{platform}\`).

### Building on Linux

Requires: `cmake` and a build system of your choice

1. To setup vcpkg run `./vcpkg/bootstrap-vcpkg.sh`
2. Create a new folder with `mkdir build`, then run `cmake ..` in the `build/` directory to generate the build configuration.
3. Build the project using the build system of your choice (e.g. run `make`), which will compile the executable `cursed-game`.
4. (Optional) Run the install configuration, which will put everything the game needs to run in `build/usr/local/`.

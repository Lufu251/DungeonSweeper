# DungeonSweeper
This is a simple game that adds to the concept of the classic MineSweeper.

* [Features](#features)
* [Building](#building)
* [Notes](#notes)
* [Media](#media)
* [License](#license)

## Features

## Building

### Prerequisites
* Compiler (GCC, Clang, MSVC)
* CMake
* Emscripten (only WEB)
* Python 3.8 or newer (only WEB)
* Git (Recommended)

### CMake Build

1.  **Clone the repository:**
    ```bash
    git clone https://github.com/Lufu251/DungeonSweeper.git
    cd DungeonSweeper
    ```

2.  **Configure and build with CMake:**
    ```bash
    mkdir build
    cd build
    cmake ..
    cmake --build .
    ```
    The binaries will be located in the `build/bin` directory.

### Emscripten Build

1.  **Clone the repository:**
    ```bash
    git clone https://github.com/Lufu251/DungeonSweeper.git
    cd DungeonSweeper
    ```

2.  **Configure and build with Emscripten:**
    ```bash
    cd tools
    ./build_web.sh
    ```
    Now there should be a HTTP Server running under port 8000 to test your project. The URL should be visible in the active terminal.

## Notes
* 

## Media


## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

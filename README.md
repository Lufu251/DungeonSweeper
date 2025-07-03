# DungeonSweeper
This is a simple game that adds to the concept of the classic MineSweeper.

* [Features](#features)
* [Notes](#notes)
* [Media](#media)
* [Building](#building)
* [License](#license)

## Features
* (Add a features of your project here)

## Notes
* (Add a controls here)
* (Add a additional information here)

## Media
* (Add a screenshot or GIF of your project here)

## Building

### Prerequisites
* **CMake** (3.15 or newer)
* **C++ Compiler** (e.g.,GCC, Clang, MSVC)
* **Git** (for fetching dependencies)
* **Emscripten SDK** (only for web builds)
* **Python 3.8+** (only for web builds)

### Desktop Build (Windows, macOS, Linux)
1. **Configure and build with CMake:**
    ```bash
    mkdir build
    cd build
    cmake ..
    cmake --build .
    ```
    The example binaries will be located in the `build/bin` directory.

### Web Build (WebAssembly)
1.  **Configure and build with Emscripten**
    ```bash
    cd tools
    ./build_web.sh
    ```
    Now there should be a HTTP Server running under port 8000 to test your project. The URL should be visible in the active terminal.

## License
This project is licensed under the [LICENSE_NAME] License - see the [LICENSE](LICENSE) file for details.

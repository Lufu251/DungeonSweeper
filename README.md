# Raylib Template
This template simplifies the setup process for Raylib using CMake. It supports automatic fetching of some pre-selected libraries. This template is designed to work for web and desktop builds. It's an easy way to start an awesome Raylib project!

* [Features](#features)
* [Building](#building)
* [Notes](#notes)
* [Media](#media)
* [License](#license)

## Features
* **Automatic fetching:** You can automaticaly use some pre-selected libraries by turning them on and off
* **Build for the Web:** To build and compile your project for the web with ease
* **CMake Build:** System: Easy to configure and build the a new project and examples.
* **LufuGameLib:** Provides additional usefull features to raylib and more

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
    git clone https://github.com/Lufu251/RaylibTemplate.git <new-project-name>
    cd <new-project-name>
    rm -rf .git
    ```

2.  **Configure and build with CMake:**
    ```bash
    mkdir build
    cd build
    cmake ..
    cmake --build .
    ```
    The example binaries will be located in the `build/bin` directory.

### Emscripten Build

1.  **Clone the repository:**
    ```bash
    git clone https://github.com/Lufu251/RaylibTemplate.git <new-project-name>
    cd <new-project-name>
    rm -rf .git
    ```

2.  **Configure and build with Emscripten:**
    ```bash
    cd tools
    ./build_web.sh
    ```
    Now there should be a HTTP Server running under port 8000 to test your project. The URL should be visible in the active terminal.

## Notes
* Usefull information on how to use raylib for the web and how to solve some common issues: https://github.com/raysan5/raylib/wiki/Working-for-Web-(HTML5)

## Media


## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

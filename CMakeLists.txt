# Minimum required version of CMake
cmake_minimum_required(VERSION 3.22)
# Project name and version
project(MyCppProject VERSION 1.0)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

##########################################################################################
# Configurable options
##########################################################################################

# toggle libs to be used with ON and OFF
option(USE_RAYLIB "Use raylib" ON)
option(USE_RAYGUI "Use raygui" ON)
option(USE_BOX2D "Use Box2D" OFF)
option(USE_LDTKLOADER "Use LDtk Loader" OFF)


##########################################################################################
# Add dependencies with FetchContent
##########################################################################################

# libraries array to be linked
set(LIBRARIES ${PROJECT_NAME})

# PROJECT_INCLUDE array to be included
set(PROJECT_INCLUDE ${PROJECT_NAME})

# Include FetchContent
include(FetchContent)

##########################################################################################
# Raylib Setup
##########################################################################################

if(USE_RAYLIB)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
    set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # don't build the supplied example games
    set(BUILD_TESTING OFF CACHE BOOL "" FORCE)
    set(CUSTOMIZE_BUILD OFF CACHE BOOL "" FORCE)

    message(STATUS "Fetching raylib...")
    FetchContent_Declare(raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG        master
        GIT_SHALLOW    TRUE
        GIT_PROGRESS   TRUE
    )

    FetchContent_MakeAvailable(raylib)

    # add the dependency here to be linked
    list(APPEND LIBRARIES raylib)
endif()


##########################################################################################
# Raygui Setup
##########################################################################################

if(USE_RAYGUI)
    set(BUILD_RAYGUI_EXAMPLES OFF CACHE BOOL "" FORCE)

    message(STATUS "Fetching raygui...")
    FetchContent_Declare(raygui
        GIT_REPOSITORY https://github.com/raysan5/raygui.git
        GIT_TAG        master
        GIT_SHALLOW    TRUE
        GIT_PROGRESS   TRUE
    )
    FetchContent_MakeAvailable(raygui)

    # Adding raygui include paths
    list(APPEND PROJECT_INCLUDE ${raygui_SOURCE_DIR}/src/)
endif()


##########################################################################################
# Box2D Setup
##########################################################################################

if(USE_BOX2D)
    set(BOX2D_BUILD_TESTBED OFF CACHE BOOL "" FORCE) # don't build the supplied examples
    set(BOX2D_BUILD_UNIT_TESTS OFF CACHE BOOL "" FORCE) # don't build the supplied examples

    message(STATUS "Fetching box2d...")
    FetchContent_Declare(box2d
        GIT_REPOSITORY https://github.com/erincatto/box2d.git
        GIT_TAG        main
        GIT_SHALLOW    TRUE
        GIT_PROGRESS   TRUE
    )
    FetchContent_MakeAvailable(box2d)

    # add the dependency here to be linked
    list(APPEND LIBRARIES box2d)
endif()


##########################################################################################
# Project executable setup
##########################################################################################

# Specify the output directories for compiled binaries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Adding our source files
# Define PROJECT_SOURCES as a list of all source files
file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp")

# Adding include paths
list(APPEND PROJECT_INCLUDE ${CMAKE_CURRENT_LIST_DIR}/include/)

# Declaring our executable
add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_INCLUDE})


##########################################################################################
# Project build settings
##########################################################################################

# Build for web instructions
if (${PLATFORM} STREQUAL "Web")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Os") 
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --shell-file ${CMAKE_CURRENT_LIST_DIR}/tools/minshell.html -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -s ASYNCIFY -s GL_ENABLE_GET_PROC_ADDRESS=1")
    set(CMAKE_EXECUTABLE_SUFFIX ".html") # This line is used to set your executable to build with the emscripten html template so that you can directly open it.
endif ()

# Link libraries
target_link_libraries(${LIBRARIES})

# Set common compiler options for your target
target_compile_options(${PROJECT_NAME} PRIVATE
    -Wall
    -Wextra      # More warnings
    -Wpedantic   # Strict ISO C++ compliance warnings
    # Add other warning flags like -Wshadow, -Wconversion, etc. as needed
)
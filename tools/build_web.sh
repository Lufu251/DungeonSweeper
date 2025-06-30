#!/bin/bash

#==============================================================================
# Raylib Web Build Automation Script
#
# This script automates the entire process of compiling a Raylib project
# for the Web (HTML5) using Emscripten.
#==============================================================================

# NOTE you must have installed emscripten to any folder and define the path here:
https://emscripten.org/docs/getting_started/downloads.html

# CHANGE THIS VARIABLE to match your system's path.
EMSDK_PATH="$HOME/emsdk"

# The name of the build directory to be created.
BUILD_DIR="build-web"


#==============================================================================
# Script
#==============================================================================

# Exit immediately if any command fails.
set -e

echo "--- [ Raylib Web Build Started ] ---"

# Change the current directory to the script's directory
cd "$(dirname "$0")"

# Go up one folder to start in the root folder of the project
cd ..

# 1. Validate and Source the Emscripten Environment
# ------------------------------------------------------------
echo "-> Checking for Emscripten SDK at: $EMSDK_PATH"

if [ ! -d "$EMSDK_PATH" ]; then
    echo "Error: Emscripten SDK directory not found at '$EMSDK_PATH'."
    echo "Please update the EMSDK_PATH variable in this script."
    exit 1
fi

if [ ! -f "$EMSDK_PATH/emsdk_env.sh" ]; then
    echo "Error: 'emsdk_env.sh' not found inside '$EMSDK_PATH'."
    echo "Your Emscripten installation might be incomplete or the path is wrong."
    exit 1
fi

echo "-> Sourcing Emscripten environment..."
# The 'source' command loads the emsdk environment into the current shell session.
source "$EMSDK_PATH/emsdk_env.sh"

# Note: 'emsdk activate' is usually a one-time setup and not needed for every build.
# Sourcing the environment is the key step for each terminal session.

# 2. Configure the Build with CMake
# ------------------------------------------------------------
echo "-> Creating build directory: '$BUILD_DIR'"
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

echo "-> Configuring project with emcmake..."
# We pass -DPLATFORM=Web to tell Raylib's CMake configuration to set up a web build.
emcmake cmake .. -DPLATFORM=Web

# 3. Compile the Game
# ------------------------------------------------------------
echo "-> Compiling the game with emmake..."
emmake make

# The compilation will produce an HTML file (e.g., your_project_name.html)
# We can try to find this file to provide a direct link to the user.
HTML_FILE=$(find ./bin -maxdepth 1 -type f -name "*.html" | head -n 1)

echo ""
echo "--- [ Build Successful! ] ---"
echo "Project compiled successfully."
echo "Output files are in the '$PWD' directory."

# 4. Run the Local Web Server
# ------------------------------------------------------------
echo ""
echo "--- [ Starting Local Web Server ] ---"
echo "You can now view your game in a web browser."

if [ -n "$HTML_FILE" ]; then
    echo "URL: http://localhost:8000/$HTML_FILE"
else
    echo "Navigate to http://localhost:8000"
fi

echo ""
echo "Starting server... (Press CTRL+C to stop)"

# Use python3 if available, otherwise fall back to python
if command -v python3 &> /dev/null; then
    python3 -m http.server
else
    python -m SimpleHTTPServer
fi
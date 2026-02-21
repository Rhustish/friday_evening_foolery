#!/bin/sh

# Exit immediately if a command fails
set -e

# Get the directory where this script is located
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"

# Move to the script directory
cd "$SCRIPT_DIR"

# Remove existing build directory if it exists
if [ -d "build" ]; then
    rm -rf build
fi

# Run cmake to generate build files and export compile commands
cmake -S . -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

cd build
cmake --build .

cd ..

# Copy compile_commands.json to current directory
cp build/compile_commands.json ./compile_commands.json

echo "Done."

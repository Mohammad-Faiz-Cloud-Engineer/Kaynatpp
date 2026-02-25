#!/bin/bash
# Setup script for third-party dependencies

set -e

cd "$(dirname "$0")"

echo "Setting up Kaynat++ third-party dependencies..."
echo ""

# Clone Dear ImGui
if [ ! -d "imgui" ]; then
    echo "Downloading Dear ImGui..."
    git clone --depth 1 https://github.com/ocornut/imgui.git
    echo "✓ Dear ImGui downloaded"
else
    echo "✓ Dear ImGui already present"
fi

# Download nlohmann/json
if [ ! -f "nlohmann/json.hpp" ]; then
    echo "Downloading nlohmann/json..."
    mkdir -p nlohmann
    wget -q https://github.com/nlohmann/json/releases/download/v3.11.3/json.hpp -O nlohmann/json.hpp
    echo "✓ nlohmann/json downloaded"
else
    echo "✓ nlohmann/json already present"
fi

echo ""
echo "Third-party dependencies ready!"
echo ""
echo "Note: SDL2 and libcurl must be installed via your system package manager."
echo "See third_party/README.md for installation instructions."

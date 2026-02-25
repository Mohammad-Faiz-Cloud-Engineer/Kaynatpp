# Third-Party Dependencies

This directory contains bundled third-party libraries used by Kaynat++.

## Required Libraries

### 1. Dear ImGui (Bundled)

**Location**: `imgui/`

Dear ImGui is a bloat-free graphical user interface library for C++. It's used for the GUI programming features in Kaynat++.

**Setup**:
```bash
cd third_party
git clone https://github.com/ocornut/imgui.git
```

**License**: MIT License

### 2. nlohmann/json (Header-only, Bundled)

**Location**: `nlohmann/json.hpp`

A modern C++ JSON library that's header-only and easy to integrate.

**Setup**:
```bash
cd third_party
mkdir -p nlohmann
wget https://github.com/nlohmann/json/releases/download/v3.11.3/json.hpp -O nlohmann/json.hpp
```

**License**: MIT License

### 3. SDL2 (System Library)

SDL2 is required for window management and rendering. Install via your system package manager:

**Ubuntu/Debian**:
```bash
sudo apt-get install libsdl2-dev
```

**macOS**:
```bash
brew install sdl2
```

**Arch Linux**:
```bash
sudo pacman -S sdl2
```

### 4. libcurl (System Library)

libcurl is required for HTTP networking features. Install via your system package manager:

**Ubuntu/Debian**:
```bash
sudo apt-get install libcurl4-openssl-dev
```

**macOS**:
```bash
brew install curl
```

**Arch Linux**:
```bash
sudo pacman -S curl
```

## Setup Script

Run this script to download and set up bundled dependencies:

```bash
#!/bin/bash
cd third_party

# Clone Dear ImGui
if [ ! -d "imgui" ]; then
    echo "Downloading Dear ImGui..."
    git clone https://github.com/ocornut/imgui.git
fi

# Download nlohmann/json
if [ ! -f "nlohmann/json.hpp" ]; then
    echo "Downloading nlohmann/json..."
    mkdir -p nlohmann
    wget https://github.com/nlohmann/json/releases/download/v3.11.3/json.hpp -O nlohmann/json.hpp
fi

echo "Third-party dependencies ready!"
```

Save this as `setup_deps.sh` and run:
```bash
chmod +x setup_deps.sh
./setup_deps.sh
```

## License Information

All third-party libraries are used under their respective licenses:

- **Dear ImGui**: MIT License
- **nlohmann/json**: MIT License
- **SDL2**: zlib License
- **libcurl**: MIT/X derivate License

See individual library directories for full license texts.

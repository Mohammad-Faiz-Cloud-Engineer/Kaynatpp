#!/bin/bash
# Build script for Kaynat++

set -e  # Exit on error

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo -e "${GREEN}Building Kaynat++ Programming Language${NC}"
echo ""

# Parse arguments
BUILD_TYPE="Release"
CLEAN=false
RUN_TESTS=false

while [[ $# -gt 0 ]]; do
    case $1 in
        --debug)
            BUILD_TYPE="Debug"
            shift
            ;;
        --clean)
            CLEAN=true
            shift
            ;;
        --test)
            RUN_TESTS=true
            shift
            ;;
        --help)
            echo "Usage: ./build.sh [OPTIONS]"
            echo ""
            echo "Options:"
            echo "  --debug     Build in debug mode with sanitizers"
            echo "  --clean     Clean build directory before building"
            echo "  --test      Run tests after building"
            echo "  --help      Show this help message"
            exit 0
            ;;
        *)
            echo -e "${RED}Unknown option: $1${NC}"
            exit 1
            ;;
    esac
done

BUILD_DIR="build/${BUILD_TYPE,,}"

# Clean if requested
if [ "$CLEAN" = true ]; then
    echo -e "${YELLOW}Cleaning build directory...${NC}"
    rm -rf "$BUILD_DIR"
fi

# Create build directory
mkdir -p "$BUILD_DIR"

# Configure
echo -e "${YELLOW}Configuring CMake (${BUILD_TYPE})...${NC}"
cmake -B "$BUILD_DIR" -DCMAKE_BUILD_TYPE="$BUILD_TYPE"

# Build
echo -e "${YELLOW}Building...${NC}"
cmake --build "$BUILD_DIR" --parallel $(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)

# Success message
echo ""
echo -e "${GREEN}Build successful!${NC}"
echo -e "Binary location: ${YELLOW}$BUILD_DIR/kaynat${NC}"
echo ""

# Run tests if requested
if [ "$RUN_TESTS" = true ]; then
    echo -e "${YELLOW}Running tests...${NC}"
    # TODO: Add test execution when tests are implemented
    echo -e "${YELLOW}Tests not yet implemented${NC}"
fi

# Show usage examples
echo -e "${GREEN}Usage examples:${NC}"
echo -e "  Run a program:  ${YELLOW}$BUILD_DIR/kaynat examples/01_hello_world.kn${NC}"
echo -e "  Start REPL:     ${YELLOW}$BUILD_DIR/kaynat --repl${NC}"
echo -e "  Show help:      ${YELLOW}$BUILD_DIR/kaynat --help${NC}"
echo ""

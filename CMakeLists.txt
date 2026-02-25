cmake_minimum_required(VERSION 3.20)
project(Kaynat++ VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -fsanitize=address,undefined")

# Position independent code
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Find required packages
find_package(SDL2 REQUIRED)
find_package(CURL REQUIRED)

# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/third_party
    ${CMAKE_SOURCE_DIR}/third_party/imgui
    ${CMAKE_SOURCE_DIR}/third_party/nlohmann
    ${SDL2_INCLUDE_DIRS}
    ${CURL_INCLUDE_DIRS}
)

# Source files
set(KAYNAT_SOURCES
    src/main.cpp
    src/repl.cpp
    src/lexer/lexer.cpp
    src/parser/parser.cpp
    src/interpreter/interpreter.cpp
    src/interpreter/environment.cpp
    src/stdlib/math_tools.cpp
    src/stdlib/string_tools.cpp
    src/stdlib/list_tools.cpp
    src/stdlib/file_tools.cpp
    src/stdlib/date_tools.cpp
    src/stdlib/random_tools.cpp
    src/stdlib/network_tools.cpp
    src/stdlib/json_tools.cpp
    src/stdlib/crypto_tools.cpp
    src/stdlib/pattern_tools.cpp
    src/dsa/graph.cpp
    src/gui/engine.cpp
    src/gui/window.cpp
    src/gui/widgets.cpp
    src/gui/events.cpp
    src/gui/canvas.cpp
    src/gui/dialogs.cpp
    src/gui/menu.cpp
    src/gui/themes.cpp
    src/oop/blueprint.cpp
    src/oop/instance.cpp
    src/oop/contract.cpp
    src/errors/messages.cpp
)

# ImGui sources
set(IMGUI_SOURCES
    third_party/imgui/imgui.cpp
    third_party/imgui/imgui_draw.cpp
    third_party/imgui/imgui_tables.cpp
    third_party/imgui/imgui_widgets.cpp
    third_party/imgui/backends/imgui_impl_sdl2.cpp
    third_party/imgui/backends/imgui_impl_sdlrenderer2.cpp
)

# Main executable
add_executable(kaynat ${KAYNAT_SOURCES} ${IMGUI_SOURCES})
target_link_libraries(kaynat ${SDL2_LIBRARIES} ${CURL_LIBRARIES})

# Install target
install(TARGETS kaynat DESTINATION bin)

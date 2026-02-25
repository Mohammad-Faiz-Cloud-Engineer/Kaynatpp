/**
 * @file main.cpp
 * @brief Entry point for Kaynat++ interpreter
 * 
 * Handles command-line arguments and dispatches to REPL or file execution.
 */

#include <iostream>
#include <string>

namespace kaynat {
    void run_repl();
    void run_file(const std::string& filename);
}

/**
 * @brief Print usage information
 */
void print_usage(const char* program_name) {
    std::cout << "Kaynat++ Programming Language\n";
    std::cout << "Usage:\n";
    std::cout << "  " << program_name << " <file.kn>     Run a Kaynat++ program\n";
    std::cout << "  " << program_name << " --repl        Start interactive REPL\n";
    std::cout << "  " << program_name << " --help        Show this help message\n";
    std::cout << "  " << program_name << " --version     Show version information\n";
}

/**
 * @brief Print version information
 */
void print_version() {
    std::cout << "Kaynat++ version 1.0.0\n";
    std::cout << "Built with C++17\n";
    std::cout << "Created by Mohammad Faiz\n";
}

/**
 * @brief Main entry point
 */
int main(int argc, char* argv[]) {
    if (argc < 2) {
        print_usage(argv[0]);
        return 1;
    }
    
    const std::string arg = argv[1];
    
    if (arg == "--help" || arg == "-h") {
        print_usage(argv[0]);
        return 0;
    }
    
    if (arg == "--version" || arg == "-v") {
        print_version();
        return 0;
    }
    
    if (arg == "--repl" || arg == "-r") {
        kaynat::run_repl();
        return 0;
    }
    
    // Assume it's a filename
    try {
        kaynat::run_file(arg);
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
}

/**
 * @file repl.cpp
 * @brief REPL implementation
 */

#include "repl.hpp"
#include "errors/error_types.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

namespace kaynat {

void run_repl() {
    std::cout << "Kaynat++ REPL v1.0.0\n";
    std::cout << "Type 'exit' to quit, 'help' for help\n\n";
    
    std::string line;
    
    while (true) {
        std::cout << ">>> ";
        
        if (!std::getline(std::cin, line)) {
            break;
        }
        
        // Trim whitespace
        const size_t start = line.find_first_not_of(" \t\r\n");
        if (start == std::string::npos) {
            continue;
        }
        line = line.substr(start);
        
        // Check for commands
        if (line == "exit" || line == "quit") {
            std::cout << "Goodbye!\n";
            break;
        }
        
        if (line == "help") {
            std::cout << "Kaynat++ REPL Commands:\n";
            std::cout << "  exit, quit  - Exit the REPL\n";
            std::cout << "  help        - Show this help message\n";
            std::cout << "  clear       - Clear the screen\n";
            std::cout << "\nEnter Kaynat++ statements to execute them.\n";
            continue;
        }
        
        if (line == "clear") {
            std::cout << "\033[2J\033[1;1H";
            continue;
        }
        
        try {
            // TODO: Integrate lexer, parser, and interpreter
            std::cout << "TODO: Execute: " << line << "\n";
            
        } catch (const KaynatError& e) {
            std::cerr << e.formatted_message() << "\n";
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << "\n";
        }
    }
}

void run_file(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw FileError(filename, "file not found", 0, 0);
    }
    
    std::ostringstream buffer;
    buffer << file.rdbuf();
    const std::string source = buffer.str();
    
    if (source.empty()) {
        throw FileError(filename, "file is empty", 0, 0);
    }
    
    try {
        // TODO: Integrate lexer, parser, and interpreter
        std::cout << "TODO: Execute file: " << filename << "\n";
        std::cout << "Source length: " << source.length() << " bytes\n";
        
    } catch (const KaynatError& e) {
        std::cerr << e.formatted_message() << "\n";
        throw;
    }
}

} // namespace kaynat

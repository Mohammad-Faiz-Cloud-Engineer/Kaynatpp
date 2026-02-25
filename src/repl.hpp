/**
 * @file repl.hpp
 * @brief Interactive REPL for Kaynat++
 * 
 * Provides a Read-Eval-Print Loop for interactive Kaynat++ programming.
 */

#pragma once

#include <string>

namespace kaynat {

/**
 * @brief Start the interactive REPL
 * 
 * Runs an interactive shell where users can type Kaynat++ statements
 * and see results immediately. Supports multi-line input and history.
 * 
 * Commands:
 * - exit: Exit the REPL
 * - help: Show help message
 * - clear: Clear the screen
 */
void run_repl();

/**
 * @brief Execute a Kaynat++ source file
 * @param filename Path to .kn file
 * 
 * Reads, parses, and executes a complete Kaynat++ program from file.
 * Throws KaynatError on compilation or runtime errors.
 */
void run_file(const std::string& filename);

} // namespace kaynat

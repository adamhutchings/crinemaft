/**
 * Various utilities for Crinemaft.
 */

#pragma once

#include <fstream>
#include <string>
#include <sstream>

namespace util {

/**
 * Get the full source of a file as a string - inefficient for large files, use
 * for smaller ones like shaders.
 */
std::string get_full_source(std::ifstream& file);

}

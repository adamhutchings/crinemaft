#include "util.h"

namespace util {

std::string get_full_source(std::ifstream& file) {
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

}

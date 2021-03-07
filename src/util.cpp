#include "util.h"

namespace util {

std::string get_full_source(std::ifstream const& file) {
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

}

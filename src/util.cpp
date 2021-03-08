#include "util.h"

namespace util {

std::string get_full_source(std::ifstream const& file) {
    std::stringstream buffer;
    buffer << file.rdbuf() << "\0";
    std::string shaderCode = buffer.str().c_str();
    return shaderCode;
}

}

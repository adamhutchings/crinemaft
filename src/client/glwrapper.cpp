#include "glwrapper.h"

namespace {

    // The window handle
    GLFWwindow* wn;

    // How many characters an error message can be max
    int const gl_error_len = 512;

}

namespace cmgl {

void init() {
    glfwInit();
#ifdef __APPLE__
    glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif // __APPLE__
}

void cleanup() {
    glfwTerminate();
}

void create_window() {
    wn = glfwCreateWindow(500, 500, "Crinemaft", NULL, NULL);
    glfwMakeContextCurrent(wn);
}

void update_window() {
    while (!glfwWindowShouldClose(wn)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glfwSwapBuffers(wn);
        glfwPollEvents();
    }
}

bool window_open() {
    return !glfwWindowShouldClose(wn);
}

Shader::Shader(std::string name) {

    std::string vpath = std::string("src/shader/") + name + "_vert.glsl";
    std::string fpath = std::string("src/shader/") + name + "_frag.glsl";
    char const* vsrc = util::get_full_source(std::ifstream(vpath)).c_str();
    char const* fsrc = util::get_full_source(std::ifstream(fpath)).c_str();

    int success;
    char error_log[gl_error_len];

    // Compile vertex shader
    int vshad = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vshad, 1, &vsrc, NULL);
    glCompileShader(vshad);
    glGetShaderiv(vshad, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vshad, gl_error_len, NULL, error_log);
        std::cerr << "Error compiling" << vpath << ":\n" << error_log << "\n";
        exit(-1);
    }

    // Compile fragment shader
    int fshad = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(fshad, 1, &fsrc, NULL);
    glCompileShader(fshad);
    glGetShaderiv(fshad, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fshad, gl_error_len, NULL, error_log);
        std::cerr << "Error compiling" << fpath << ":\n" << error_log << "\n";
        exit(-1);
    }

    // link shaders
    int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vshad);
    glAttachShader(shaderProgram, fshad);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, gl_error_len, NULL, error_log);
        std::cerr << "Error linking" << name << ":\n" << error_log << "\n";
        exit(-1);
    }
    glDeleteShader(vshad);
    glDeleteShader(fshad);

    this->shaderID = shaderProgram;

}

void Shader::bind() {
    glUseProgram(shaderID);
}

void Shader::unbind() {
    glUseProgram(0);
}

void Shader::destroy() {
    glDeleteProgram(shaderID);
}

}  // namespace cmgl

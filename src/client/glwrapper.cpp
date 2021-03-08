#include "glwrapper.h"

namespace {

    // The window handle
    GLFWwindow* wn;

    // How many characters an error message can be max
    int const gl_error_len = 512;

    float vertices[] = {
        // positions         // colors
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 

    };

    cmgl::Shader* sh;

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
    sh->destroy();
    delete sh;
    glfwTerminate();
}

void create_window() {
    wn = glfwCreateWindow(500, 500, "Crinemaft", NULL, NULL);
    glfwMakeContextCurrent(wn);
    sh = new Shader("block");
    sh->bind();
}

void update_window() {
    while (!glfwWindowShouldClose(wn)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glfwSwapBuffers(wn);
        auto vs = load_vertices(sizeof vertices, vertices);
        vs.draw();
        unload_vertices(vs);
        glfwPollEvents();
    }
}

bool window_open() {
    return !glfwWindowShouldClose(wn);
}

Shader::Shader(std::string name) {

    std::string vpath = std::string("src/shader/") + name + "_vert.glsl";
    std::string fpath = std::string("src/shader/") + name + "_frag.glsl";
    std::string vsss = util::get_full_source(std::ifstream(vpath));
    std::string fsss = util::get_full_source(std::ifstream(fpath));
    char const* vsrc = vsss.c_str();
    char const* fsrc = fsss.c_str();
    int success;
    char error_log[gl_error_len];

    // Compile vertex shader
    int vshad = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vshad, 1, &vsrc, NULL);
    glCompileShader(vshad);
    glGetShaderiv(vshad, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vshad, gl_error_len, NULL, error_log);
        std::cerr << "Error compiling " << vpath << ":\n" << error_log << "\n";
        exit(-1);
    }

    // Compile fragment shader
    int fshad = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fshad, 1, &fsrc, NULL);
    glCompileShader(fshad);
    glGetShaderiv(fshad, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fshad, gl_error_len, NULL, error_log);
        std::cerr << "Error compiling " << fpath << ":\n" << error_log << "\n";
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
        std::cerr << "Error linking " << name << ":\n" << error_log << "\n";
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

VertexSet load_vertices(int num, float* vertices) {
    unsigned int vbo, vao;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    VertexSet vs;
    vs.vao = vao;
    vs.vbo = vbo;
    return vs;
}

void unload_vertices(VertexSet vs) {
    glDeleteVertexArrays(1, &(vs.vao));
    glDeleteBuffers(1, &(vs.vbo));
}

void VertexSet::draw() {
    glBindVertexArray(this->vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

}  // namespace cmgl

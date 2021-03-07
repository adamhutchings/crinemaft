#include "glwrapper.h"

namespace {

    // The window handle
    GLFWwindow* wn;

}

namespace cmgl {

void init() {
    glfwInit();
#ifdef __APPLE__
    glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 2);
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

}  // namespace cmgl

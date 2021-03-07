#include <glinc.h>

int main(int argc, char** argv) {
    glfwInit();
    auto* wn = glfwCreateWindow(500, 500, "Crinemaft", NULL, NULL);
    glfwMakeContextCurrent(wn);
    while (!glfwWindowShouldClose(wn)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glfwSwapBuffers(wn);
        glfwPollEvents();
    }
    glfwTerminate();
}
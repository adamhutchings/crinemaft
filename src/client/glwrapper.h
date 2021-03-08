/**
 * OpenGL / GLFW wrapper - a uniform interface which should include all
 * OS-specific rendering / windowing capabilities.
 */

#pragma once

#include <iostream>
#include <string>

/**
 * OpenGL is deprecated on Apple.
 */
#ifdef __APPLE__
    #define GL_SILENCE_DEPRECATION
#endif // __APPLE__

#define GLFW_INCLUDE_GLCOREARB

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#ifdef __APPLE__
    #include <OpenGL/gl3.h>
#else
    #include <GL/gl3.h>
#endif // __APPLE__

#include <util.h>

// Crinemaft GL
namespace cmgl {

    //// WINDOWING ////
    void init();
    void cleanup();

    void create_window();
    void update_window();

    bool window_open();

    //// SHADERS ////
    class Shader {
    private:
        int shaderID;
    public:
        Shader(std::string name);
        void bind();
        void unbind();
        void destroy();
    };

}

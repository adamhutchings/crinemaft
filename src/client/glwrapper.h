/**
 * OpenGL / GLFW wrapper - a uniform interface which should include all
 * OS-specific rendering / windowing capabilities.
 */

#pragma once

/**
 * OpenGL is deprecated on Apple.
 */
#ifdef __APPLE__
    #define GL_SILENCE_DEPRECATION
#endif // __APPLE__

#define GLFW_INCLUDE_GLCOREARB

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

// Crinemaft GL
namespace cmgl {

    void init();
    void cleanup();

    void create_window();
    void update_window();

    bool window_open();

}

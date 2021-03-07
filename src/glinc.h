/**
 * OpenGL / GLFW include - things like this may work differently on different
 * operating systems.
 */

#pragma once

#ifdef __APPLE__
    #define GL_SILENCE_DEPRECATION
#endif // __APPLE__

#define GLFW_INCLUDE_GLCOREARB

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

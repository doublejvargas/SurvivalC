#pragma once

#include <GL/glew.h>
#include <iostream>

// Macros that help with debugging opengl function calls
#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

// Functions that help with debugging opengl function calls
void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);
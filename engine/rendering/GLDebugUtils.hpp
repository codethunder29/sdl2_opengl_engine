#ifndef __GL_DEBUG_UTILS__
#define __GL_DEBUG_UTILS__
// #pragma once

#include <iostream>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <string>
#include <signal.h>

// debug tools for debugging opengl
#define ASSERT(x) if(!(x)) raise(SIGTRAP);
#define GLDebugCall(x) GLClearError();\
                   x;\
                   ASSERT(GLFindError(#x, __FILE__, __LINE__))

// #define GLErrorLogStart() GLClearError();
// #define GLErrorLogEnd() ASSERT(GLLogErrors())

static void GLClearError()
{
    while(glGetError() != GL_NO_ERROR);
}

static std::string GLParseError(Uint32 error)
{
    std::string errorMsg = "";
    switch (error)
    {
    case GL_INVALID_ENUM:
        errorMsg = "GL INVALID ENUM";
        break;

    case GL_INVALID_VALUE:
        errorMsg = "GL INVALID VALUE";
        break;

    case GL_INVALID_OPERATION:
        errorMsg = "GL INVALID OPERATION";
        break;

    case GL_INVALID_FRAMEBUFFER_OPERATION:
        errorMsg = "GL INVALID OPERATION";
        break;

    case GL_OUT_OF_MEMORY:
        errorMsg = "GL OUT OF MEMORY";
        break;
    
    // if error is opengl 4.x+ specific
    default:
        errorMsg = std::to_string(error);
        break;
    }

    return errorMsg;
}

static bool GLFindError(const char* function, const char* file, int line)
{
    while(Uint32 error = glGetError())
    {
        std::string errorMsg = GLParseError(error);
        std::cout << "OPENGL ERROR (" << errorMsg << ") in " << function << "\n" << file << ":" << line << std::endl;
        return false;
    }

    return true;
}

// bool GLLogErrors()
// {
//     Uint16 count = 0;
//     bool noErrors = true;
//     Uint32 error = glGetError();

//     while(error != GL_NO_ERROR)
//     {
//         std::string errorMsg = GLParseError(error);
//         std::cout << count << ": " << errorMsg << std::endl;
//         noErrors = false;
//         count++;
//         error = glGetError();
//     }

//     return noErrors;
// }

#endif
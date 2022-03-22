#include "Shader.hpp"

std::string Shader::loadShader(std::string path)
{
    FILE* file = fopen(path.c_str(), "r");
    GLint chr;
    std::string shader = "";

    if(file == nullptr)
    {
        std::cout << path << " is invalid path" << std::endl;
        return "";
    }

    chr = fgetc(file);
    while(chr != EOF)
    {
        shader += chr;
        chr = fgetc(file);
    }

    fclose(file);
    return shader;
}

Shader::Shader(std::string path, GLuint type)
{
    id = glCreateShader(type);
    this->type = type;
    shaderSource = loadShader(path);
}

Shader::~Shader()
{
    glDeleteShader(id);
}

void Shader::compile()
{
    const char* src = shaderSource.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    GLint result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);

    if(result == GL_FALSE)
    {
        GLint length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* msg = (char*)alloca(length * sizeof(char));  // allocating on stack
        glGetShaderInfoLog(id, length, &length, msg);

        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader" << std::endl;
        std::cout << msg << std::endl;

        glDeleteShader(id);
    }
}

GLuint Shader::getID()
{
    return id;
}
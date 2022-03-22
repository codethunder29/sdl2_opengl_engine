#include <GL/glew.h>
#include <iostream>
#include <string>

class Shader
{
private:
    GLuint id;
    std::string shaderSource;
    GLuint type;

    std::string loadShader(std::string path);

public:
    Shader(std::string path, GLuint type);
    ~Shader();

    void compile();
    GLuint getID();
};
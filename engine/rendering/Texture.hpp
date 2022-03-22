#include <GL/glew.h>
#include <string>
#include <iostream>
#include "stb_image.h"

class Texture
{
private:
    GLuint id;
    GLint width;
    GLint height;
    GLint bpp;  // bits per pixel
    GLubyte* pixelBuffer;

public:
    Texture();
    ~Texture();

    void bind(GLint slot=0);
    void unbind() const;
    void loadFromFile(std::string path);
    GLuint getID() const;
    GLint getSlot() const;
};
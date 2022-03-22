#include "Texture.hpp"
#include "GLDebugUtils.hpp"

Texture::Texture()
{
    width = 0;
    height = 0;

    glGenTextures(1, &id);
}

Texture::~Texture()
{
    glDeleteTextures(1, &id);
}

void Texture::bind(GLint slot)
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::loadFromFile(std::string path)
{
    stbi_set_flip_vertically_on_load(1);  // doing this because opengl is idiot and thinks bottom left is 0,0
    pixelBuffer = stbi_load(path.c_str(), &width, &height, &bpp, 4);  // loading image with rbga

    if(pixelBuffer == nullptr)
    {
        std::cout << "Error: failed to load " + path << std::endl;
        return;
    }

    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);  // minimizing algorithm for texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);  // same as above but for maximizing
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);  // 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    GLDebugCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixelBuffer));
    GLDebugCall(glBindTexture(GL_TEXTURE_2D, 0));

    // deleting loaded image
    stbi_image_free(pixelBuffer);
}

GLuint Texture::getID() const
{
    return id;
}
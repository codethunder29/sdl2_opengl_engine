#ifndef __INDEX_BUFFER__
#define __INDEX_BUFFER__

#include <GL/glew.h>

class IndexBuffer
{
private:
    GLuint id;
    GLushort count;

public:
    IndexBuffer();
    ~IndexBuffer();

    void setData(const GLushort* data, GLuint count, GLenum usage);
    void bind() const;
    void unbind() const;
    GLushort getCount() const;
};

#endif
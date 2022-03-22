#ifndef __VERTEX_BUFFER__
#define __VERTEX_BUFFER__

#include <GL/glew.h>

class VertexBuffer
{
private:
    GLuint id;

public:
    VertexBuffer();
    ~VertexBuffer();

    void setData(const void* data, GLuint size, GLenum usage);
    void bind() const;
    void unbind() const;
};

#endif
#include "IndexBuffer.hpp"


IndexBuffer::IndexBuffer()
{
    glGenBuffers(1, &id);
    count = 0;
}

IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &id);
}

void IndexBuffer::setData(const GLushort* data, GLuint count, GLenum usage)
{
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLushort), data, usage);
    this->count = count;
}

void IndexBuffer::bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void IndexBuffer::unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

GLushort IndexBuffer::getCount() const
{
    return count;
}
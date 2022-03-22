#include "VertexBufferLayout.hpp"

VertexBufferLayout::VertexBufferLayout()
{
    stride = 0;
}

template <>
void VertexBufferLayout::add<GLdouble>(GLuint count, GLboolean normalized)
{
    elements.push_back({GL_FLOAT, count, normalized, sizeof(GLdouble)});
    stride += count * sizeof(GLdouble);
}

template <>
void VertexBufferLayout::add<GLfloat>(GLuint count, GLboolean normalized)
{
    elements.push_back({GL_FLOAT, count, normalized, sizeof(GLfloat)});
    stride += count * sizeof(GLfloat);
}

template <>
void VertexBufferLayout::add<GLint>(GLuint count, GLboolean normalized)
{
    elements.push_back({GL_INT, count, normalized, sizeof(GLint)});
    stride += count * sizeof(GLint);
}

template <>
void VertexBufferLayout::add<GLshort>(GLuint count, GLboolean normalized)
{
    elements.push_back({GL_SHORT, count, normalized, sizeof(GLshort)});
    stride += count * sizeof(GLshort);
}

template <>
void VertexBufferLayout::add<GLbyte>(GLuint count, GLboolean normalized)
{
    elements.push_back({GL_BYTE, count, normalized, sizeof(GLbyte)});
    stride += count * sizeof(GLbyte);
}

template <>
void VertexBufferLayout::add<GLuint>(GLuint count, GLboolean normalized)
{
    elements.push_back({GL_UNSIGNED_INT, count, normalized, sizeof(GLuint)});
    stride += count * sizeof(GLuint);
}

template <>
void VertexBufferLayout::add<GLushort>(GLuint count, GLboolean normalized)
{
    elements.push_back({GL_UNSIGNED_SHORT, count, normalized, sizeof(GLushort)});
    stride += count * sizeof(GLushort);
}

template <>
void VertexBufferLayout::add<GLubyte>(GLuint count, GLboolean normalized)
{
    elements.push_back({GL_UNSIGNED_BYTE, count, normalized, sizeof(GLubyte)});
    stride += count * sizeof(GLubyte);
}

void VertexBufferLayout::clear()
{
    elements.clear();
    stride = 0;
}

const std::vector<VertexLayoutElement>& VertexBufferLayout::getElements() const
{
    return elements;
}

GLsizei VertexBufferLayout::getStride() const
{
    return stride;
}
#include "VertexArray.hpp"
#include <iostream>

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &id);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &id);
};

void VertexArray::bind() const
{
    glBindVertexArray(id);
}

void VertexArray::unbind() const
{
    glBindVertexArray(0);
}

void VertexArray::addBuffer(const VertexBuffer& vb, const VertexBufferLayout& vbl)
{
    bind();
    vb.bind();
    
    const auto& elements = vbl.getElements();
    GLuint offset = 0;

    for(GLuint i=0; i<elements.size(); i++)
    {
        const auto& element = elements[i];
        glEnableVertexAttribArray(i);

        if(element.type == GL_INT || element.type == GL_UNSIGNED_INT || element.type == GL_SHORT || element.type == GL_UNSIGNED_SHORT || element.type == GL_BYTE || element.type == GL_UNSIGNED_BYTE)
            glVertexAttribIPointer(i, element.count, element.type, vbl.getStride(), (const void*)offset);
        else
            glVertexAttribPointer(i, element.count, element.type, element.normalized, vbl.getStride(), (const void*)offset);

        offset += element.count * element.typeSize;

    }
}
    
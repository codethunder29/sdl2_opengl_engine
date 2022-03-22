#include "ShaderProgram.hpp"

ShaderProgram::ShaderProgram()
{
    id = glCreateProgram();
}

ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(id);
}

void ShaderProgram::bind() const
{
    glUseProgram(id);
}

void ShaderProgram::unbind() const
{
    glUseProgram(0);
}

void ShaderProgram::linkShaders() const
{
    GLint result;
    glLinkProgram(id);

    // checking if linking failed
    glGetProgramiv(id, GL_LINK_STATUS, &result);
    if(result == GL_FALSE)
    {
        GLint length;
        glGetProgramiv(id, GL_INFO_LOG_LENGTH, &length);
        char* msg = (char*)alloca(length * sizeof(char));  // allocating on stack
        glGetProgramInfoLog(id, length, &length, msg);

        std::cout << msg << std::endl;
        glDeleteProgram(id);
    }

    glValidateProgram(id);

    // checking if validation failed
    glGetProgramiv(id, GL_VALIDATE_STATUS, &result);
    if(result == GL_FALSE)
    {
        GLint length;
        glGetProgramiv(id, GL_INFO_LOG_LENGTH, &length);
        char* msg = (char*)alloca(length * sizeof(char));  // allocating on stack
        glGetProgramInfoLog(id, length, &length, msg);

        std::cout << msg << std::endl;
        glDeleteProgram(id);
    }
}

void ShaderProgram::addShader(Shader& shader)
{
    glAttachShader(id, shader.getID());
}

GLint ShaderProgram::getUniformLocation(std::string name)
{
    GLint location;
    auto it = uniforms.find(name);

    if(it == uniforms.end())
    {
        location = glGetUniformLocation(id, name.c_str());

        if(location == -1)
        {
            std::cout << "Error: uniform " << name << " may not exist" << std::endl;
            return location;
        }

        uniforms.insert({name, location});
    }
    else
    {
        location = it->second;
    }

    return location;
}



// ------------SCALARS + VECTORS------------
// 1D
template <>
void ShaderProgram::setUniform<GLdouble>(std::string name, GLdouble val0)
{
    GLint location = getUniformLocation(name);

    if(location == -1)
        return;

    glUniform1d(location, val0);
}

template <>
void ShaderProgram::setUniform<GLfloat>(std::string name, GLfloat val0)
{
    GLint location = getUniformLocation(name);

    if(location == -1)
        return;

    glUniform1f(location, val0);
}

template <>
void ShaderProgram::setUniform<GLint>(std::string name, GLint val0)
{
    GLint location;
    getUniformLocation(name);

    if(location == -1)
        return;

    glUniform1i(location, val0);
}

template <>
void ShaderProgram::setUniform<GLuint>(std::string name, GLuint val0)
{
    GLint location = getUniformLocation(name);

    if(location == -1)
        return;

    glUniform1ui(location, val0);
}


// 2D
template <>
void ShaderProgram::setUniform<GLdouble>(std::string name, GLdouble val0, GLdouble val1)
{
    GLint location = getUniformLocation(name);

    if(location == -1)
        return;

    glUniform2d(location, val0, val1);
}

template <>
void ShaderProgram::setUniform<GLfloat>(std::string name, GLfloat val0, GLfloat val1)
{
    GLint location = getUniformLocation(name);

    if(location == -1)
        return;

    glUniform2f(location, val0, val1);
}

template <>
void ShaderProgram::setUniform<GLint>(std::string name, GLint val0, GLint val1)
{
    GLint location = getUniformLocation(name);

    if(location == -1)
        return;

    glUniform2i(location, val0, val1);
}

template <>
void ShaderProgram::setUniform<GLuint>(std::string name, GLuint val0, GLuint val1)
{
    GLint location = getUniformLocation(name);

    if(location == -1)
        return;

    glUniform2ui(location, val0, val1);
}


// 3D
template <>
void ShaderProgram::setUniform<GLdouble>(std::string name, GLdouble val0, GLdouble val1, GLdouble val2)
{
    GLint location = getUniformLocation(name);

    if(location == -1)
        return;

    glUniform3d(location, val0, val1, val2);
}

template <>
void ShaderProgram::setUniform<GLfloat>(std::string name, GLfloat val0, GLfloat val1, GLfloat val2)
{
    GLint location = getUniformLocation(name);

    if(location == -1)
        return;

    glUniform3f(location, val0, val1, val2);
}

template <>
void ShaderProgram::setUniform<GLint>(std::string name, GLint val0, GLint val1, GLint val2)
{
    GLint location = getUniformLocation(name);

    if(location == -1)
        return;

    glUniform3i(location, val0, val1, val2);
}

template <>
void ShaderProgram::setUniform<GLuint>(std::string name, GLuint val0, GLuint val1, GLuint val2)
{
    GLint location = getUniformLocation(name);

    if(location == -1)
        return;

    glUniform3ui(location, val0, val1, val2);
}


// 4D
template <>
void ShaderProgram::setUniform<GLdouble>(std::string name, GLdouble val0, GLdouble val1, GLdouble val2, GLdouble val3)
{
    GLint location = getUniformLocation(name);

    if(location == -1)
        return;

    glUniform4d(location, val0, val1, val2, val3);
}

template <>
void ShaderProgram::setUniform<GLfloat>(std::string name, GLfloat val0, GLfloat val1, GLfloat val2, GLfloat val3)
{
    GLint location = getUniformLocation(name);

    if(location == -1)
        return;

    glUniform4f(location, val0, val1, val2, val3);
}

template <>
void ShaderProgram::setUniform<GLint>(std::string name, GLint val0, GLint val1, GLint val2, GLint val3)
{
    GLint location = getUniformLocation(name);

    if(location == -1)
        return;

    glUniform4i(location, val0, val1, val2, val3);
}

template <>
void ShaderProgram::setUniform<GLuint>(std::string name, GLuint val0, GLuint val1, GLuint val2, GLuint val3)
{
    GLint location = getUniformLocation(name);

    if(location == -1)
        return;

    glUniform4ui(location, val0, val1, val2, val3);
}



// ------------ARRAYS------------
// 1D
template <>
void ShaderProgram::setUniformArray1D<GLdouble>(std::string name, GLsizei count, GLdouble* arr)
{
    GLint location = getUniformLocation(name);

    if(location == -1)
        return;

    glUniform1dv(location, count, arr);
}

template <>
void ShaderProgram::setUniformArray1D<GLfloat>(std::string name, GLsizei count, GLfloat* arr)
{
    GLint location = getUniformLocation(name);

    if(location == -1)
        return;

    glUniform1fv(location, count, arr);
}

template <>
void ShaderProgram::setUniformArray1D<GLint>(std::string name, GLsizei count, GLint* arr)
{
    GLint location = getUniformLocation(name);

    if(location == -1)
        return;

    glUniform1iv(location, count, arr);
}

template <>
void ShaderProgram::setUniformArray1D<GLuint>(std::string name, GLsizei count, GLuint* arr)
{
    GLint location = getUniformLocation(name);

    if(location == -1)
        return;

    glUniform1uiv(location, count, arr);
}

// template <>
void ShaderProgram::setUniformMatrix4(std::string name, GLboolean transpose, glm::mat4& mat)
{
    GLint location = getUniformLocation(name);

    if(location == -1)
        return;

    glUniformMatrix4fv(location, 1, transpose, glm::value_ptr(mat));
}

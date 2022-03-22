#include "Shader.hpp"
#include <unordered_map>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ShaderProgram
{
private:
    GLuint id;
    std::unordered_map<std::string, GLuint> uniforms;

public:
    ShaderProgram();
    ~ShaderProgram();

    void bind() const;
    void unbind() const;
    void linkShaders() const;
    void addShader(Shader& shader);
    GLint getUniformLocation(std::string name);

    template <typename T>
    void setUniform(std::string name, T val0);

    template <typename T>
    void setUniform(std::string name, T val0, T val1);

    template <typename T>
    void setUniform(std::string name, T val0, T val1, T val2);

    template <typename T>
    void setUniform(std::string name, T val0, T val1, T val2, T val3);

    template <typename T>
    void setUniformArray1D(std::string name, GLsizei count, T* arr);

    // template <typename T>
    void setUniformMatrix4(std::string name, GLboolean transpose, glm::mat4& mat);

    // // need to implement the functions below
    // template <typename T>
    // void setUniformArray(std::string name, GLsizei count, T* arr);

    // template <typename T>
    // void setUniformArray(std::string name, GLsizei count, T* arr);

    // template <typename T>
    // void setUniformArray(std::string name, GLsizei count, T* arr);
};
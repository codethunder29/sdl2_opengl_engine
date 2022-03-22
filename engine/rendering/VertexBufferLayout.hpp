#include <GL/glew.h>
#include <vector>

struct VertexLayoutElement
{
    GLenum type;
    GLuint count;
    GLboolean normalized;
    GLuint typeSize;
};

class VertexBufferLayout
{
private:
    std::vector<VertexLayoutElement> elements;
    GLsizei stride;

public:
    VertexBufferLayout();

    template <typename T>
    void add(GLuint count, GLboolean normalized);

    void clear();
    const std::vector<VertexLayoutElement>& getElements() const;
    GLsizei getStride() const;
};
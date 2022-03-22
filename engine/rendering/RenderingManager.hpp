#ifndef __RENDERING_MANAGER__
#define __RENDERING_MANAGER__

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <iostream>
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include "ShaderProgram.hpp"
#include "Texture.hpp"

#define TEX_SLOT_BUFFER_SIZE 10
#define MAX_TEXTURE_SLOTS 3  // NOTE: this only used by availableTexSlot and not to define texture slot buffer size
#define TEX_BATCH_INDEX 0

//NOTE: remove SDL color to not be depended on SDL

// position, texture coords, texture coords offset, color, texture slot
struct Vertex
{
    GLfloat x, y;
    GLfloat texX, texY;
    GLfloat scaleX, scaleY;
    GLfloat angle;
    GLfloat pivX, pivY;  // rotation pivot point
    GLuint color;
    GLint tSlot;
};

struct Line
{
    GLfloat x0, y0;
    GLfloat x1, y1;
};

struct Triangle
{
    GLfloat x0, y0;
    GLfloat x1, y1;
    GLfloat x2, y2;
};

struct Rect
{
    GLfloat x, y;
    GLfloat w, h;
};

struct Circle
{
    GLfloat x, y;
    GLfloat radius;
};

enum renderingModes
{
    RM_SOFTWARE,
    RM_OPENGL
};

class RenderingManager
{
private:
    SDL_Window* window;
    SDL_GLContext context; 
    ShaderProgram* sp;
    VertexArray* va;
    VertexBuffer* vb;
    IndexBuffer* ib;
    VertexBufferLayout vbl;
    std::vector<Vertex> vertexData;
    std::vector<GLushort> indexData;

    GLint screenWidth;
    GLint screenHeight;
    GLubyte rendMode;
    GLuint indexOffset;  // used for batch rendering to offset values for the index buffer
    GLubyte lastDrawType;  // used for batch render similar types of geometry e.g. triangles
    GLuint lastTexture;  // used for checking if need to bind a new texture in the GPU if no then reusing current texture in GPU
    GLuint renderColor;
    GLfloat angle;  // used for drawing object in a certain angle (used in model matrix)
    GLfloat scaleX, scaleY;  // used for drawing object in certain scale (used in model matrix)
    GLfloat camPosX, camPosY;  // used for camera offsetting (used in view matrix)
    GLfloat camAngle;  // used for camera rotation (used in view matrix)
    GLfloat camScaleX, camScaleY;  // used for camera zoom (used in view matrix)
    GLint textureSlots;  // the number of texture slots available on the GPU
    GLubyte availableTexSlot;  // the current availble texture slot on the GPU
    GLint textureSlotBuffer[10];  // an array of texture slots, used in the fragment shader to map textures to vertices
    GLint textureSlotMap[10];  // an array

    GLushort drawCalls;
    glm::mat4 PV;
    glm::mat4 projMat;
    glm::mat4 viewMat;
    glm::mat4 camRotate;
    glm::mat4 camScale;
    glm::mat4 camOffset;

    void drawBatch();
    GLint findTextureSlot(GLint textureID);  // this function is for finding texture id's in 
    GLuint rgba2color(GLubyte r, GLubyte g, GLubyte b, GLubyte a);
    glm::mat4 rotateMat(GLfloat angle);
    glm::mat4 scaleAroundPoint(GLfloat scaleX, GLfloat scaleY);

    void printMat(glm::mat4& mat);
public:
    RenderingManager();

    void init(SDL_Window* window);
    void clean();
    void setVsync(bool value);
    void updateRenderSize();
    void clear(SDL_Color color);
    void display();
    // void setShaderProgram(ShaderProgram* sp);
    void setColor(SDL_Color color);
    void setAngle(GLfloat angle);
    void setScale(GLfloat x, GLfloat y);
    void setCamPos(GLfloat x, GLfloat y);
    void setCamAngle(GLfloat angle);
    void setCamScale(GLfloat x, GLfloat y);
    void drawLine(Line& line);
    void drawTriangle(Triangle& triangle);
    void drawRect(Rect& rect);
    void fillTriangle(Triangle& triangle);
    void fillRect(Rect& rect);
    // void fillCircle();
    void drawTexture(Rect& rect, Texture& texture);


};

#endif
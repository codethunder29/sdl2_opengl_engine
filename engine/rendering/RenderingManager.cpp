#include "RenderingManager.hpp"

RenderingManager::RenderingManager()
{
    window = nullptr;
    indexOffset = 0;
    lastDrawType = 0;
    lastTexture = 0;
    renderColor = rgba2color(0, 0, 0, 0);
    angle = 0;
    scaleX = 1;
    scaleY = 1;
    camPosX = 0;
    camPosY = 0;
    camAngle = 0;
    camScaleX = 1;
    camScaleY = 1;
    textureSlots = 0;
    availableTexSlot = 0;  // reserving index 0 for texture atlas

    drawCalls = 0;
    
    // initializing the slot buffer since it doesn't change
    for(GLuint i=0; i<TEX_SLOT_BUFFER_SIZE; i++)
    {
        textureSlotBuffer[i] = i;
    }
}

void RenderingManager::init(SDL_Window* window)
{
    this->window = window;

    SDL_GetWindowSize(window, &screenWidth, &screenHeight);

    context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, context);

    glewExperimental = GL_TRUE;  // heard windows doesn't work without experimental
    if(glewInit() != GLEW_OK)
    {
        std::cout << "Unable to initialize OpenGL!" << std::endl;
        exit(1);
    }

    std::cout << glGetString(GL_VERSION) << std::endl;
    sp = new ShaderProgram();
    va = new VertexArray();
    vb = new VertexBuffer();
    ib = new IndexBuffer();
    
    Shader vs("../vertexShader.vert", GL_VERTEX_SHADER);
    Shader fs("../fragmentShader.frag", GL_FRAGMENT_SHADER);

    vs.compile();
    fs.compile();

    sp->addShader(vs);
    sp->addShader(fs);
    sp->linkShaders();
    sp->bind();

    vbl.clear();
    vbl.add<GLfloat>(2, GL_FALSE);
    vbl.add<GLfloat>(2, GL_FALSE);
    vbl.add<GLfloat>(2, GL_FALSE);
    vbl.add<GLfloat>(1, GL_FALSE);
    vbl.add<GLfloat>(2, GL_FALSE);
    vbl.add<GLuint>(1, GL_FALSE);
    vbl.add<GLint>(1, GL_FALSE);

    projMat = glm::ortho(-screenWidth/2.0f, screenWidth/2.0f, -screenHeight/2.0f, screenHeight/2.0f, -1.0f , 1.0f);
    camOffset = glm::mat4(1.0f);  // creating an identity matrix

    // setting the uniforms here because they won't change
    sp->setUniformArray1D<GLint>("uTextures", TEX_SLOT_BUFFER_SIZE, textureSlotBuffer);

    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &textureSlots);

    if(textureSlots > MAX_TEXTURE_SLOTS)
        textureSlots = MAX_TEXTURE_SLOTS;


    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void RenderingManager::clean()
{
    delete sp;
    delete va;
    delete vb;
    delete ib;
    SDL_GL_DeleteContext(context);
}

void RenderingManager::setVsync(bool value)
{
    // maybe modify it in the future to work with adaptive vsync (value = -1)
    if(SDL_GL_SetSwapInterval(value) != 0)
        std::cout << SDL_GetError() << std::endl;
}

void RenderingManager::updateRenderSize()
{
    SDL_GetWindowSize(window, &screenWidth, &screenHeight);
    glViewport(0, 0, screenWidth, screenHeight);
    projMat = glm::ortho(-screenWidth/2.0f, screenWidth/2.0f, -screenHeight/2.0f, screenHeight/2.0f, -1.0f , 1.0f);
}

void RenderingManager::clear(SDL_Color color)
{
    drawCalls = 0;
    glClearColor(color.r/255, color.g/255, color.b/255, color.a/255);
    glClear(GL_COLOR_BUFFER_BIT);

    camRotate = rotateMat(camAngle);
    camScale = scaleAroundPoint(camScaleX, camScaleY);
    camOffset[3][0] = -camPosX;
    camOffset[3][1] = -camPosY;

    viewMat = camScale * camOffset;

    PV = projMat * viewMat;
    sp->setUniformMatrix4("uPV", GL_FALSE, PV);
}

void RenderingManager::display()
{
    sp->setUniformArray1D<GLint>("uTextures", TEX_SLOT_BUFFER_SIZE, textureSlotBuffer);
    drawBatch();
    // std::cout << "Draw Calls: " << drawCalls << std::endl;
    SDL_GL_SwapWindow(window);
}

void RenderingManager::setColor(SDL_Color color)
{
    renderColor = rgba2color(color.r, color.g, color.b, color.a);
}

void RenderingManager::setAngle(GLfloat angle)
{
    this->angle = angle;
}

void RenderingManager::setScale(GLfloat x, GLfloat y)
{
    scaleX = x;
    scaleY = y;
}

void RenderingManager::setCamPos(GLfloat x, GLfloat y)
{
    camPosX = x;
    camPosY = y;
}

void RenderingManager::setCamAngle(GLfloat angle)
{
    camAngle = angle;
}

void RenderingManager::setCamScale(GLfloat x, GLfloat y)
{
    camScaleX = x;
    camScaleY = y;
}

void RenderingManager::drawLine(Line& line)
{
    if(lastDrawType != GL_LINES)
        drawBatch();  // draws the last batch to prepare for a new one

    GLfloat centerX = (line.x0 + line.x1)/2;
    GLfloat centerY = (line.y0 + line.y1)/2;

    vertexData.push_back({line.x0, line.y0, 0, 0, scaleX, scaleY, angle, centerX, centerY, renderColor, -1});
    vertexData.push_back({line.x1, line.y1, 0, 0, scaleX, scaleY, angle, centerX, centerY, renderColor, -1});

    indexData.push_back(0 + indexOffset);
    indexData.push_back(1 + indexOffset);

    indexOffset += 2;
    lastDrawType = GL_LINES;
}

void RenderingManager::drawTriangle(Triangle& triangle)
{
    if(lastDrawType != GL_LINES)
        drawBatch();  // draws the last batch to prepare for a new one

    GLfloat centerX = (triangle.x0 + triangle.x1 + triangle.x2)/2;
    GLfloat centerY = (triangle.y0 + triangle.y1 + triangle.y2)/2;

    vertexData.push_back({triangle.x0, triangle.y0, 0, 0, scaleX, scaleY, angle, centerX, centerY, renderColor, -1});
    vertexData.push_back({triangle.x1, triangle.y1, 0, 0, scaleX, scaleY, angle, centerX, centerY, renderColor, -1});
    vertexData.push_back({triangle.x2, triangle.y2, 0, 0, scaleX, scaleY, angle, centerX, centerY, renderColor, -1});

    indexData.push_back(0 + indexOffset);
    indexData.push_back(1 + indexOffset);
    indexData.push_back(0 + indexOffset);
    indexData.push_back(2 + indexOffset);
    indexData.push_back(1 + indexOffset);
    indexData.push_back(2 + indexOffset);

    indexOffset += 3;
    lastDrawType = GL_LINES;
}

void RenderingManager::drawRect(Rect& rect)
{
    if(lastDrawType != GL_LINES)
        drawBatch();  // draws the last batch to prepare for a new one

    GLfloat centerX = rect.x + rect.w/2;
    GLfloat centerY = rect.y + rect.h/2;

    vertexData.push_back({rect.x, rect.y, 0, 0, scaleX, scaleY, angle, centerX, centerY, renderColor, -1});
    vertexData.push_back({rect.x, rect.y + rect.h, 0, 0, scaleX, scaleY, angle, centerX, centerY, renderColor, -1});
    vertexData.push_back({rect.x + rect.w, rect.y, 0, 0, scaleX, scaleY, angle, centerX, centerY, renderColor, -1});
    vertexData.push_back({rect.x + rect.w, rect.y + rect.h, 0, 0, scaleX, scaleY, angle, centerX, centerY, renderColor, -1});

    indexData.push_back(0 + indexOffset);
    indexData.push_back(1 + indexOffset);
    indexData.push_back(0 + indexOffset);
    indexData.push_back(2 + indexOffset);
    indexData.push_back(1 + indexOffset);
    indexData.push_back(3 + indexOffset);
    indexData.push_back(2 + indexOffset);
    indexData.push_back(3 + indexOffset);

    indexOffset += 4;
    lastDrawType = GL_LINES;
}

void RenderingManager::fillTriangle(Triangle& triangle)
{
    if(lastDrawType != GL_TRIANGLES)
        drawBatch();  // draws the last batch to prepare for a new one

    GLfloat centerX = (triangle.x0 + triangle.x1 + triangle.x2)/2;
    GLfloat centerY = (triangle.y0 + triangle.y1 + triangle.y2)/2;

    vertexData.push_back({triangle.x0, triangle.y0, 0, 0, scaleX, scaleY, angle, centerX, centerY, renderColor, -1});
    vertexData.push_back({triangle.x1, triangle.y1, 0, 0, scaleX, scaleY, angle, centerX, centerY, renderColor, -1});
    vertexData.push_back({triangle.x2, triangle.y2, 0, 0, scaleX, scaleY, angle, centerX, centerY, renderColor, -1});

    indexData.push_back(0 + indexOffset);
    indexData.push_back(1 + indexOffset);
    indexData.push_back(2 + indexOffset);

    indexOffset += 3;
    lastDrawType = GL_TRIANGLES;
}

void RenderingManager::fillRect(Rect& rect)
{
    if(lastDrawType != GL_TRIANGLES)
        drawBatch();  // draws the last batch to prepare for a new one

    GLfloat centerX = rect.x + rect.w/2;
    GLfloat centerY = rect.y + rect.h/2;

    vertexData.push_back({rect.x, rect.y, 0, 0, scaleX, scaleY, angle, centerX, centerY, renderColor, -1});
    vertexData.push_back({rect.x, rect.y + rect.h, 0, 0, scaleX, scaleY, angle, centerX, centerY, renderColor, -1});
    vertexData.push_back({rect.x + rect.w, rect.y, 0, 0, scaleX, scaleY, angle, centerX, centerY, renderColor, -1});
    vertexData.push_back({rect.x + rect.w, rect.y + rect.h, 0, 0, scaleX, scaleY, angle, centerX, centerY, renderColor, -1});

    indexData.push_back(0 + indexOffset);
    indexData.push_back(1 + indexOffset);
    indexData.push_back(2 + indexOffset);
    indexData.push_back(1 + indexOffset);
    indexData.push_back(2 + indexOffset);
    indexData.push_back(3 + indexOffset);

    indexOffset += 4;
    lastDrawType = GL_TRIANGLES;
}

void RenderingManager::drawTexture(Rect& rect, Texture& texture)
{
    if(lastDrawType != GL_TRIANGLES || lastTexture != texture.getID())
        drawBatch();

    texture.bind(TEX_BATCH_INDEX);
    lastTexture = texture.getID();

    GLfloat centerX = rect.x + rect.w/2;
    GLfloat centerY = rect.y + rect.h/2;

    vertexData.push_back({rect.x, rect.y, 0, 0, scaleX, scaleY, angle, centerX, centerY, renderColor, TEX_BATCH_INDEX});
    vertexData.push_back({rect.x, rect.y + rect.h, 0, 1, scaleX, scaleY, angle, centerX, centerY, renderColor, TEX_BATCH_INDEX});
    vertexData.push_back({rect.x + rect.w, rect.y, 1, 0, scaleX, scaleY, angle, centerX, centerY, renderColor, TEX_BATCH_INDEX});
    vertexData.push_back({rect.x + rect.w, rect.y + rect.h, 1, 1, scaleX, scaleY, angle, centerX, centerY, renderColor, TEX_BATCH_INDEX});

    indexData.push_back(0 + indexOffset);
    indexData.push_back(1 + indexOffset);
    indexData.push_back(2 + indexOffset);
    indexData.push_back(1 + indexOffset);
    indexData.push_back(2 + indexOffset);
    indexData.push_back(3 + indexOffset);

    indexOffset += 4;
    lastDrawType = GL_TRIANGLES;
}



// helper functions
void RenderingManager::drawBatch()
{
    if(lastDrawType != 0)
    {
        drawCalls++;

        vb->setData(&vertexData[0], sizeof(Vertex) * vertexData.size(), GL_STATIC_DRAW);
        va->addBuffer(*vb, vbl);
        va->bind();

        ib->setData(&indexData[0], indexData.size(), GL_STATIC_DRAW);
        ib->bind();
        
        glDrawElements(lastDrawType, ib->getCount(), GL_UNSIGNED_SHORT, nullptr);
        vertexData.clear();
        indexData.clear();
        indexOffset = 0;
        lastDrawType = 0;
        availableTexSlot = TEX_BATCH_INDEX;
    }
}

GLint RenderingManager::findTextureSlot(GLint textureID)
{
    for(int i=0; i<textureSlots; i++)
    {
        if(textureSlotMap[i] == textureID)
            return i;
    }

    return -1;
}

GLuint RenderingManager::rgba2color(GLubyte r, GLubyte g, GLubyte b, GLubyte a)
{
    GLuint color = r;
    color = color << 8;
    color = color | g;
    color = color << 8;
    color = color | b;
    color = color << 8;

    return color | a;
}

glm::mat4 RenderingManager::rotateMat(GLfloat angle)
{
    glm::mat4 rot =
    {
        cos(angle), sin(angle), 0.0f, 0.0f,
        -sin(angle), cos(angle), 0.0f, 0.0f,
        0.0f, 0.0f, 1, 0.0f,
        0, 0, 0.0f, 1.0f
    };

    return rot;
}

glm::mat4 RenderingManager::scaleAroundPoint(GLfloat scaleX, GLfloat scaleY)
{
    glm::mat4 scale =
    {
        scaleX,       0,          0, 0,
        0,            scaleY,     0, 0,
        0,            0,          1, 0,
        0,            0,          0, 1
    };

    return scale;
}

void RenderingManager::printMat(glm::mat4& mat)
{
    for(int i=0; i<4;i++)
    {
        for(int j=0; j<4;j++)
            std::cout << mat[i][j] << " ";

        std::cout << std::endl;
    }
}
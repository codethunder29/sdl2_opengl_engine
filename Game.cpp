#include "Game.hpp"

MyGame::MyGame(const char *title, int xPos, int yPos, int width, int height) : Engine(title, xPos, yPos, width, height)
{
    angChg = 0;
    scaleX = 1;
    scaleY = 1;
    mAngle = 0;

    for(int x=0; x<50; x++)
    {
        for(int y=0; y<50; y++)
        {
            tiles.push_back({x*20, y*20});
        }
    }
}

MyGame::~MyGame()
{

}

void MyGame::onStart()
{
    rm.setVsync(true);
    tex.loadFromFile("/home/user/Pictures/tank.png");
    tex2.loadFromFile("/home/user/Pictures/slime.png");
    tex3.loadFromFile("/home/user/Pictures/Sprite-0001.png");
    tex4.loadFromFile("/home/user/Pictures/tank2.png");
    tex5.loadFromFile("/home/user/Pictures/Sprite-0001.png");
}

void MyGame::onUpdate()
{
    // cam.angle += camVel.x/10.0f;
    // cam.update();   
    cam.pos += camVel;
    cam.scale += scale;
    mAngle += angChg;
}

void MyGame::onDraw()
{
    rm.clear({0, 0, 0, 255});

    rm.setColor({255,255,255,255});
    // rm.setAngle()
    // rm.fillTriangle()


    float offsetX = 0;//(rand()%210 - 100)/100.0f;
    float offsetY = 0.5;///100.0f;
    Triangle trg;
    Rect r;

    rm.setAngle(mAngle);
    rm.setScale(scaleX, scaleY);

    rm.setCamAngle(cam.angle);
    rm.setCamPos(cam.pos.x, cam.pos.y);
    rm.setCamScale(cam.scale.x, cam.scale.y);

    for(auto tile : tiles)
    {
        r = {tile.x, tile.y, 20, 20};
        rm.drawTexture(r, tex);
        // rm.fillRect(r);
    }

    // for(int i=0; i<1; i++)
    // {
    //     // offsetX = (rand()%400 - 200);
    //     // offsetY = (rand()%300 - 150);
    //     rm.setAngle(mAngle);
    //     rm.setScale(scaleX, scaleY);

        // Rect r = {0,0,70,100};
    //     rm.setColor({rand()%256, rand()%256, rand()%256, rand()%256});

        // rm.drawTexture(r, tex3);
    //     // rm.drawTexture(r, tex);
    // }

    // for(int i=0; i<5000; i++)
    // {
    //     offsetX = (rand()%400+400);
    //     offsetY = (rand()%600);

    //     Rect r = {offsetX,offsetY,70,100};
    //     rm.setColor({rand()%256, rand()%256, rand()%256, rand()%256});

    //     // rm.drawTexture(r, tex3);
    //     rm.drawTexture(r, tex);
    // }

    // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    rm.display();
}

void MyGame::onEvent(SDL_Event &event)
{
    switch(event.type)
    {
    case SDL_QUIT:
        running = false;
        break;

    case SDL_WINDOWEVENT:
        if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
        {
            rm.updateRenderSize();
            // cam.updateSize(window);
            // gl
        }
        break;
    }
}

void MyGame::onInput()
{
    camVel = {0, 0};
    scale = {0, 0};

    // std::cout << p->getComponent<Transform>()->angle << std::endl;

    if(keys[SDL_SCANCODE_K])
        cam.target(p);

    if(keys[SDL_SCANCODE_J])
        cam.target(nullptr);

    if(keys[SDL_SCANCODE_UP])
        camVel.y = 3;
    else if(keys[SDL_SCANCODE_DOWN])
        camVel.y = -3;

    if(keys[SDL_SCANCODE_LEFT])
        camVel.x = -3;
    else if(keys[SDL_SCANCODE_RIGHT])
        camVel.x = 3;

    if(keys[SDL_SCANCODE_RIGHTBRACKET])
        scale = {0.01, 0.01};

    else if(keys[SDL_SCANCODE_LEFTBRACKET])
        scale = {-0.01, -0.01};


    if(keys[SDL_SCANCODE_P])
        scaleX += 0.01;
    else if(keys[SDL_SCANCODE_O])
        scaleX -= 0.01;


    if(keys[SDL_SCANCODE_L])
        scaleY += 0.01;
    else if(keys[SDL_SCANCODE_K])
        scaleY -= 0.01;

    if(keys[SDL_SCANCODE_D])
        cam.angle += 0.1;
    else if(keys[SDL_SCANCODE_A])
        cam.angle -= 0.1;

    if(keys[SDL_SCANCODE_C])
        angChg = 0.05;
    else if(keys[SDL_SCANCODE_Z])
        angChg = -0.05;
    else
        angChg = 0;

    if(keys[SDL_SCANCODE_B])
    {
        cam.angle = 0;
        // rm.useLayers = !rm.useLayers;

        // // rm.updateScreenSize();
        // if(rm.useLayers)
        //     rm.setLayerPadding(0,{100,100});
        // else
        //     rm.setLayerPadding(0,{0,0});
        // rm.setLayerOffsetting(0,rm.useLayers);
        SDL_Delay(300);
    }
}
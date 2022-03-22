#ifndef __ENGINE__
#define __ENGINE__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
// #include <SDL2/SDL2_gfxPrimitives.h>
// #include <SDL2/SDL_mixer.h>
// #include <SDL2/SDL_ttf.h>
#include "RenderingManager.hpp"
#include "ComponentManager.hpp"
#include "EntityManager.hpp"
#include "Camera.hpp"
#include <string>  
#include <iostream>

class Engine
{
protected:
    bool running;
    Uint16 maxLPS;
    Uint8 delay;
    SDL_Window* window;
    SDL_Renderer* renderer;
    std::string title;
    RenderingManager rm;
    ComponentManager cm;
    EntityManager em;
    Camera cam;
    const Uint8* keys = SDL_GetKeyboardState(NULL);  // initial here since it is const

public:
    Engine(const char* title, int xPos, int yPos, int width, int height);
    ~Engine();

    virtual void onStart() = 0;
    virtual void onUpdate() = 0;
    virtual void onDraw() = 0;
    virtual void onEvent(SDL_Event& event) = 0;
    virtual void onInput() = 0;  // better to spilt it from onEvent since its can get quite big, also it uses keys instead of event

    void start();
    void setFullscreen(bool value);
    void setTitle(const char* title);
    void setResize(bool value);
    void setMaxLPS(Uint16 lps);
    void setVsync(bool value);  // need to use with conf file
};

#endif
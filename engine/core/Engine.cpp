#include "Engine.hpp"
#include "glm/gtx/orthonormalize.hpp"


Engine::Engine(const char* title, int xPos, int yPos, int width, int height)
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << "Failed to init SDL2" << std::endl;
        std::cout << SDL_GetError() << std::endl;
        exit(1);
    }

    if(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) == 0)
    {
        std::cout << "Failed to init SDL_image" << std::endl;
        std::cout << IMG_GetError() << std::endl;
        exit(1);
    }

    // if(Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) == 0)
    // {
    //     std::cout << "Failed to init SDL_mixer" << std::endl;
    //     std::cout << Mix_GetError() << std::endl;
    //     exit(1);
    // }

    // set hints and settings;
    // SDL_SetHint(SDL_HINT_RENDER_OPENGL_SHADERS, "0");
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    
    window = SDL_CreateWindow(title, xPos, yPos, width, height, SDL_WINDOW_OPENGL);

    rm.init(window);
    cam = Camera({0, 0}, {width, height});  // since camera pos min is 0,0 so center is width/2 and height/2
    em.init(&cm);
    this->title = std::string(title);
}

Engine::~Engine()
{
    rm.clean();
    SDL_DestroyWindow(window);
    // IMG_Quit();
    // Mix_Quit();
    SDL_Quit();
    std::cout << "Exited successfully" << std::endl;
}

void Engine::start() 
{
    SDL_Event event;
    Uint64 nowTime = 0;
    Uint64 lastTime = SDL_GetTicks();
    float targetDT = 1 / 60.0;  // we want delta of 1/60 aka 60 fps
    float currentDT = 0;
    float unprocessedTime = 0;
    float metricCounter = 0;
    Uint16 frames = 0;
    Uint16 loops = 0;
    Uint16 updates = 0;
    Uint8 maxSkipFrames = 30;
    Uint8 skipFrames = 0;
    bool render = false;
    running = true;
    maxLPS = 230;  // using 
    delay = 5;

    onStart();
    
    while(running)
    {
        // std::cout << SDL_GetError() << std::endl;

        while(SDL_PollEvent(&event)) 
        {
            onEvent(event);
        }

        onInput();
        
        nowTime = SDL_GetTicks();
        currentDT = (nowTime - lastTime)/1000.0;
        lastTime = nowTime;

        unprocessedTime += currentDT;  // using it to update when needed aka when it comes to 1/60 or above
        metricCounter += currentDT;  // using for counting frames
        loops++;
        
        skipFrames = 0;
        render = false;

        if(metricCounter >= 1.0)  // since 60 FPS is 1/60, 60 frames will be 1.0
        {
            setTitle((title+" FPS: "+std::to_string(frames)+" UPS: "+std::to_string(updates)+" LPS: "+std::to_string(loops)+" Delay: "+std::to_string(delay)).c_str());
            
            if((loops-maxLPS) >= 5)
            {
                if(delay < 255)
                    delay++;
            }
            else if((loops-maxLPS) <= -5)
            {
                if(delay > 0)
                    delay--;
            }

            metricCounter = 0;
            loops = 0;
            frames = 0;
            updates = 0;       
        }

        // doing this to catch up with updates, if currentDT is very small that
        while(unprocessedTime >= targetDT && skipFrames < maxSkipFrames)
        {
            onUpdate();
            unprocessedTime -= targetDT;
            skipFrames++;
            render = true;
            updates++;
        }

        // if update happend redraw, else wait
        if(render)
        {
            onDraw();
            frames++;
        }
        else
            SDL_Delay(delay);
    }
}

void Engine::setFullscreen(bool value)
{
    if(value)
        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
    else
        SDL_SetWindowFullscreen(window, 0);
}

void Engine::setTitle(const char* title) 
{
    SDL_SetWindowTitle(window, title);
}

void Engine::setResize(bool value)
{
    SDL_SetWindowResizable(window, (SDL_bool)value);
}

// set max lps (updates are only 60 frames, lps is the number of loops per second, its used to not hog the cpu)
void Engine::setMaxLPS(Uint16 lps)
{
    maxLPS = lps;
}

void Engine::setVsync(bool value)
{

}

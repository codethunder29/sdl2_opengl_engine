#include "Game.hpp"

int main()
{
    MyGame* game = new MyGame("test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600);
    // game->setFullscreen(true);
    game->setResize(true);
    game->start();

    delete game;
    return 0;
}
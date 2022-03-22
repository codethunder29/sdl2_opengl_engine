// #include "Enemy.hpp"

// Enemy::Enemy()
// {
//     angle = 0;
//     steps = 0;
//     vel = {0,0};
// }

// Enemy::Enemy(SDL_Renderer* renderer, Vec2<float> pos, Vec2<int> size) : GameObject(pos, size)
// {
//     angle = 0;
//     steps = 0;
//     vel = {3,3};
//     objSprite = new Sprite();
//     objSprite->loadTexture(renderer, "/home/user/Pictures/slime.png");
// }

// Enemy::~Enemy() {}

// void Enemy::update()
// {
//     if(steps == 0)
//     {
//         if(rand()%11 == 5)
//         {
//             steps = rand()%50+30;
//             angle = rand()%7;
//         }
//     }
//     else
//     {
//         steps--;
//         pos.x += cos(angle)*vel.x;
//         pos.y += sin(angle)*vel.y;
//     }

//     objSprite->pos = pos;
//     objSprite->size = size;
// }
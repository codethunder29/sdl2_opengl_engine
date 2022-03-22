// #include "Ball.hpp"

// Ball::Ball(SDL_Renderer* renderer, Vec2<float> pos, Vec2<int> size) : GameObject(pos, size)
// {
//     objSprite = new Sprite();
//     objSprite->loadTexture(renderer, "/home/user/Pictures/tank.png");
//     objSprite->size = size;
//     angle = 0;
//     speed = 0;
//     TTL = 0;
//     moving = false;
// }

// void Ball::update()
// {
//     if(moving && TTL > 0)
//     {
//         pos.x += cosf(angle) * speed;
//         pos.y += sinf(angle) * speed;

//         TTL--;
//         objSprite->pos = pos;
//     }
// }

// void Ball::setAngle(float angle)
// {
//     this->angle = angle;
// }

// void Ball::setSpeed(float speed)
// {
//     this->speed = speed;
// }

// void Ball::setTTL(Uint16 TTL)
// {
//     this->TTL = TTL;
// }

// void Ball::move()
// {
//     moving = true;
// }

// bool Ball::dead()
// {
//     return (TTL <= 0);
// }
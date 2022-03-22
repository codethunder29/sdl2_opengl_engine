// #include "Player.hpp"

// Player::Player(SDL_Renderer* renderer, Vec2<float> pos, Vec2<int> size) : GameObject(pos, size)
// {
//     vel = {0,0};
//     angle = 0;

//     objSprite = new Sprite();
//     objSprite2 = new Sprite();

//     objSprite->loadTexture(renderer, "/home/user/Pictures/tank.png");
//     objSprite2->loadTexture(renderer, "/home/user/Pictures/tank2.png");

//     objSprite2->size = {25, 50};
//     objSprite2->setRotationOffset({0,-25 - size.y/2 + 5});
// }

// Player::~Player()
// {
//     delete objSprite2;
// }

// void Player::update()
// {
//     pos.x += vel.x;
//     pos.y += vel.y;
//     angle += vel.x;

//     objSprite->pos = pos;
//     objSprite->size = size;

//     objSprite2->pos = {pos.x + size.x/2 - 25/2, pos.y + size.y - 5};
//     objSprite2->angle = angle;
// }

// Sprite* Player::getSprite2()
// {
//     return objSprite2;
// }
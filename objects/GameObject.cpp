// #include "GameObject.hpp"

// GameObject::GameObject(Vec2<float> pos, Vec2<int> size)
// {
//     this->pos = pos;
//     this->size = size;
//     vel = {0,0};
//     objSprite = nullptr;
// }

// GameObject::~GameObject()
// {
//     if(objSprite != nullptr)
//         delete objSprite;
// }

// Sprite* GameObject::getSprite()
// {
//     return objSprite;
// }

// void GameObject::update() {}

// SDL_Rect GameObject::getBounds()
// {
//     return {(int)pos.x, (int)pos.y, size.x, size.y};
// }

// Vec2<float> GameObject::getCenteredPos()
// {
//     return {pos.x+size.x/2,pos.y+size.y/2};
// }


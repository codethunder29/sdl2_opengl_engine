#ifndef __TRANSFORM_COMPONENT__
#define __TRANSFORM_COMPONENT__

#include "Component.hpp"

class Transform : public Component
{
public:
    Vec2<float> scale;
    Vec2<float> rotationOffset;
    float angle;
    SDL_RendererFlip flip;

    Transform(Vec2<float> scale={1,1}, Vec2<float> rotationOffset={0,0}, float angle=0, SDL_RendererFlip flip=SDL_FLIP_NONE)
    {
        id = TRANS_COMP;
        this->scale = scale;
        this->rotationOffset = rotationOffset;
        this->angle = angle;
        this->flip = flip;
    }

    static Uint8 getId()
    {
        return TRANS_COMP;
    }
};

#endif
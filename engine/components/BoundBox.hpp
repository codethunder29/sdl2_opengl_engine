#ifndef __BOUND_BOX__
#define __BOUND_BOX__

#include "Component.hpp"

class BoundBox : public Component
{
private:

public:
    Vec2<float> pos;
    Vec2<Uint16> size;

    BoundBox(Vec2<float> pos, Vec2<Uint16> size)
    {
        id = BOUND_BOX_COMP;
        this->pos = pos;
        this->size = size;
    }

    Vec2<float> getCenteredPos()
    {
        return {pos.x+size.x/2,pos.y+size.y/2};
    }

    SDL_Rect getBounds()
    {
        return {pos.x,pos.y,size.x,size.y};
    }

    static Uint8 getId()
    {
        return BOUND_BOX_COMP;
    }
};

#endif
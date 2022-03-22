#include "Component.hpp"

class Position : public Component
{
public:
    Vec2<float> pos;

    Position(Vec2<float> pos)
    {
        id = POS_COMP;
        this->pos = pos;
    }

    // doing this in function and variable because one is needed for pointers/instances and other is without instance
    static Uint8 getId()
    {
        return POS_COMP;
    }
};
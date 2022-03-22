#ifndef __COMPONENT__
#define __COMPONENT__

#include <SDL2/SDL.h>
#include "DataTypes.hpp"

enum ComponentTypes
{
    POS_COMP,  // position component
    TEX_COMP,  // texture component
    BOUND_BOX_COMP,  // position + size component
    TRANS_COMP,  // transformation component
    SOUND_COMP  // sound component
};

enum ComponentSigns
{
    POS_COMP_SIGN = 0x00000001,
    TEX_COMP_SIGN = 0x00000002,
    BOUND_BOX_COMP_SIGN = 0x00000004,
    TRANS_COMP_SIGN = 0x00000008,
    SOUND_COMP_SIGN = 0x00000016
};

class Component
{
public:
    Uint8 id;
};

#endif
#include "Component.hpp"

class SoundComp : public Component
{
public:
    SDL_BlendMode blend;

    SoundComp()
    {
        id = SOUND_COMP;
        
    }

    static Uint8 getId()
    {
        return SOUND_COMP;
    }
};
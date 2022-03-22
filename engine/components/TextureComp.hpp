#ifndef __TEXTURE_COMPONENT__
#define __TEXTURE_COMPONENT__

#include "Component.hpp"
#include <string>
#include <SDL2/SDL_image.h>

class TextureComp : public Component
{
public:
    SDL_Texture* texture;
    Vec2<Uint8> textureOffset;

    TextureComp(SDL_Renderer* renderer, std::string path, SDL_Color color={255,255,255,255}, SDL_BlendMode blend=SDL_BLENDMODE_BLEND)
    {
        id = TEX_COMP;
        textureOffset = {0,0};

        SDL_Surface* tmp = IMG_Load(path.c_str());
        SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer ,tmp);
        SDL_FreeSurface(tmp);

        SDL_SetTextureColorMod(tex, color.r, color.g, color.b);
        SDL_SetTextureAlphaMod(tex, color.a);
        SDL_SetTextureBlendMode(tex, blend);
        texture = tex;

    }

    ~TextureComp()
    {
        SDL_DestroyTexture(texture);
    }

    void setColor(SDL_Color color)
    {
        SDL_SetTextureColorMod(texture, color.r, color.g, color.b);
        SDL_SetTextureAlphaMod(texture, color.a);
    }

    void setBlending(SDL_BlendMode blend)
    {
        SDL_SetTextureBlendMode(texture, blend);
    }

    static Uint8 getId()
    {
        return TEX_COMP;
    }  
};

#endif
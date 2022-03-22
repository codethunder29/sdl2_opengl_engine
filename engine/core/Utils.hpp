#ifndef __UTILS__
#define __UTILS__

#include <SDL2/SDL.h>
#include <string>
#include <algorithm>
#include "DataTypes.hpp"

namespace utils
{
    void normalizeVec(Vec2<float>& vec);
    float distance(Vec2<float>& p1, Vec2<float>& p2);
    float interpolation1D(float startVal, float endVal, float time);
    float radToDeg(float radians);
    bool pointInRect(Vec2<float> p, SDL_Rect& r);
    bool rectInRect(SDL_Rect& r1, SDL_Rect& r2);  // checking if r1 is in r2
    bool isColliding(SDL_Rect& r1, SDL_Rect& r2);
    // bool isColliding(SDL_Rect& r, Circle& c);
    // bool isColliding(SDL_Rect& r, Line& l);
    // bool isColliding(SDL_Rect& r, Ray& ry);
    // Vec2<float> isColliding(SDL_Rect& r, Circle& c);
}

#endif
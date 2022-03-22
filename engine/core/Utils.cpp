#include "Utils.hpp"

void utils::normalizeVec(Vec2<float>& vec)
{
    float tmpX = cosf(atan2f(vec.y, vec.x));
    vec.y = sinf(atan2f(vec.y, vec.x));
    vec.x = tmpX;
}

float utils::distance(Vec2<float>& p1, Vec2<float>& p2)
{
    return std::sqrt(std::pow(p1.x - p2.x,2) + std::pow(p1.y - p2.y,2));
}

float utils::interpolation1D(float startVal, float endVal, float time)
{
    return (endVal - startVal) * time + startVal;
}

float utils::radToDeg(float radians)
{
    return radians*(180/M_PI);
}

bool utils::pointInRect(Vec2<float> p, SDL_Rect& r)
{
    if(r.x <= p.x && p.x <= r.x+r.h)
    {
        return (r.y <= p.y && p.y <= r.y+r.h);
    }

    return false;
}

// checking if r1 is in or intersecting with r2
bool utils::rectInRect(SDL_Rect& r1, SDL_Rect& r2)
{
    if(r2.x <= r1.x+r1.w && r1.x <= r2.x+r2.w)
    {
        return (r2.y <= r1.y+r1.h && r1.y <= r2.y+r2.h);
    }

    return false;
}

bool utils::isColliding(SDL_Rect& r1, SDL_Rect& r2)
{
    if(abs((r1.x+r1.w/2) - (r2.x+r2.w/2))*2 < (r1.w+r2.w))
        return abs((r1.y+r1.h/2) - (r2.y+r2.h/2))*2 < (r1.h+r2.h);

    return false;
}

// bool utils::isColliding(SDL_Rect& r, Circle& c)
// {
//     Vec2<float> nearPoint;
//     Vec2<float> cirCenter = {c.pos.x, c.pos.y};
//     nearPoint.x = std::clamp((int)c.pos.x, r.x, r.x+r.w);
//     nearPoint.y = std::clamp((int)c.pos.y, r.y, r.y+r.h);

//     return distance(nearPoint, cirCenter) <= c.radius;
// }

// // fast line rect function (used in raycasting python engine)
// bool utils::isColliding(SDL_Rect& r, Line& l)
// {
//     if(r.x <= l.p1.x && l.p1.x <= r.x+r.w && r.y <= l.p1.y && l.p1.y <= r.y+r.h)
//         return true;

//     if(r.x <= l.p2.x && l.p2.x <= r.x+r.w && r.y <= l.p2.y && l.p2.y <= r.y+r.h)
//         return true;

//     if(l.p1.x < r.x && l.p2.x < r.x)
//         return false;

//     if(l.p1.x > r.x+r.w && l.p2.x > r.x+r.w)
//         return false;
    
//     if(l.p1.y < r.y && l.p2.y < r.y)
//         return false;

//     if(l.p1.y > r.y+r.h && l.p2.y > r.y+r.h)
//         return false;

//     if(l.p1.x == l.p2.x)
//     {
//         if(r.x > l.p1.x || l.p1.x > r.x+r.w)
//             return false;

//         float minY = std::min(l.p1.y, l.p2.y);
//         float maxY = std::max(l.p1.y, l.p2.y);

//         return (minY <= r.y && maxY >= r.y+r.h);
//     }
//     else
//     {
//         float slope = (l.p1.y - l.p2.y)/(l.p1.x - l.p2.x);
//         float intercept = l.p1.y - slope*l.p1.x;

//         if(slope == 0)
//         {
//             if(r.y > l.p1.y || l.p1.y > r.y+r.h)
//                 return false;

//             float minX = std::min(l.p1.x, l.p2.x);
//             float maxX = std::max(l.p1.x, l.p2.x);

//             return (minX <= r.x && maxX >= r.x+r.w);
//         }
//         else
//         {   
//             float y = slope*r.x+intercept;
//             if(r.y <= y && y <= r.y+r.h)
//                 return true;

//             y = slope*(r.x+r.w)+intercept;
//             if(r.y <= y && y <= r.y+r.h)
//                 return true;

//             float x = (r.y - intercept)/slope;
//             if(r.x <= x && x <= r.x+r.w)
//                 return true;

//             // last one just returns without if because its the last one
//             x = (r.y + r.h - intercept)/slope;
//             return (r.x <= x && x <= r.x+r.w);
//         }
//     }
// }

// // need to test this one
// bool utils::isColliding(SDL_Rect& r, Ray& ry)
// {
//     if(ry.angle == M_PI/2 || ry.angle == 1.5*M_PI)
//     {
//         float ryX = ry.magnitude*cosf(ry.angle);
//         float ryY = ry.magnitude*sinf(ry.angle);

//         if(r.x > ryX || ryX > r.x+r.w)
//             return false;

//         float minY = std::min(ryY, ry.pos.y);
//         float maxY = std::max(ryY, ry.pos.y);

//         return (minY <= r.y && maxY >= r.y+r.h);
//     }
//     else
//     {
//         float slope = tanf(ry.angle);  // since tan is y/x it is equal to slope
//         float intercept = ry.pos.y - slope*ry.pos.x;

//         if(slope == 0)
//         {
//             float ryX = ry.magnitude*cosf(ry.angle);
//             float ryY = ry.magnitude*sinf(ry.angle);

//             if(r.y > ryY || ryY > r.y+r.h)
//                 return false;

//             float minX = std::min(ryX, ry.pos.x);
//             float maxX = std::max(ryX, ry.pos.x);
            
//             return (minX <= r.x && maxX >= r.x+r.w);
//         }
//         else
//         {
//             float y = slope*r.x+intercept;
//             if(r.y <= y && y <= r.y+r.h)
//                 return true;

//             y = slope*(r.x+r.w)+intercept;
//             if(r.y <= y && y <= r.y+r.h)
//                 return true;

//             float x = (r.y - intercept)/slope;
//             if(r.x <= x && x <= r.x+r.w)
//                 return true;

//             // last one just returns without if because its the last one
//             x = (r.y + r.h - intercept)/slope;
//             return (r.x <= x && x <= r.x+r.w);
//         }
//     }
// }
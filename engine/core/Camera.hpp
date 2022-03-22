#ifndef __CAMERA__
#define __CAMERA__

#include <SDL2/SDL.h>
#include "DataTypes.hpp"
#include "Utils.hpp"
#include "Entity.hpp"
#include "BoundBox.hpp"
#include <deque>
#include <algorithm>


enum cameraModes
{
    NONE,
    NORMAL_MODE,  // just follows entities
    GRID_MODE  // moving the camera when going outside of camera bounds
};

class Camera
{
private:
    Entity* targetObj;
    std::deque<Vec2<float>> positions;
    float cameraAccel;
    float cameraVel;
    float ogCameraVel;
    Uint8 maxCameraVel;
    Uint8 cameraMode;
    bool onTarget;
    bool locked;
    float ogDistToTarget;
    float distToTarget;
    Vec2<float> startCameraPos;
    float slowingDistance;
    float maxSlowingDistance;

    void moveStep(Vec2<float> pos, Vec2<float> startPos);

public:
    Vec2<float> pos;
    Vec2<int> size;
    Vec2<float> scale;
    Vec2<Uint16> padding;  // used to extend drawing outside of camera bounds (good for rotated objects because they disappear near bounds)
    float angle;

    Camera(Vec2<float> pos=Vec2<float>(0,0), Vec2<int> size=Vec2<int>(0,0));
    ~Camera();

    void update();
    void move(Vec2<float> newPos);
    // void zoom(Vec2<float> newScale);
    void target(Entity* obj);
    void setCameraMode(Uint8 mode);
    void setLock(bool val);
    void updateSize(SDL_Window* window);
    void setBorderPadding(Vec2<Uint16> padding);
    SDL_Rect getBounds();
};

#endif
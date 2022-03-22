#include "Camera.hpp"

Camera::Camera(Vec2<float> pos, Vec2<int> size)
{
    this->pos = pos;
    this->size = size;
    scale = {1,1};
    targetObj = nullptr;
    cameraAccel = 0.3;
    cameraVel = 10;
    ogCameraVel = cameraVel;
    maxCameraVel = 30;
    distToTarget = 0;
    cameraMode = NONE;
    onTarget = false;
    locked = false;
    maxSlowingDistance = (pow(cameraVel, 2) - pow(maxCameraVel, 2))/(2 * -cameraAccel);  // using kinematic formulas to determine distance that camera need to pass to go from max vel to og vel
    slowingDistance = 0;
    startCameraPos = Vec2<float>(0,0);
    padding = {0,0};
    angle = 0;
}

Camera::~Camera() {}

void Camera::update()
{
    if(positions.size() > 0)
    {
        Vec2<float> v = positions[0];
        positions.pop_front();

        if(!locked)
        {
            pos.x += v.x;
            pos.y += v.y;
        }
    }

    if(cameraMode == NORMAL_MODE)
    {
        if(targetObj != nullptr)
        {
            Vec2<float> targetPos = targetObj->getComponent<BoundBox>()->getCenteredPos();
            float currDistance = 0;
            distToTarget = 0;

            if(onTarget)
            {
                pos.x = targetPos.x;
                pos.y = targetPos.y;
            }
            else
            {
                currDistance = utils::distance(targetPos, pos);
                distToTarget = utils::distance(targetPos, startCameraPos);

                if(abs(distToTarget - ogDistToTarget) >= 10)
                {
                    ogDistToTarget = distToTarget;
                    slowingDistance = std::clamp(distToTarget/2, 0.0f, maxSlowingDistance);
                }

                if(currDistance > cameraVel)
                {
                    moveStep(targetPos, pos);

                    if(currDistance < slowingDistance)
                    {
                        if(cameraVel - cameraAccel > ogCameraVel)
                            cameraVel -= cameraAccel;
                    }
                    else
                    {
                        if(cameraVel + cameraAccel < maxCameraVel)
                            cameraVel += cameraAccel;
                    }  
                }
                else
                {
                    onTarget = true;
                    cameraVel = ogCameraVel;
                }
            }
        }
    }
    else if(cameraMode == GRID_MODE)
    {
        if(targetObj != nullptr && positions.size() == 0)
        {
            if(targetObj->getComponent<BoundBox>()->getCenteredPos().x > pos.x + size.x/2)
                move({pos.x+size.x,pos.y});
            
            if(targetObj->getComponent<BoundBox>()->getCenteredPos().x < pos.x - size.x/2)
                move({pos.x-size.x,pos.y});

            if(targetObj->getComponent<BoundBox>()->getCenteredPos().y > pos.y + size.y/2)
                move({pos.x,pos.y+size.y});
            
            if(targetObj->getComponent<BoundBox>()->getCenteredPos().y < pos.y - size.y/2)
                move({pos.x,pos.y-size.y});
        }
    }
}

void Camera::moveStep(Vec2<float> pos, Vec2<float> startPos)
{
    Vec2<float> tmp;
    float dist = utils::distance(pos, startPos);
    tmp.x = (pos.x - startPos.x)/dist * cameraVel;
    tmp.y = (pos.y - startPos.y)/dist * cameraVel;

    tmp.x = std::clamp(tmp.x, (float)-maxCameraVel, (float)maxCameraVel);
    tmp.y = std::clamp(tmp.y, (float)-maxCameraVel, (float)maxCameraVel);
    
    positions.push_back(tmp);
}

void Camera::move(Vec2<float> newPos)
{
    Vec2<float> tmp = pos;
    Vec2<float> step = {0,0};
    float dist = utils::distance(tmp, newPos);
    slowingDistance = std::clamp(dist/2, 0.0f, maxSlowingDistance);
    float angle = atan2(newPos.y - pos.y, newPos.x - pos.x);
    cameraVel = ogCameraVel;

    while(dist > cameraVel)
    {
        step.x = cosf(angle) * cameraVel;
        step.y = sinf(angle) * cameraVel;
        tmp.x += step.x;
        tmp.y += step.y;

        if(dist < slowingDistance)
        {
            if(cameraVel - cameraAccel > ogCameraVel)
                cameraVel -= cameraAccel;
        }
        else
        {
            if(cameraVel + cameraAccel < maxCameraVel)
                cameraVel += cameraAccel;
        }  

        positions.push_back(step);
        dist = utils::distance(tmp, newPos);
    }

    positions.push_back(newPos - tmp);   
}

void Camera::target(Entity* obj)
{
    onTarget = false;  // unlock when changing targets
    cameraVel = ogCameraVel;

    if(obj != nullptr && obj->checkComponents(BOUND_BOX_COMP_SIGN))
    {
        ogDistToTarget = utils::distance(obj->getComponent<BoundBox>()->pos, pos);
        slowingDistance = std::clamp(ogDistToTarget/2, 0.0f, maxSlowingDistance);
        startCameraPos = pos;
        targetObj = obj;
    }
    else
    {
        targetObj = nullptr;
    }
}

// need to update vars based on the change
void Camera::setCameraMode(Uint8 mode)
{
    cameraMode = mode;
}

void Camera::setLock(bool val)
{
    locked = val;
}

void Camera::updateSize(SDL_Window* window)
{
    // SDL_GetWindowSize(window, &size.x, &size.y);
    // pos.x = size.x/2;
    // pos.y = size.y/2;
}

void Camera::setBorderPadding(Vec2<Uint16> padding)
{
    this->padding = padding;
}

SDL_Rect Camera::getBounds()
{
    return {(int)(pos.x - size.x/2),(int)(pos.y - size.y/2),size.x,size.y};
}
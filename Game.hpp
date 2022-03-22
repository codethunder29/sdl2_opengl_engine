#include "Engine.hpp"
#include "Position.hpp"
#include "TextureComp.hpp"
#include "Transform.hpp"
#include "BoundBox.hpp"


class MyGame : public Engine
{
private:
    Entity* p;
    Entity* slime;
    Vec2<float> camVel;
    Vec2<float> scale;
    float mAngle;
    float angChg;
    float scaleX, scaleY;
    std::vector<Vec2<float>> tiles;
    

    Texture tex;
    Texture tex2;
    Texture tex3;
    Texture tex4;
    Texture tex5;

public:
    MyGame(const char* title, int xPos, int yPos, int width, int height);
    ~MyGame();

    void onStart();
    void onUpdate(); 
    void onDraw();
    void onEvent(SDL_Event& event);
    void onInput();
};
#include "raylib.h"

class Character
{
public:
    Character(float faceDir, float speed, int maxFrames,float winBoundaryX, float winBoundaryY ,float updateTime = 1.f/12.f, float runningTime = 0.f, int frame = 0);
    Vector2 GetWorldPos() { return worldPos; }
    void SetTexturePath(char *path)
    {
        texture = LoadTexture(path);
    }
    void SetIdlePath(char *path)
    {
        idle = LoadTexture(path);
    }
    void SetRunPath(char *path)
    {
        run = LoadTexture(path);
    }
    void SetScreenPos(int winWidth, int winHieght);
    void SetWorldPos(float width, float height);
    void Tick(float deltaTime);
    void Movement();
    void Animation(float deltaTime);
    void Drawing();
    void UnloadTextures();
private:
    Texture2D texture;
    Texture2D idle;
    Texture2D run;
    Vector2 screenPos;
    Vector2 worldPos;
    Vector2 velocity;
    float faceDir = -1.0f;
    int frame = 0;
    float updateTime = 1.f / 12.f;
    float runningTime = 0;
    float speed = 5.0;
    int maxFrames;
    float winBoundaryX;
    float winBoundaryY;
};
#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H
#include "raylib.h"
#include "raymath.h"

class BaseCharacter
{
public:
    BaseCharacter();
    Vector2 GetWorldPos() { return worldPos; }
    virtual Vector2 GetScreenPos() = 0;
    Vector2 GetPlayerVelocity() { return Vector2Scale(Vector2Normalize(velocity), speed); }
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
    // void Tick(float deltaTime);
    void Movement();
    void Animation(float deltaTime);
    void Drawing();
    void UnloadTextures();
    Rectangle getCollisionRec();
    void UnDoMovement();
    bool notMoving = false;
    virtual void Tick(float deltaTime);
    bool getAlive(){return alive;};
    void setAlive(bool isAlive){ alive = isAlive;};

protected:
    Texture2D texture;
    Texture2D idle;
    Texture2D run;
    Vector2 screenPos;
    Vector2 worldPos;
    Vector2 velocity;

    Vector2 worldPosLastFrame;

    float faceDir = -1.0f;
    int frame = 0;
    float updateTime = 1.f / 12.f;
    float runningTime = 0;
    float speed = 5.0;
    int maxFrames;
    float winBoundaryX;
    float winBoundaryY;
    float scale;
    float width;
    float height;

private:
    bool alive = true;
};

#endif
#include "Character.h"
#include "raymath.h"

Character::Character(float faceDir, float speed, int maxFrames, float winBoundaryX, float winBoundaryY, float updateTime, float runningTime, int frame)
{
    this->faceDir = faceDir;
    this->speed = speed;
    this->maxFrames = maxFrames;
    this->updateTime = updateTime;
    this->runningTime = runningTime;
    this->frame = frame;
    this->winBoundaryX = winBoundaryX;
    this->winBoundaryY = winBoundaryY;
}

void Character::UnloadTextures()
{
    UnloadTexture(texture);
    UnloadTexture(idle);
    UnloadTexture(run);
}

void Character::SetScreenPos(int winWidth, int winHeight)
{
    screenPos = {
        winWidth / 2.0f - 4.0f * (0.5f * (float)texture.width / 6.0f),
        winHeight / 2.0f - 4.0f * (0.5f * (float)texture.height)};
}

void Character::SetWorldPos(float width, float height)
{
    worldPos = {
        width, height};
}

void Character::Tick(float deltaTime)
{
    Movement();
    Animation(deltaTime);
    Drawing();
}

void Character::Drawing()
{
    Rectangle knightSource{
        frame * (float)(texture.width) / 6.0f,
        0,
        faceDir * (float)(texture.width) / 6.0f,
        (float)texture.height};
    Rectangle knightDest{
        screenPos.x,
        screenPos.y,
        4.0f * (float)(texture.width) / 6.0f,
        4.0f * (float)texture.height};
    DrawTexturePro(texture, knightSource, knightDest, Vector2{}, 0, WHITE);
}

void Character::Animation(float deltaTime)
{
    runningTime += deltaTime;
    if (runningTime > updateTime)
    {
        frame++;
        runningTime = 0;
        if (frame > maxFrames)
        {
            frame = 0;
        }
    }
}

void Character::Movement()
{
    velocity = {};
    if (IsKeyDown(KEY_A))
        velocity.x = 1.0;
    if (IsKeyDown(KEY_D))
        velocity.x -= 1.0;
    if (IsKeyDown(KEY_W))
        velocity.y += 1.0;
    if (IsKeyDown(KEY_S))
        velocity.y -= 1.0;
    if (Vector2LengthSqr(velocity) != 0.0)
    {
        // worldPos = worldPos + direction

        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity), speed));
        if(worldPos.x > 0) worldPos.x = 0;
        if(worldPos.y > 0) worldPos.y = 0;
        if(worldPos.x < -winBoundaryX) worldPos.x = -winBoundaryX ;
        if(worldPos.y < -winBoundaryY) worldPos.y = -winBoundaryY ;

        // if((worldPos.x < 0 || worldPos.y < 0) || (worldPos.x > winBoundaryX || worldPos.y > winBoundaryY))
        velocity.x < 0.f ? faceDir = 1.f : faceDir = -1.f;
        texture = run;
    }
    else
    {
        texture = idle;
    }
}

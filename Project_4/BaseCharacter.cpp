#include "BaseCharacter.h"

BaseCharacter::BaseCharacter(){

}
void BaseCharacter::UnloadTextures()
{
    UnloadTexture(texture);
    UnloadTexture(idle);
    UnloadTexture(run);
}

void BaseCharacter::SetScreenPos(int winWidth, int winHeight)
{
    screenPos = {
        winWidth / 2.0f - scale * (0.5f * static_cast<float>(texture.width) / maxFrames),
        winHeight / 2.0f - scale * (0.5f * static_cast<float>(texture.height))};
}

void BaseCharacter::SetWorldPos(float width, float height)
{
    worldPos = {
        width, height};
}

void BaseCharacter::Drawing()
{
    Rectangle Source{
        frame * static_cast<float>(texture.width) / maxFrames,
        0,
        faceDir * static_cast<float>(texture.width) / maxFrames,
        (float)texture.height};
    Rectangle Dest{
        screenPos.x,
        screenPos.y,
        scale * (float)(texture.width) / maxFrames,
        scale *  (float)texture.height};
    DrawTexturePro(texture, Source, Dest, Vector2{}, 0, WHITE);
}

void BaseCharacter::Animation(float deltaTime)
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

void BaseCharacter::Movement()
{

    if (Vector2LengthSqr(velocity) != 0.0)
    {
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity), speed));
        if(worldPos.x > 0) worldPos.x = 0;
        if(worldPos.y > 0) worldPos.y = 0;
        if(worldPos.x < -winBoundaryX) worldPos.x = -winBoundaryX ;
        if(worldPos.y < -winBoundaryY) worldPos.y = -winBoundaryY ;
        velocity.x < 0.f ? faceDir = 1.f : faceDir = -1.f;
        texture = run;
    }
    else
    {
        texture = idle;
    }
    // velocity = {};
}

Rectangle BaseCharacter::getCollisionRec(){
    return Rectangle{
        screenPos.x,
        screenPos.y,
        texture.width/6 * scale,
        texture.height * scale
    };
}


void  BaseCharacter::UnDoMovement(){
    worldPos = worldPosLastFrame;
}


void BaseCharacter::Tick(float deltaTime)
{
    worldPosLastFrame = worldPos;
    // Movement();
    Animation(deltaTime);
    Drawing();
}
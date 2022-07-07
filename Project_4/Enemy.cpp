#include "Enemy.h"
#include "raymath.h"

Enemy::Enemy(Vector2 pos, Texture2D idle, Texture2D run)
{
    worldPos = pos;
    screenPos = Vector2{0, 0};
    texture = idle;
    this->idle = idle;
    this->run = run;
    scale = 4;
    updateTime = 1.f / 12.f;
    runningTime = 0;
    frame = 0;
    maxFrames = 6;
    speed = 3.1f;
    faceDir = 1.0f;
    width = texture.width / maxFrames;
    height = texture.height;
}

void Enemy::Tick(float deltaTime)
{
    if (!getAlive())
        return;
    MoveToTarget();
    if (CheckCollisionRecs(this->getCollisionRec() , target->getCollisionRec()))
    {
        this->UnDoMovement();
        texture = idle;
        attackStamp += deltaTime;
        if (attackStamp > attackRate)
        {
            attackStamp = 0;
            target->takeDamage(damagePerSec);
        }
    }
    else
    {
        texture = run;
    }
    screenPos = Vector2Add(worldPos, target->GetWorldPos());
    BaseCharacter::Tick(deltaTime);
}

void Enemy::MoveToTarget()
{
    Vector2 toTarget = Vector2Subtract(target->GetScreenPos(), screenPos);
    if (toTarget.x > 0)
    {
        faceDir = 1.0f;
    }
    else
        faceDir = -1.0f;
    toTarget = Vector2Normalize(toTarget);
    toTarget = Vector2Scale(toTarget, speed);
    // velocity = toTarget;
    worldPos = Vector2Add(worldPos, toTarget);
}

Vector2 Enemy::GetScreenPos()
{
    return Vector2{screenPos};
}

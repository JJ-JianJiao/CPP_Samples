#include "Character.h"
#include "raymath.h"

Character::Character(Vector2 worldPos, Texture2D idle, Texture2D run, float boundaryX, float boundaryY)
{
    worldPos = worldPos;
    this->winBoundaryX = boundaryX;
    this->winBoundaryY = boundaryY;
    texture = idle;
    this->idle = idle;
    this->run = run;
    scale = 4;
    updateTime = 1.f / 12.f;
    runningTime = 0;
    frame = 0;
    maxFrames = 6;
    speed = 5.f;
    faceDir = 1.0f;
    width = texture.width / maxFrames;
    height = texture.height;
}

void Character::Tick(float deltaTime)
{
    if (!getAlive())
        return;
    BaseCharacter::Tick(deltaTime);
    velocity = {};
    if (IsKeyDown(KEY_A))
        velocity.x = 1.0;
    if (IsKeyDown(KEY_D))
        velocity.x -= 1.0;
    if (IsKeyDown(KEY_W))
        velocity.y += 1.0;
    if (IsKeyDown(KEY_S))
        velocity.y -= 1.0;
    Movement();

    // draw sword
    Vector2 origin = {};
    Vector2 offset{};
    if (faceDir > 0.f)
    {
        origin = {0.f, weapon.height * scale};
        offset = {35.f, 55.f};
        weaponCollisionRec = {
            GetScreenPos().x + offset.x,
            GetScreenPos().y + offset.y - weapon.height * scale,
            weapon.width * scale,
            weapon.height * scale};
        IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? rotation = 35.f : rotation = 0.f;
    }
    else
    {
        origin = {weapon.width * scale, weapon.height * scale};
        offset = {25.f, 55.f};
        weaponCollisionRec = {
            GetScreenPos().x + offset.x - weapon.width * scale,
            GetScreenPos().y + offset.y - weapon.height * scale,
            weapon.width * scale,
            weapon.height * scale};
        IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? rotation = -35.f : rotation = 0.f;
    }

    Rectangle source{0.f, 0.f, static_cast<float>(weapon.width) * faceDir, static_cast<float>(weapon.height)};
    Rectangle dest{GetScreenPos().x + offset.x, GetScreenPos().y + offset.y, weapon.width * scale, weapon.height * scale};

    DrawTexturePro(weapon, source, dest, origin, rotation, WHITE);
    weaponCollisionRec = {GetScreenPos().x + weapon.width * scale / 2 * faceDir, GetScreenPos().y, weapon.width * scale, weapon.height * scale};
    DrawRectangleLines(weaponCollisionRec.x, weaponCollisionRec.y, weaponCollisionRec.width, weaponCollisionRec.height, RED);
}

Vector2 Character::GetScreenPos()
{
    return Vector2{screenPos};
}

void Character::takeDamage(float damage)
{
    health -= damage;
    if (health <= 0)
    {
        health = 0;
        setAlive(false);
    }
}
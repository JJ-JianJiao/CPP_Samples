#ifndef CHARACTER_H
#define CHARACTER_H

#include "raylib.h"
#include "raymath.h"
#include "BaseCharacter.h"

class Character:public BaseCharacter
{
public:
    Character(Vector2 worldPos, Texture2D idle, Texture2D run, float boundaryX, float boundaryY);
    virtual void Tick(float deltaTime) override;
    virtual Vector2 GetScreenPos() override;
    Rectangle getWeaponCollisionRec(){
        return weaponCollisionRec;
    }
    float getHealth() const {return health;}
    void takeDamage(float damage);
private:
    Texture2D weapon{LoadTexture("characters/weapon_sword.png")};
    Rectangle weaponCollisionRec{};
    float rotation = 35.f;
    float health{100.f};
};

#endif
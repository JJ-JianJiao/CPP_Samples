#include "raylib.h"
#include "BaseCharacter.h"
#include "Character.h"

class Enemy : public BaseCharacter
{
public:
    Enemy(Vector2 pos, Texture2D idle, Texture2D run);
    virtual void Tick(float deltaTime) override;
    void SetTarget(Character *chara)
    {
        target = chara;
    }
    virtual Vector2 GetScreenPos() override;

private:
    Character *target;
    void MoveToTarget();
    float damagePerSec{10.f};
    float attackRate =1.f;
    float attackStamp = 1.f;
};
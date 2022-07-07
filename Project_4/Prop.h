#include "raylib.h"

class Prop
{
public:
    Prop(float scale, Vector2 pos, Texture2D texture);
    void Render(Vector2 knightPos);
    void ReleaseTexture();
    Rectangle getCollisionRec(Vector2 knightPos);

private:
    Texture2D texture{};
    Vector2 worldPos{};
    float scale{};
};
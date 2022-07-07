#include "Prop.h"
#include "raymath.h"

Prop::Prop(float scale , Vector2 pos, Texture2D texture):
    scale(scale), 
    worldPos(pos), 
    texture(texture)
{

}


void Prop::Render(Vector2 pos){
    Vector2 screenPos = Vector2Add(worldPos,pos);
    DrawTextureEx(texture,screenPos,0.f,scale,WHITE);
}

void Prop::ReleaseTexture(){
    UnloadTexture(texture);
}

Rectangle Prop::getCollisionRec(Vector2 knightPos)
{
    Vector2 screenPos = Vector2Add(worldPos,knightPos);
    return Rectangle{
        screenPos.x,
        screenPos.y,
        texture.width * scale,
        texture.height  * scale
    };
}

#include "raylib.h"
#include "raymath.h"
#include <string>
#include "Character.h"

int main()
{
    int windowDimensions[] = {384, 384};
    const char *title = "ClassyClash";
    InitWindow(windowDimensions[0], windowDimensions[1], title);

    SetTargetFPS(60);
    // Map texture
    const char *mapPath = "nature_tileset/WorldMap.png";
    Texture2D worldMapTexture = LoadTexture(mapPath);
    const float mapScale{4};

    // knight
    char *knightIdlePath = "characters/knight_idle_spritesheet.png";
    char *knightRunPath = "characters/knight_run_spritesheet.png";

    Character knight(1.f,5.f,6,worldMapTexture.width * mapScale - windowDimensions[0], worldMapTexture.height * mapScale - windowDimensions[1] ,1.f/12.f, GetFrameTime(),0);
    knight.SetTexturePath(knightIdlePath);
    knight.SetIdlePath(knightIdlePath);
    knight.SetRunPath(knightRunPath);
    knight.SetScreenPos(windowDimensions[0], windowDimensions[1]);
    knight.SetWorldPos(-(float)worldMapTexture.width / 2, -(float)worldMapTexture.height / 2);

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(WHITE);
        DrawTextureEx(worldMapTexture,  knight.GetWorldPos(), 0.0, mapScale, WHITE);
        knight.Tick(GetFrameTime());
        EndDrawing();
    }
    UnloadTexture(worldMapTexture);
    knight.UnloadTextures();
    CloseWindow();
}
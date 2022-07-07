#include "raylib.h"
#include "raymath.h"
#include <string>
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"
#include <string>

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

    // Character knight(1.f, 5.f, 6, worldMapTexture.width * mapScale - windowDimensions[0], worldMapTexture.height * mapScale - windowDimensions[1], mapScale, 1.f / 12.f, GetFrameTime(), 0);
    Character knight(Vector2{-(float)worldMapTexture.width / 2, -(float)worldMapTexture.height / 2}, LoadTexture(knightIdlePath), LoadTexture(knightRunPath), worldMapTexture.width * mapScale - windowDimensions[0], worldMapTexture.height * mapScale - windowDimensions[1]);
    knight.SetScreenPos(windowDimensions[0], windowDimensions[1]);
    knight.SetWorldPos(-(float)worldMapTexture.width / 2, -(float)worldMapTexture.height / 2);

    // Prop
    Texture2D rockTexture = LoadTexture("nature_tileset/Rock.png");
    Texture2D logTexture = LoadTexture("nature_tileset/Log.png");

    Prop props[2]{
        Prop{mapScale, Vector2{-knight.GetWorldPos().x, -knight.GetWorldPos().y}, rockTexture},
        Prop{mapScale, Vector2{-knight.GetWorldPos().x * 2, -knight.GetWorldPos().y * 2}, logTexture},
    };

    // enemy
    char *goblinIdlePath = "characters/goblin_idle_spritesheet.png";
    char *goblinRunPath = "characters/goblin_run_spritesheet.png";
    char *slimeIdlePath = "characters/slime_idle_spritesheet.png";
    char *slimeRunPath = "characters/slime_run_spritesheet.png";
    Enemy goblin{Vector2{(float)worldMapTexture.width / 3, (float)worldMapTexture.height / 3}, LoadTexture(goblinIdlePath), LoadTexture(goblinRunPath)};
    Enemy goblin2{Vector2{(float)worldMapTexture.width / 2, (float)worldMapTexture.height / 2}, LoadTexture(goblinIdlePath), LoadTexture(goblinRunPath)};
    Enemy goblin3{Vector2{(float)worldMapTexture.width / 3, (float)worldMapTexture.height / 1.5}, LoadTexture(slimeIdlePath), LoadTexture(slimeRunPath)};
    Enemy goblin4{Vector2{(float)worldMapTexture.width / 1.2, (float)worldMapTexture.height / 2}, LoadTexture(slimeIdlePath), LoadTexture(slimeRunPath)};

    Enemy *enemies[] = {
        &goblin,
        &goblin2,
        &goblin3,
        &goblin4,
    };

    int enemiesNUm = 4;

    for (auto enemy : enemies)
    {
        enemy->SetTarget(&knight);
    }

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(WHITE);
        DrawTextureEx(worldMapTexture, knight.GetWorldPos(), 0.0, mapScale, WHITE);

        // for (size_t i = 0; i < 2; i++)
        // {
        //     props[i].Render(knight.GetWorldPos());
        // }
        for (auto prop : props)
        {
            if (CheckCollisionRecs(prop.getCollisionRec(knight.GetWorldPos()), knight.getCollisionRec()))
            {
                knight.UnDoMovement();
            }
        }
        for (auto prop : props)
        {
            prop.Render(knight.GetWorldPos());
        }

        if (enemiesNUm == 0)
        {
            DrawText("You win", 55.f, 45.f, 40, RED);
            knight.Tick(GetFrameTime());

            EndDrawing();
            continue;
        }

        if (!knight.getAlive())
        {
            DrawText("Game Over", 55.f, 45.f, 40, RED);
            EndDrawing();
            continue;
        }
        else
        {
            std::string knightHealth = "Health: ";
            knightHealth.append(std::to_string(knight.getHealth()), 0, 5);
            DrawText(knightHealth.c_str(), 55.f, 45.f, 40, RED);
        }

        // goblin.Tick(GetFrameTime());
        for (auto enemy : enemies)
        {
            enemy->Tick(GetFrameTime());
        }
        knight.Tick(GetFrameTime());
        // rock.Render(knight.GetWorldPos());

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {

            for (auto enemy : enemies)
            {
                if (enemy->getAlive())
                {
                    if (CheckCollisionRecs(enemy->getCollisionRec(), knight.getWeaponCollisionRec()))
                    {
                        enemy->setAlive(false);
                        enemiesNUm--;
                    }
                }
            }
        }

        EndDrawing();
    }
    UnloadTexture(worldMapTexture);
    knight.UnloadTextures();
    goblin.UnloadTextures();
    for (auto prop : props)
    {
        prop.ReleaseTexture();
    }
    CloseWindow();
}
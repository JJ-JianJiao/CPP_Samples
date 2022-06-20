#include "raylib.h"

int main(){

    int width = 350;
    int height = 200;
    const char* title = "My first Raylib game";
    InitWindow(width,height, title);
    while (true)
    {
        BeginDrawing();

        ClearBackground(RED);
        EndDrawing();
    }
    
}
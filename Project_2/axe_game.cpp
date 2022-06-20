#include "raylib.h"





int main(){

    int winWidth = 800;
    int winHeight = 600;
    const char* title = "My first Raylib game";
    InitWindow(winWidth,winHeight, title);

    int cirPositionX = winWidth/2;
    int cirPositionY = winHeight/2;
    float radius = 50;
    Color cirColor = RED;
    int cirOffsetX = radius * 4;
    int cirOffsetY = radius * 4;
    int cirSpeed = 5;


    int recPositionX = cirPositionX;
    int recPositionY = 0;
    int height = radius * 2;
    int width = radius * 2;
    Color recColor = BLUE;
    int recSpeed = 3;

    bool collision_with_axe = false;
    SetTargetFPS(120);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        
        if(collision_with_axe){
            DrawText("Game Over!",winWidth/2, winHeight/2, 20, RED);
        }
        else{

            int cir_t_y = cirPositionY - radius;
            int cir_b_y = cirPositionY + radius;
            int cir_l_x = cirPositionX - cirOffsetX - radius;
            int cir_r_x = cirPositionX - cirOffsetX + radius;


            int rec_t_y = recPositionY;
            int rec_b_y = recPositionY + height;
            int rec_l_x = recPositionX;
            int rec_r_x = recPositionX + width;
            //game logic begins
            int tempCirPosX = cirPositionX - cirOffsetX;
            int tempCirPosY = cirPositionY;
            if(cirPositionX - cirOffsetX - radius < 0){
                tempCirPosX = radius;
            }
            else if(cirPositionX - cirOffsetX + radius > winWidth){
                tempCirPosX = winWidth - radius;
            }
            if(cirPositionY + radius > winHeight){
                tempCirPosY = winHeight - radius;
            }
            else if(cirPositionY - radius < 0){
                tempCirPosY = radius;
            }

            DrawCircle(tempCirPosX, tempCirPosY, radius, cirColor);
            DrawRectangle(recPositionX,recPositionY,width,height,recColor);
            
            if(IsKeyDown(KEY_D) && cirPositionX - cirOffsetX  + radius <= winWidth)
            {
                cirPositionX +=cirSpeed;
            }
            if(IsKeyDown(KEY_A) && cirPositionX - cirOffsetX - radius >=0)
            {
                cirPositionX -=cirSpeed;
            }

            if(IsKeyDown(KEY_S) && cirPositionY  + radius <= winHeight)
            {
                cirPositionY +=cirSpeed;
            }
            if(IsKeyDown(KEY_W) && cirPositionY - radius >=0)
            {
                cirPositionY -=cirSpeed;
            }

            recPositionY += recSpeed;
            if(recPositionY + height > winHeight || recPositionY < 0){
                recSpeed *= -1;
            }

            if(rec_b_y >= cir_t_y && rec_t_y <= cir_b_y && rec_l_x <= cir_r_x && rec_r_x >= cir_l_x){
                collision_with_axe = true;
            }
            //game logic ends
        }

        EndDrawing();
    }

} 

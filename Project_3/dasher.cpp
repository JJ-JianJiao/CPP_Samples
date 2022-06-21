#include "raylib.h"


struct AnimData{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

int main(){

    const int winWidth = 512;
    const int winHeight = 380;
    const int fpsValue = 60;
    const char* title = "My second game";
    InitWindow(winWidth,winHeight,title);
    const int recWidth = 50;
    const int recHeight = 80;

    const int gravity{80};

    int recPosY = winHeight- recHeight;

    int velocity = 0;
    int jumpForce = -1600;

    bool isGround = false;
    int jumpTimes = 0;

    //nebula variables
    const char* nebulaPath = "textures/12_nebula_spritesheet.png";
    Texture2D nebulaTexture = LoadTexture(nebulaPath);
    AnimData nebulaAnim;
    nebulaAnim.rec.height = nebulaTexture.height/8.0f;
    nebulaAnim.rec.width = nebulaTexture.width/8.0f;
    nebulaAnim.rec.x = 0;
    nebulaAnim.rec.y = 0;
    nebulaAnim.pos.x = winWidth;
    nebulaAnim.pos.y = winHeight - nebulaAnim.rec.height;
    nebulaAnim.frame = 0;
    nebulaAnim.updateTime  = 1.0/30.0;
    nebulaAnim.runningTime  = 0;

    AnimData nebulaAnim2;
    nebulaAnim2.rec.height = nebulaTexture.height/8.0f;
    nebulaAnim2.rec.width = nebulaTexture.width/8.0f;
    nebulaAnim2.rec.x = 0;
    nebulaAnim2.rec.y = 0;
    nebulaAnim2.pos.x = winWidth + 300;
    nebulaAnim2.pos.y = winHeight - nebulaAnim2.rec.height;
    nebulaAnim2.frame = 0;
    nebulaAnim2.updateTime  = 1.0/30.0;
    nebulaAnim2.runningTime  = 0;

    float nebulaVolocity = -350;
    float resetNebula = 2;
    float duringTimeNebula = 0;
    float resetNebula2 = 3;
    float duringTimeNebula2 = 0;

    //Scarfy variables
    const char* scarfyPath = "textures/scarfy.png";
    Texture2D scarfy = LoadTexture(scarfyPath);

    AnimData scarfyData;
    scarfyData.rec.height = scarfy.height;
    scarfyData.rec.width = scarfy.width/6;
    scarfyData.rec.x = 0;
    scarfyData.rec.y = 0;
    // Vector2 scarfyPos;
    scarfyData.pos.x = winWidth/2 - scarfyData.rec.width * 1;
    scarfyData.pos.y = winHeight - scarfyData.rec.height;
    scarfyData.frame = 0;
    scarfyData.updateTime = 1.0/12.0;
    scarfyData.runningTime = 0;

    //bancground
    const char* farBuildingsPath = "textures/far-buildings.png";
    const char* backBuildingsPath = "textures/back-buildings.png";
    const char* foregroundPath = "textures/foreground.png";

    Texture2D farBuldingTex = LoadTexture(farBuildingsPath);
    Texture2D backBuildingsTex = LoadTexture(backBuildingsPath);
    Texture2D foregroundTex = LoadTexture(foregroundPath);
    Rectangle farBuildRec = {0,0,winWidth,winHeight};
    Vector2 buildingPositon= {0.0,0.0};


    bool isCollision = false;
    int jumpOverNum = 0;
    bool isWin = false;
    SetTargetFPS(fpsValue);

    while(!WindowShouldClose()){

        BeginDrawing();

        ClearBackground(WHITE);
        DrawTextureRec(farBuldingTex,farBuildRec,buildingPositon, WHITE);

        if(!isCollision && !isWin){
            // scarfyRec.x += scarfyRec.width;
            if(isGround){
                scarfyData.runningTime += GetFrameTime();
                scarfyData.rec.x = scarfyData.frame * scarfyData.rec.width;
                if(scarfyData.runningTime > scarfyData.updateTime){
                    scarfyData.frame++;
                    scarfyData.runningTime = 0;
                }
                if(scarfyData.frame > 6){
                    scarfyData.frame = 0;
                }
            }

            nebulaAnim.runningTime += GetFrameTime();
            nebulaAnim2.runningTime += GetFrameTime();
            nebulaAnim.rec.x = nebulaAnim.frame * nebulaAnim.rec.width;
            nebulaAnim2.rec.x = nebulaAnim2.frame * nebulaAnim2.rec.width;
            if(nebulaAnim.runningTime > nebulaAnim.updateTime){
                nebulaAnim.frame++;
                nebulaAnim.runningTime = 0;
                nebulaAnim2.frame++;
                nebulaAnim2.runningTime = 0;
            }
            if(nebulaAnim.frame > 8){
                nebulaAnim.frame = 0;
                nebulaAnim2.frame = 0;
            }

            if( IsKeyPressed(KEY_SPACE) && (isGround || jumpTimes < 2) ){
            // if(IsKeyDown(KEY_SPACE)){
                jumpTimes++;
                // velocity += jumpForce;
                velocity = 0;

                velocity += jumpForce* GetFrameTime();
                isGround = false;
            }

            velocity += gravity * GetFrameTime();

            // recPosY += velocity; 
            scarfyData.pos.y += velocity; 


            if(scarfyData.pos.y > winHeight - scarfyData.rec.height){
                scarfyData.pos.y = winHeight-scarfyData.rec.height;
                velocity = 0;
                isGround = true;
                jumpTimes = 0;
            }
            nebulaAnim.pos.x += nebulaVolocity * GetFrameTime();
            nebulaAnim2.pos.x += nebulaVolocity * GetFrameTime();
            duringTimeNebula += GetFrameTime();
            duringTimeNebula2 += GetFrameTime();
            if(duringTimeNebula > resetNebula )
            {
                duringTimeNebula = 0;
                nebulaAnim.pos.x = winWidth;
                // nebulaAnim2.pos.x = winWidth + GetRandomValue(200,300);
                jumpOverNum++;

            }  
            if(duringTimeNebula2 > resetNebula2 )
            {
                duringTimeNebula2 = 0;
                nebulaAnim2.pos.x = winWidth + 300;
                jumpOverNum++;

            }  

            if(jumpOverNum > 20){
                    isWin = true;
            }
            // DrawRectangle(winWidth/2, recPosY, recWidth, recHeight, BLUE);

            DrawTextureRec(nebulaTexture,nebulaAnim.rec,nebulaAnim.pos,WHITE);
            DrawTextureRec(nebulaTexture,nebulaAnim2.rec,nebulaAnim2.pos,RED);
            
            DrawTextureRec(scarfy,scarfyData.rec,scarfyData.pos, WHITE);
        }
        else if(isCollision){
            DrawText("Game Over", winWidth/2, winHeight/2,22,RED);
        }
        else if(isWin){
            DrawText("You Win", winWidth/2, winHeight/2,22,RED);
        }
        EndDrawing();
    }
    UnloadTexture(nebulaTexture);
    UnloadTexture(scarfy);
    CloseWindow();
}

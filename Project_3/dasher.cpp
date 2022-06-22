#include "raylib.h"


struct AnimData{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

bool IsOnGround(AnimData data, int windowHeight){
    return data.pos.y >= windowHeight - data.rec.height;
}

void UpdateAnimationData(AnimData* data, float deltaTime, int frameNum){
    data->runningTime += deltaTime;
    data->rec.x = data->frame * data->rec.width;
    if(data->runningTime > data->updateTime){
        data->frame++;
        data->runningTime = 0;
    }
    if(data->frame > frameNum){
        data->frame = 0;
    }
}

void UpdateBackGround(Vector2* position, int speed, int winWidth,Texture2D bgTexture){
    position->x -= speed * GetFrameTime();
    Vector2 currentPositon = {position->x, position->y};
    Vector2 secondBg = {position->x + winWidth, 0.0};
    DrawTextureEx(bgTexture,currentPositon, 0.0, 2.0,WHITE);
    DrawTextureEx(bgTexture,secondBg, 0.0, 2.0,WHITE);
    if(position->x + winWidth <=0){
        position->x = 0;
    }
}

int main(){
    int windowDimensions[] = {512,380};
    // const int winWidth = 512;
    // const int winHeight = 380;
    const int fpsValue = 60;
    const char* title = "My second game";
    InitWindow(windowDimensions[0],windowDimensions[1],title);
    const int recWidth = 50;
    const int recHeight = 80;

    const int gravity{80};

    int recPosY = windowDimensions[1]- recHeight;

    int velocity = 0;
    int jumpForce = -1600;

    bool isGround = false;
    int jumpTimes = 0;

    //nebula variables
    const char* nebulaPath = "textures/12_nebula_spritesheet.png";
    Texture2D nebulaTexture = LoadTexture(nebulaPath);
    // AnimData nebulaAnim;
    // nebulaAnim.rec.height = nebulaTexture.height/8.0f;
    // nebulaAnim.rec.width = nebulaTexture.width/8.0f;
    // nebulaAnim.rec.x = 0;
    // nebulaAnim.rec.y = 0;
    // nebulaAnim.pos.x = windowDimensions[0];
    // nebulaAnim.pos.y = windowDimensions[1] - nebulaAnim.rec.height;
    // nebulaAnim.frame = 0;
    // nebulaAnim.updateTime  = 1.0/30.0;
    // nebulaAnim.runningTime  = 0;

    // AnimData nebulaAnim2;
    // nebulaAnim2.rec.height = nebulaTexture.height/8.0f;
    // nebulaAnim2.rec.width = nebulaTexture.width/8.0f;
    // nebulaAnim2.rec.x = 0;
    // nebulaAnim2.rec.y = 0;
    // nebulaAnim2.pos.x = windowDimensions[0] + 300;
    // nebulaAnim2.pos.y = windowDimensions[1] - nebulaAnim2.rec.height;
    // nebulaAnim2.frame = 0;
    // nebulaAnim2.updateTime  = 1.0/30.0;
    // nebulaAnim2.runningTime  = 0;

    // AnimData nebulaAnim2{
    //     {0,0,nebulaTexture.width/8.0f,nebulaTexture.height/8.0f},
    //     {nebulaAnim.pos.x = windowDimensions[0],nebulaAnim2.pos.y = windowDimensions[1] - nebulaAnim2.rec.height},
    //     0,
    //     1.0/30.0,
    //     0
    // };
    const int sizeofNebula = 2;
    AnimData nebulaAnims[sizeofNebula]{};

    for (int i = 0; i < sizeofNebula; i++)
    {
        nebulaAnims[i].rec.height = nebulaTexture.height/8.0f;
        nebulaAnims[i].rec.width = nebulaTexture.width/8.0f;
        nebulaAnims[i].rec.x = 0;
        nebulaAnims[i].rec.y = 0;
        nebulaAnims[i].pos.x = windowDimensions[0] + i * 350;
        nebulaAnims[i].pos.y = windowDimensions[1] - nebulaAnims[i].rec.height;
        nebulaAnims[i].frame = 0;
        nebulaAnims[i].updateTime  = 1.0/30.0;
        nebulaAnims[i].runningTime  = 0;
    }
    // nebulaAnims[1].pos.x = windowDimensions[0] + 300;

    float nebulaVolocity = -350;
    float resetNebula = 2;
    float duringTimeNebula = 0;
    float resetNebula2 = 4;
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
    scarfyData.pos.x = windowDimensions[0]/2 - scarfyData.rec.width * 1;
    scarfyData.pos.y = windowDimensions[1] - scarfyData.rec.height;
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
    // Rectangle farBuildRec = {0,0,windowDimensions[0],windowDimensions[1]};
    Vector2 buildingPositon= {0.0,0.0};
    Vector2 foregroundPositon= {0.0,0.0};
    Vector2 farBuildPositon= {0.0,0.0};


    bool isCollision = false;
    int jumpOverNum = 0;
    bool isWin = false;
    float isWinDuringTime = 3;
    float isWinTimeStamp = 0;
    SetTargetFPS(fpsValue);

    

    while(!WindowShouldClose()){

        BeginDrawing();

        ClearBackground(WHITE);

        // buildingPositon.x -= 20 * GetFrameTime();
        // Vector2 secondBg = {buildingPositon.x + windowDimensions[0], 0.0};
        // DrawTextureEx(farBuldingTex,buildingPositon, 0.0, 2.0,WHITE);
        // DrawTextureEx(farBuldingTex,secondBg, 0.0, 2.0,WHITE);
        // if(buildingPositon.x + windowDimensions[0] <=0){
        //     buildingPositon.x = 0;
        // }

        UpdateBackGround(&buildingPositon,20,windowDimensions[0],farBuldingTex);
        UpdateBackGround(&foregroundPositon,40,windowDimensions[0],backBuildingsTex);
        UpdateBackGround(&farBuildPositon,60,windowDimensions[0],foregroundTex);
        // DrawTextureEx(backBuildingsTex,buildingPositon, 0.0, 2.0,WHITE);
        // DrawTextureEx(foregroundTex,buildingPositon, 0.0, 2.0,WHITE);

        if(!isCollision && isWinTimeStamp < isWinDuringTime){
            // scarfyRec.x += scarfyRec.width;
            if(isGround){

                UpdateAnimationData(&scarfyData, GetFrameTime(), 6);
                // scarfyData.runningTime += GetFrameTime();
                // scarfyData.rec.x = scarfyData.frame * scarfyData.rec.width;
                // if(scarfyData.runningTime > scarfyData.updateTime){
                //     scarfyData.frame++;
                //     scarfyData.runningTime = 0;
                // }
                // if(scarfyData.frame > 6){
                //     scarfyData.frame = 0;
                // }
            }

            // nebulaAnims[0].runningTime += GetFrameTime();
            // nebulaAnims[1].runningTime += GetFrameTime();
            // nebulaAnims[0].rec.x = nebulaAnims[0].frame * nebulaAnims[0].rec.width;
            // nebulaAnims[1].rec.x = nebulaAnims[1].frame * nebulaAnims[1].rec.width;
            // if(nebulaAnims[0].runningTime > nebulaAnims[0].updateTime){
            //     nebulaAnims[0].frame++;
            //     nebulaAnims[0].runningTime = 0;
            //     nebulaAnims[1].frame++;
            //     nebulaAnims[1].runningTime = 0;
            // }
            // if(nebulaAnims[0].frame > 8){
            //     nebulaAnims[0].frame = 0;
            //     nebulaAnims[1].frame = 0;
            // }

            for (int i = 0; i < sizeofNebula; i++)
            {
                // nebulaAnims[i].runningTime += GetFrameTime();
                // nebulaAnims[i].rec.x = nebulaAnims[i].frame * nebulaAnims[i].rec.width;
                // if(nebulaAnims[i].runningTime > nebulaAnims[i].updateTime){
                //     nebulaAnims[i].frame++;
                //     nebulaAnims[i].runningTime = 0;
                // }
                // if(nebulaAnims[i].frame > 8){
                //     nebulaAnims[i].frame = 0;
                // }
                UpdateAnimationData(&nebulaAnims[i], GetFrameTime(), 8);
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


            // if(scarfyData.pos.y > windowDimensions[1] - scarfyData.rec.height){
            if(IsOnGround(scarfyData, windowDimensions[1])){
                scarfyData.pos.y = windowDimensions[1]-scarfyData.rec.height;
                velocity = 0;
                isGround = true;
                jumpTimes = 0;
            }
            nebulaAnims[0].pos.x += nebulaVolocity * GetFrameTime();
            nebulaAnims[1].pos.x += nebulaVolocity * GetFrameTime();
            duringTimeNebula += GetFrameTime();
            duringTimeNebula2 += GetFrameTime();
            if(duringTimeNebula > resetNebula && !isWin && !isCollision)
            {
                duringTimeNebula = 0;
                nebulaAnims[0].pos.x = windowDimensions[0];
                // nebulaAnim2.pos.x = winWidth + GetRandomValue(200,300);
                jumpOverNum++;

            }  
            if(duringTimeNebula2 > resetNebula2 && !isWin&& !isCollision)
            {
                duringTimeNebula2 = 0;
                nebulaAnims[1].pos.x = windowDimensions[0] + 300;
                jumpOverNum++;

            }  

            if(jumpOverNum > 5){
                isWinTimeStamp += GetFrameTime();
                isWin = true;
            }

            for(AnimData data:nebulaAnims){
                float pad = 50;
                Rectangle nebRec{
                    data.pos.x + 20,
                    data.pos.y + 20,
                    data.rec.width - 2* pad,
                    data.rec.height - 2* pad
                };

                Rectangle scarftRec{
                    scarfyData.pos.x,
                    scarfyData.pos.y,
                    scarfyData.rec.width,
                    scarfyData.rec.height
                };

                if(CheckCollisionRecs(nebRec,scarftRec) && !isWin){
                    isCollision = true;
                }

            }
            // DrawRectangle(winWidth/2, recPosY, recWidth, recHeight, BLUE);

            if(!isWin){
                DrawTextureRec(nebulaTexture,nebulaAnims[0].rec,nebulaAnims[0].pos,WHITE);
                DrawTextureRec(nebulaTexture,nebulaAnims[1].rec,nebulaAnims[1].pos,RED);
            }
            DrawTextureRec(scarfy,scarfyData.rec,scarfyData.pos, WHITE);
        }
        else if(isCollision){
            DrawText("Game Over", windowDimensions[0]/2, windowDimensions[1]/2,22,RED);
        }
        else if(isWin && isWinTimeStamp >= isWinDuringTime){
            DrawText("You Win", windowDimensions[0]/2, windowDimensions[1]/2,22,RED);
        }
        EndDrawing();
    }
    UnloadTexture(backBuildingsTex);
    UnloadTexture(foregroundTex);
    UnloadTexture(farBuldingTex);
    UnloadTexture(nebulaTexture);
    UnloadTexture(scarfy);
    CloseWindow();
}

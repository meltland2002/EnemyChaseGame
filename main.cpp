// Made using raylib [core] example - Keyboard input as a base

/*******************************************************************************************
*
*   raylib [core] example - Keyboard input
*
*   Example originally created with raylib 1.0, last time updated with raylib 1.0
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2014-2023 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include <iostream>
using namespace std;

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "simple chase game");

    Texture2D texture = LoadTexture("player.png");
    Texture2D enemy = LoadTexture("enemy.png");
    Vector2 playerPos = { (float)screenWidth/2, (float)screenHeight/2 };
    Vector2 enemyPos = { (float)screenWidth-80, (float)screenHeight-80 };
    Rectangle pArea = {(float)screenWidth/2, (float)screenHeight/2, 80, 80,};
    Rectangle hArea = {(float)screenWidth-80, (float)screenHeight-80, 80, 80,};
    bool GameOver = false;

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        if (!GameOver) {
            if (IsKeyDown(KEY_RIGHT)) playerPos.x += 4.0f;
            if (IsKeyDown(KEY_LEFT)) playerPos.x -= 4.0f;
            if (IsKeyDown(KEY_UP)) playerPos.y -= 4.0f;
            if (IsKeyDown(KEY_DOWN)) playerPos.y += 4.0f;
            // Move enemy
            if (enemyPos.x>playerPos.x) enemyPos.x -= 1;
            if (enemyPos.x<playerPos.x) enemyPos.x += 1;
            if (enemyPos.y>playerPos.y) enemyPos.y -= 1;
            if (enemyPos.y<playerPos.y) enemyPos.y += 1;
            // Check collision
            pArea = (Rectangle) {
                playerPos.x,
                playerPos.y,
                80,
                80,
            };
            hArea = (Rectangle) {
                enemyPos.x,
                enemyPos.y,
                80,
                80,
            };
            if (CheckCollisionRecs(pArea, hArea)) GameOver = true;
            // Move player
            if (playerPos.x<=0) playerPos.x = 1;
            if (playerPos.x>=720) playerPos.x = 719;
            if (playerPos.y<=0) playerPos.y = 1;
            if (playerPos.y>=370) playerPos.y = 369;
        } else {
            DrawRectangle(0, 100, screenWidth, 200, BLACK);
            DrawText("You died!", 40, 180, 30, WHITE);
        };
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText("Don't die!", 10, 10, 20, DARKGRAY);

            if(!GameOver) {
                DrawTexture(texture, playerPos.x, playerPos.y, WHITE);
                DrawTexture(enemy, enemyPos.x, enemyPos.y, WHITE);
            }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(texture);
    UnloadTexture(enemy);
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

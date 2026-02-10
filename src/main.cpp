#include <stdio.h>
#include <math.h>

#include "raylib.h"
#include "rlImGui.h"
#include "imgui/imgui.h"

//"ehh, good enough" - mediocrates

//basic 720, probably won't be changed in the future
int HEIGHT = 720;
int WIDTH = 1280;

//entities
 struct player{
     float x, y;
     float vx, vy; //velocity
     float width, height;
     Color color;
     float speed;
 };

 struct colider{
     float x, y;
     Color color;
     float width, height;
 };

int solveColision(player &p, colider &c) //0 means no col solved, 1 means top col solved, 2 right, 3 bottom, 4 left
{

     if(p.x < c.x + c.width && p.x + p.width > c.x && p.y < c.y + c.height && p.y + p.height > c.y)
     {
         float left = (p.x + p.width) - c.x;
         float right = (c.x + c.width) - p.x;
         float top = (p.y + p.height) - c.y;
         float bottom = (c.y + c.height) - p.y;

         float minOverlapX = fmin(left, right);
         float minOverlapY = fmin(top,bottom);
         if(minOverlapX < minOverlapY)
         {
            if(left < right)
            {
                 p.x -= left;
                 return 4;
            }
            else
            {
                 p.x += right;
                 return 2;
            }
         }
         else
         {
            if (top < bottom)
            {
                p.y -= top;

                return 1;
            }
            else
            {
                 p.y += bottom;
                 return 3;
            }
         }

     }
     return 0;
}

int main() {
    player player;
    player.x = 200;
    player.y = 200;
    player.width = 50;
    player.height = 50;
    player.color = {255, 0 , 0, 255};
    player.speed = 8;


    colider colider;
    colider.x = 400;
    colider.y = 200;
    colider.height = 200;
    colider.width = 80;
    colider.color = BLACK;

    InitWindow(WIDTH,HEIGHT,"work");
    SetTargetFPS(30); //as of the shitty new version, no delta time so fps changes game speed
    rlImGuiSetup(true);
    int result;
    while(WindowShouldClose() == false)
    {
        BeginDrawing();
        ClearBackground(WHITE); //any bg is better than onne
        if (IsKeyDown(KEY_LEFT))
        {
            player.vx -= player.speed;
        }
        if (IsKeyDown(KEY_RIGHT))
        {
            player.vx += player.speed;
        }
        if (IsKeyDown(KEY_UP))
        {
            player.vy -= player.speed;
        }
        if (IsKeyDown(KEY_DOWN))
        {
            player.vy += player.speed;
        }

        player.x += player.vx;
        player.y += player.vy;

        player.vx = 0;
        player.vy = 0;

        result = solveColision(player, colider);

        rlImGuiBegin();
        ImGui::Begin("cunt");
        ImGui::Text("x: %f", player.x);
        ImGui::Text("y: %f", player.y);
        ImGui::Text("speed: %f", player.vx);
        ImGui::Text("result: %d", result);
        ImGui::End();
        rlImGuiEnd();

        DrawRectangle(player.x,player.y,player.width,player.height, player.color);
        DrawRectangle(colider.x, colider.y, colider.width, colider.height, colider.color);
        EndDrawing();
    }

    printf("ay");
    return 0;
}

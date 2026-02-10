#include "raylib.h"
#include <locale>
#include <stdio.h>

int HEIGHT = 720;
int WIDTH = 1280;

 struct player{
     int x, y;
     Color color;
     int speed;
     bool canMove;
 };

 struct colider{
     int x, y;
     Color color;
     int width, height;
 };

int main() {
    player player;
    player.x = 200;
    player.y = 200;
    player.color = {255, 0 , 0, 255};
    player.speed = 8;
    player.canMove = true; //this definitly wont cause problems in the future

    colider colider;
    colider.x = 400;
    colider.y = 200;
    colider.height = 800;
    colider.width = 80;
    colider.color = BLACK;
    bool isColiding = false;
    int speedChangeX = 0;
    int speedChangeY = 0;
    InitWindow(WIDTH,HEIGHT,"work");
    SetTargetFPS(30); //as of the shitty new version, no delta time so fps changes game speed
    while(WindowShouldClose() == false)
    {
        BeginDrawing();
        ClearBackground(WHITE); //any bg is better than onne

        speedChangeX = 0;
        speedChangeY = 0;
        //draw player and coliderr
        DrawRectangle(player.x,player.y,50,50, player.color);
        DrawRectangle(colider.x, colider.y, colider.width, colider.height, colider.color);

        if(player.canMove)
        {
        //speed
        if (IsKeyDown(KEY_LEFT))
        {
            speedChangeX -= player.speed;
        }
        if (IsKeyDown(KEY_RIGHT))
        {
            speedChangeX += player.speed;
        }
        if (IsKeyDown(KEY_UP))
        {
            speedChangeY -= player.speed;
        }
        if (IsKeyDown(KEY_DOWN))
        {
            speedChangeY += player.speed;
        }
        }




        printf("x: %d y: %d\n", player.x, player.y);
        printf("isColding: %d\n", isColiding);
        player.x += speedChangeX;
        player.y += speedChangeY;
        isColiding = player.x < colider.x + colider.width && player.x + 50 > colider.x && player.y < colider.y + colider.height && player.y + 50 > colider.y;
        while(isColiding)
        {
            speedChangeX = -speedChangeX;
            speedChangeY = -speedChangeY;
            while(isColiding){
            player.x += speedChangeX ;
            player.y += speedChangeY;
            isColiding = player.x < colider.x + colider.width && player.x + 50 > colider.x && player.y < colider.y + colider.height && player.y + 50 > colider.y;
            }
            //"ehh, good enough" - mediocrates
        }
        EndDrawing();

    }

    printf("ay");
    return 0;
}

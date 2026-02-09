#include "raylib.h"
#include <stdio.h>


int HEIGHT = 720;
int WIDTH = 1280;

int main() {
    InitWindow(WIDTH,HEIGHT,"work");
    Color bgColor = { 255,0,0,255 };
    SetTargetFPS(500);
    int cState = 0;
    while(WindowShouldClose() == false)
    {
        BeginDrawing();
        ClearBackground(bgColor);

        switch (cState) {
            case 0:
            bgColor.g += 1; if (bgColor.g==255) {cState++;}
            break;
            case 1:
            bgColor.r -=1; if (bgColor.r==0) {cState++;}
            break;
            case 2:
            bgColor.b += 1; if (bgColor.b==255) {cState++;}
            break;
            case 3:
            bgColor.g -= 1; if (bgColor.g==0) {cState++;}
            break;
            case 4:
            bgColor.r += 1; if (bgColor.r==255) {cState++;}
            break;
            case 5:
            bgColor.b -=1; if (bgColor.b==0) {cState = 0;};
            break;
            default:
            cState = 0;
            break;
        }

        printf("red: %d \ngreen: %d \nblue: %d \nstate: %d\n", bgColor.r, bgColor.g, bgColor.b, cState);
        EndDrawing();
    }

    printf("ay");
    return 0;
}

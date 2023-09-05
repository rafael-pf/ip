#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "raylib.h"
#include "include/structs_def.c"
#include "include/saveTime.c"
#include "include/jogo.c"
#include "include/manual.c"

int main()
{
    botao start, sair, comecar;
    start.frame.height = 90;
    start.frame.width = 280;
    sair.frame.height = 90;
    sair.frame.width = 280;
    start.frame.x = 225;
    start.frame.y = 170;
    sair.frame.x = 225;
    sair.frame.y = 350;
    strcpy(start.string, "Start");
    strcpy(sair.string, "Sair");
    InitWindow(lar, alt, "Testando Menu");
    Image imagem = LoadImage("assets/imgs/fundo.png");
    ImageResizeNN(&imagem, lar, alt);
    Texture2D textura = LoadTextureFromImage(imagem);

    while (!WindowShouldClose())
    {
        Vector2 pos = GetMousePosition();
        BeginDrawing();
        DrawTexture(textura, 0, 0, WHITE);
        if (CheckCollisionPointRec(pos, start.frame))
        {
            DrawRectangleRec(start.frame, RED);
            DrawText(start.string, posX_Ret + 80, 170 + 25, 35, WHITE);
            if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
                Manual();
            }
        } else {
            DrawRectangleRec(start.frame, GRAY);
            DrawText(start.string, posX_Ret + 80, 170 + 25, 35, BLACK);
        }
        if (CheckCollisionPointRec(pos, sair.frame))
        {
            if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
                CloseWindow();
            }
            DrawRectangleRec(sair.frame, RED);
            DrawText(sair.string, posX_Ret + 80, 350 + 25, 35, WHITE);
        } else {
            DrawRectangleRec(sair.frame, GRAY);
            DrawText(sair.string, posX_Ret + 80, 350 + 25, 35, BLACK);
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}

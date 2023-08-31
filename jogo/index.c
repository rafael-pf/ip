#include <stdio.h>
#include "raylib.h"
#include "jogo.c"
#define posX_Ret 225
void Manual();
typedef struct 
{
    // Implementar essa struct para as coisas ficarem mais faceis
    Rectangle frame;
    char string[100];
} botao;

int main()
{
    int lar = 720, alt = 540;
    Rectangle start, sair, comecar;
    start.height = 90;
    start.width = 280;
    sair.height = 90;
    sair.width = 280;
    start.x = 225;
    start.y = 170;
    sair.x = 225;
    sair.y = 350;
    
    InitWindow(lar, alt, "Testando Menu");
    Image imagem = LoadImage("fundo.png");
    ImageResizeNN(&imagem, lar, alt);
    Texture2D textura = LoadTextureFromImage(imagem);
    while (!WindowShouldClose())
    {
        Vector2 pos = GetMousePosition();
        //printf("%f-%f\n", pos.x, pos.y);
        BeginDrawing();
        DrawTexture(textura, 0, 0, WHITE);
        if (CheckCollisionPointRec(pos, start))
        {
            DrawRectangleRec(start, RED);
            DrawText("Start", posX_Ret + 80, 170 + 25, 35, WHITE);
            if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
                Manual();
            }
        } else {
            DrawRectangleRec(start, GRAY);
            DrawText("Start", posX_Ret + 80, 170 + 25, 35, BLACK);
        }
        if (CheckCollisionPointRec(pos, sair))
        {
            if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
                CloseWindow();
            }
            DrawRectangleRec(sair, RED);
            DrawText("Sair", posX_Ret + 80, 350 + 25, 35, WHITE);
        } else {
            DrawRectangleRec(sair, GRAY);
            DrawText("Sair", posX_Ret + 80, 350 + 25, 35, BLACK);
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
void Manual(){
    Rectangle comecar;
    comecar.height = 90;
    comecar.width = 280;
    comecar.x = 225;
    comecar.y = 400;
    while (!WindowShouldClose())
    {
        Vector2 pos = GetMousePosition();
        //printf("%f-%f\n", pos.x, pos.y);
        BeginDrawing();
        ClearBackground(WHITE);
        DrawRectangle(80, 60, 570, 305, GRAY);
        // dois /n e um bom espacamento de linha
        DrawText(TextFormat("MANUAL:"), 80, 60, 20, BLACK);
        DrawText(TextFormat("Mover para a direita"), 270, 100, 20, BLACK);
        DrawText(TextFormat("Mover para a esquerda"), 270, 170, 20, BLACK);
        DrawText(TextFormat("Pular"), 270, 240, 20, BLACK);
        DrawText(TextFormat("Dash"), 270, 310, 20, BLACK);
        if (CheckCollisionPointRec(pos, comecar))
        {
            if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
                CloseWindow();
                Joguinho();
            }
            DrawRectangleRec(comecar, RED);
            DrawText("Começar", posX_Ret + 80, 400 + 25, 35, WHITE);
        } else {
            DrawRectangleRec(comecar, GRAY);
            DrawText("Começar", posX_Ret + 80, 400 + 25, 35, BLACK);
        }
        EndDrawing();
    }
    
}
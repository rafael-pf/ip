#include <stdio.h>
#include <math.h>
#include "raylib.h"
#include "raymath.h"
void Joguinho();
int main()
{
    Joguinho();
    return 0;
}
#define G 250
#define PJS 240.0f
#define PHS 110.0f
#define eni_qtd 30
typedef struct{
    Rectangle target;
    Texture2D textura;
    float velo;
}personagem;
typedef struct 
{
    Rectangle target;
    int velo;
}inimigo;

void Joguinho(){
    int lar = 720, alt = 540, jump_height = 60;
    InitWindow(lar, alt, "Run_Jump");
    personagem persona1;
    persona1.target.height = 97;
    persona1.target.width = 86;
    Image imagem = LoadImage("fundo2.png");
    ImageResizeNN(&imagem, lar, alt);
    Image personagem = LoadImage("personagem-menor.png");
    ImageResizeNN(&personagem, 86, 97);
    persona1.textura = LoadTextureFromImage(personagem);
    Texture2D textura = LoadTextureFromImage(imagem);

    persona1.target.x = lar / 2, persona1.target.y = 414;
    int space = 0;
    bool Jump = true, hit = true;
    char dir = 'D';
    //InitAudioDevice();
    //Sound som = LoadSound("zelda.mp3");
    //Sound jumpS = LoadSoundFromWave(LoadWave("sound.wav"));
    
    char Espa_Cont = 'C';
    // FPS tava influenciando na movimentacao, agora ta mais devagar
    SetTargetFPS(40);
    int w = 86, h = 97;
    int lifes = 100;
    bool dax = true;
    int pos_Pre = persona1.target.x;
        inimigo Pini[eni_qtd];
        /*Pini.velo = 2;
        Pini.target.height = 70;
        Pini.target.width = 40;
        Pini.target.x = (lar/ 3 * 2) + 400;
        Pini.target.y = 440;*/
        for (int i = 0; i < eni_qtd; i++)
        {
            Pini[i].velo = 3;
            Pini[i].target.height = GetRandomValue(50, 60);
            Pini[i].target.width = 35;
            // tem que dar algum jeito deles nao ficarem tao juntos
            Pini[i].target.x = (lar/ 3 * 2) + GetRandomValue(180, 2000);
            Pini[i].target.y = 509 - Pini[i].target.height;
        }
        
    while (!WindowShouldClose())
    {
        double time = GetTime();
        // master volume é uma bosta, muito paia
        //SetMasterVolume(100.0);
        //PlaySound(som);
        float delta = GetFrameTime();
        /*float y =  GetMouseY();
        printf("%.2f\n", y);*/
        //printf("%d\n", fps);
        if(Jump == 1 && space == 0){
            Jump = 0;
        }
        if (IsKeyDown(KEY_RIGHT) && dax == true)
        {
            persona1.target.x += 5;
            if (dir == 'E')
            {
                dir = 'D';
                ImageFlipHorizontal(&personagem);
                //ImageFlipHorizontal(&Espe_im);
                //espada = LoadTextureFromImage(Espe_im);
                persona1.textura = LoadTextureFromImage(personagem);
            }
            
        }
        if (IsKeyDown(KEY_LEFT) && dax == true)
        {
            persona1.target.x -= 5;
            if (dir == 'D')
            {
                dir = 'E';
                ImageFlipHorizontal(&personagem);
                //ImageFlipHorizontal(&Espe_im);
                //espada = LoadTextureFromImage(Espe_im);
                persona1.textura = LoadTextureFromImage(personagem);
            }
        }
        // Dash
        if (IsKeyPressed(KEY_D) && dax == true)
        {
            dax = false;
            pos_Pre = persona1.target.x;
        }
        if (!dax)
        {
            if (dir == 'D')
            {
                persona1.target.x += 25;
                
            } else {
                persona1.target.x -= 25;
            }
            
           if (fabs(pos_Pre - persona1.target.x ) == 100)
           {
                dax = true;
           }
            
        }
        
        
        if (persona1.target.y >= 414)
        {
            hit = true, Jump = true;
        }
        if (IsKeyPressed(KEY_SPACE) && Jump == true)
        { 
            persona1.velo = -PJS;
            Jump = false, hit = false;
            //PlaySound(jumpS);
        }
        if (!hit)
        {
            persona1.target.y += persona1.velo*delta;
            persona1.velo += G*delta;
            Jump = false;
        }
        
        
        // printf("%f\n", persona1.target.y);
        BeginDrawing();
        DrawTexture(textura, 0, 0, WHITE);
        DrawTexture(persona1.textura, persona1.target.x, persona1.target.y, WHITE);
        DrawText(TextFormat("Tempo: %.2fs\n", time), 60, 80, 20, RED);
        DrawRectangleLines(persona1.target.x, persona1.target.y, w, h, RED);
        for (int i = 0; i < eni_qtd; i++)
        {
            DrawRectangleRec(Pini[i].target, RED);
        }
        
        //printf("%f-%f\n", mouse.x, mouse.y);
        EndDrawing();
        for (int i = 0; i < eni_qtd; i++)
        {
            Pini[i].target.x -= Pini[i].velo;
        }
        
    }
}
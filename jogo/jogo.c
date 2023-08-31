#include <stdio.h>
#include "raylib.h"
#include "raymath.h"
void Joguinho();
/*int main()
{
    Joguinho();
    return 0;
}*/
#define G 850
#define PJS 350.0f
#define PHS 110.0f
typedef struct{
    Rectangle target;
    Texture2D textura;
    float velo;
}personagem;
void Joguinho(){
    int lar = 720, alt = 540, jump_height = 60;
    InitWindow(lar, alt, "Jogo");
    personagem persona1;
    persona1.target.height = 97;
    persona1.target.width = 86;
    Image imagem = LoadImage("fundo2.png");
    ImageResizeNN(&imagem, lar, alt);
    Image personagem = LoadImage("personagem-menor.png");
    ImageResizeNN(&personagem, 86, 97);
    persona1.textura = LoadTextureFromImage(personagem);
    Texture2D textura = LoadTextureFromImage(imagem);
    Image Espe_im = LoadImage("espada.png");
    ImageFlipHorizontal(&Espe_im);
    ImageResizeNN(&Espe_im, 50, 50);
    Texture2D espada = LoadTextureFromImage(Espe_im);

    persona1.target.x = lar / 2, persona1.target.y = 414;
    int space = 0;
    bool Jump = true, hit = true;
    char dir = 'D';
    //som----------------------------
    InitAudioDevice();
    Music musica = LoadMusicStream("zelda.mp3");
    Sound jumpS = LoadSoundFromWave(LoadWave("sound.wav"));
    Sound dash = LoadSoundFromWave(LoadWave("dash.wav"));
    //-------------------------------
    Rectangle enemy;
    enemy.height = 30;
    enemy.width = 30;
    enemy.x = lar - 50, enemy.y = 484;
    char Espa_Cont = 'C';
    // FPS tava influenciando na movimentacao, agora ta mais devagar
    SetTargetFPS(40);
    char morto = 'A';
    int w = 86, h = 97;
    int lifes = 100;
    while (!WindowShouldClose())
    {
        SetMasterVolume(50.0);
        UpdateMusicStream(musica);
        PlayMusicStream(musica);

        double time = GetTime();
        float delta = GetFrameTime();

        //printf("%d\n", fps);
        if(Jump == 1 && space == 0){
            Jump = 0;
        }
        Vector2 mouse = GetMousePosition();
        //printf("%f-%f\n", mouse.x, mouse.y);
        if (IsKeyDown(KEY_RIGHT))
        {
            persona1.target.x += 10;
            if (dir == 'E')
            {
                dir = 'D';
                ImageFlipHorizontal(&personagem);
                ImageFlipHorizontal(&Espe_im);
                espada = LoadTextureFromImage(Espe_im);
                persona1.textura = LoadTextureFromImage(personagem);
            }
            
        }
        if (IsKeyDown(KEY_LEFT))
        {
            persona1.target.x -= 10;
            if (dir == 'D')
            {
                dir = 'E';
                ImageFlipHorizontal(&personagem);
                ImageFlipHorizontal(&Espe_im);
                espada = LoadTextureFromImage(Espe_im);
                persona1.textura = LoadTextureFromImage(personagem);
            }
        }
        if (IsKeyPressed(KEY_D))
        {
            PlaySound(dash);
            if (dir == 'D')
            {
                persona1.target.x += 50;
            } else {
                persona1.target.x -= 50;
            }
            
        }
        if (IsKeyPressed(KEY_UP))
        {
            persona1.target.y -= 5;
        }
        if (IsKeyPressed(KEY_DOWN))
        {
            persona1.target.y += 5;
        }
        if (persona1.target.y >= 414)
        {
            hit = true, Jump = true;
        }
        if (IsKeyPressed(KEY_SPACE) && Jump == true)
        { 
            persona1.velo = -PJS;
            Jump = false, hit = false;
            PlaySound(jumpS);
        }
        if (!hit)
        {
            persona1.target.y += persona1.velo*delta;
            persona1.velo += G*delta;
            Jump = false;
        }
        if (Espa_Cont == 'B')
        {
            WaitTime(0.3);
            Espa_Cont = 'C';
            ImageFlipVertical(&Espe_im);
            espada = LoadTextureFromImage(Espe_im);
            //printf("Subiu\n");
        }
        if (IsKeyPressed(KEY_P) && Espa_Cont == 'C')
        {
                ImageFlipVertical(&Espe_im);
                espada = LoadTextureFromImage(Espe_im);
                Espa_Cont = 'B';
                //printf("Abaixou\n");
        }
        // Controle dos inimigos
        int dist = persona1.target.x - enemy.x;
        if (dist < 0)
        {
            enemy.x -= 0.5;
        }
        if (dist > 0)
        {
            enemy.x += 0.5;
        }
        

        // printf("%f\n", persona1.target.y);
        BeginDrawing();
        DrawTexture(textura, 0, 0, WHITE);
        int posEspada = 0;
        if (dir == 'D')
        {
            posEspada = 60;
        } else {
            posEspada = -5;
        }
        Rectangle esp_Box;
        esp_Box.height = espada.height;
        esp_Box.width = espada.width;
        esp_Box.x = posEspada + persona1.target.x;
        esp_Box.y = persona1.target.y + 55;

        if (CheckCollisionRecs(enemy, esp_Box) && Espa_Cont == 'B')
        {
            morto = 'D';
        }
        DrawTexture(persona1.textura, persona1.target.x, persona1.target.y, WHITE);
        DrawTexture(espada, posEspada + persona1.target.x, persona1.target.y + 55, WHITE);
        // debug do hitbox
        //DrawRectangleLines(persona1.target.x, persona1.target.y, w, h, RED);
        DrawText(TextFormat("Tempo: %.2fs\n", time), 60, 80, 20, RED);
        // ver como ta o sistema de vida
        DrawText("Vida: ", 60, 105, 20, RED);
        
        if ((lifes * 1.5) >= 75)
        {
            DrawRectangle(115, 107, (lifes * 1.5), 17, GREEN);
        } else if ((lifes * 1.5) < 75 && (lifes * 1.5) >= 40)
        {
            DrawRectangle(115, 107, (lifes * 1.5), 17, ORANGE);
        } else if ((lifes * 1.5) < 40)
        {
            DrawRectangle(115, 107, (lifes * 1.5), 17, RED);
        }
        if (morto == 'A')
        {
            DrawRectangleRec(enemy, RED);
        }
        if (CheckCollisionRecs(persona1.target, enemy) && morto == 'A')
        {
            //DrawText("MOrreu", 100, 100, 40, RED);
            lifes--;
        }
        if ((lifes * 1.5) <= 0)
        {
            CloseWindow();
        }
        
        //printf("%f-%f\n", mouse.x, mouse.y);
        EndDrawing();
    }
    UnloadMusicStream(musica);
    CloseAudioDevice();
}
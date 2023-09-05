void jogo_fase1(){
    // Inicializacao do fundo
    Image fundo = LoadImage("assets/imgs/fundo2.png");
    ImageResizeNN(&fundo, lar, alt);
    Texture2D textura_fundo = LoadTextureFromImage(fundo);

    // Inicializacao do personagem
    personagem persona1;
    persona1.target.height = 97;
    persona1.target.width = 86;
    Image personagem = LoadImage("assets/imgs/personagem-menor.png");
    ImageResizeNN(&personagem, 86, 97);
    persona1.textura = LoadTextureFromImage(personagem);
    persona1.target.x = lar / 2, persona1.target.y = 414;

    // Inicializacao da espada/arma e flip dela para acertar a posicao
    arma Espada;
    Image Espe_im = LoadImage("assets/imgs/espada.png");
    ImageFlipHorizontal(&Espe_im);
    ImageResizeNN(&Espe_im, 50, 50);
    Espada.textura = LoadTextureFromImage(Espe_im);
    Espada.target.height = Espada.textura.height;
    Espada.target.width = Espada.textura.width;

    // Parte de audio
    InitAudioDevice();
    Music musica = LoadMusicStream("assets/sounds/zelda.mp3");
    PlayMusicStream(musica);
    Sound jumpS = LoadSoundFromWave(LoadWave("assets/sounds/sound.wav"));
    
    //inimigo
    Rectangle enemy;
    enemy.height = 30;
    enemy.width = 30;
    enemy.x = lar - 50, enemy.y = 484;
    
    //projetil
    Rectangle projectile;
    projectile.height = 60;
    projectile.width = 20;
    projectile.x = lar - 50, projectile.y = 50;
    
    //prejetil2
    int tam=4;
    Vector2 ball[tam];
    for(int i=0; i<tam; i++){
        ball[i].y=0;
        ball[i].x=GetRandomValue(0, lar-20);
    }

    // Variaveis de controleF
    int space = 0, lifes = 100, posEspada = 0;
    char dir = 'D', morto = 'A', Espa_Cont = 'C';
    bool Jump = true, hit = true;
    SetTargetFPS(40);
    while (!WindowShouldClose())
    {
        // Atualizacao da colisao da arma
        Espada.target.x = posEspada + persona1.target.x;
        Espada.target.y = persona1.target.y + 55;

        double time = GetTime();
        float delta = GetFrameTime();
        SetMasterVolume(5.0);
        Vector2 mouse = GetMousePosition();
        //UpdateMusicStream(musica);
        // Logica de movimentacao do personagem
        if(Jump == 1 && space == 0){
            Jump = 0;
        }
        if (IsKeyDown(KEY_RIGHT))
        {
            persona1.target.x += 10;
            if (dir == 'E')
            {
                dir = 'D';
                ImageFlipHorizontal(&personagem);
                ImageFlipHorizontal(&Espe_im);
                Espada.textura = LoadTextureFromImage(Espe_im);
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
                Espada.textura = LoadTextureFromImage(Espe_im);
                persona1.textura = LoadTextureFromImage(personagem);
            }
        }
        if (IsKeyPressed(KEY_D))
        {
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
            //WaitTime(0.1);
            Espa_Cont = 'C';
            ImageFlipVertical(&Espe_im);
            Espada.textura = LoadTextureFromImage(Espe_im);
        }
        if (IsKeyPressed(KEY_P) && Espa_Cont == 'C')
        {
                ImageFlipVertical(&Espe_im);
                Espada.textura = LoadTextureFromImage(Espe_im);
                Espa_Cont = 'B';
        }

        if (dir == 'D')
        {
            posEspada = 60;
        } else {
            posEspada = -5;
        }
        
        // Controle do inimigo
        int dist = persona1.target.x - enemy.x;
        if (dist < 0)
        {
            enemy.x -= 0.5;
        }
        if (dist > 0)
        {
            enemy.x += 0.5;
        }
        
        //Queda do projetil
        projectile.y+=2;
        for(int i=0; i<tam; i++){
            ball[i].y+=3;
        }
        
        // Check de colisao entre inimigo e espada
        if (CheckCollisionRecs(enemy, Espada.target) && Espa_Cont == 'B')
        {
            morto = 'D';
        }
        // Faz a colisao da vida do personagem
        if (CheckCollisionRecs(persona1.target, enemy) && morto == 'A')
        {
            lifes--;
        }
        if ((lifes * 1.5) <= 0)
        {
            putName(time);
        }

        BeginDrawing();
        DrawTexture(textura_fundo, 0, 0, WHITE);
        DrawTexture(persona1.textura, persona1.target.x, persona1.target.y, WHITE);
        DrawTexture(Espada.textura, posEspada + persona1.target.x, persona1.target.y + 55, WHITE);
        //teste--------
        if(projectile.y<=alt)
            DrawRectangleRec(projectile, GREEN);
        
        for(int i=0; i<tam; i++){
            if(ball[i].y<=alt+20){
                DrawCircleV(ball[i], 20, PURPLE);
            }
        }
            
        //-------------
        DrawText(TextFormat("Tempo: %.2fs\n", time), 60, 80, 20, RED);
        DrawText("Vida: ", 60, 105, 20, RED);
        // Barrinha de vida
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
        // so desenha o inimigo se ele estiver vivo
        if (morto == 'A')
        {
            DrawRectangleRec(enemy, RED);
        }
        EndDrawing();
    }
}
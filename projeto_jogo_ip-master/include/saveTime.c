void save(char *name, float time){
    //salvar tempo em arquivo txt
    FILE *arq;
    arq = fopen("saves.txt", "w");
    if(arq == NULL){
        printf("Erro ao abrir arquivo.\n");
        exit(1);
    }
    fprintf(arq, "%s,%f\n", name, time);
    fclose(arq);
}
void viewSaves(){
    //InitWindow(alt, lar, "teste");
    Rectangle voltar;
    //dimensoes do botao
    voltar.height = 90;
    voltar.width = 280;
    //coordenadas do botao
    voltar.x = 225;
    voltar.y = 400;
    
    Record *saves=NULL;
    Record *aux=NULL;
    Record auxTroca;
    int qtdSaves=0;
    int i=0, j=0;
    
    //ler arquivo
    FILE *arq;
    arq = fopen("saves.txt", "r");
    if(arq == NULL){
        printf("Erro ao abrir arquivo.\n");
        exit(1);
    }
    while(!feof(arq)){
        aux = saves;
        saves = (Record*) realloc(aux, (qtdSaves+1)*sizeof(Record));
        if(saves == NULL){
            printf("Problema de alocacao!\n");
            free(aux);
            exit(1);
        }
        fscanf(arq, "%49[^,],%f\n", saves[qtdSaves].name, &saves[qtdSaves].time);
        qtdSaves++;
    }
    fclose(arq);
    //ordenar saves pelo tempo(menor)
    for(i=0; i<qtdSaves; i++){
        for(j=i; j<qtdSaves; j++){
            if(saves[i].time>saves[j].time){
                auxTroca=saves[i];
                saves[i]=saves[j];
                saves[j]=auxTroca;
            }
        }
    }
    
    InitWindow(lar, alt, "Saves");
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        DrawRectangle(80, 60, 570, 325, GRAY);
        
        //animacao do botao
        Vector2 pos = GetMousePosition();
        if (CheckCollisionPointRec(pos, voltar))
        {
            DrawRectangleRec(voltar, RED);
            DrawText("Voltar", posX_Ret + 80, 400 + 25, 35, WHITE);
            if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
                CloseWindow();
            }
        } else {
            DrawRectangleRec(voltar, GRAY);
            DrawText("Voltar", posX_Ret + 80, 400 + 25, 35, BLACK);
        }
        DrawText(TextFormat("RECORDS"), 310, 60, 20, BLACK);
        
        for(i=0; i<qtdSaves; i++){
            if(i<15){
                if(i==0){
                    DrawText(TextFormat("%d. %s", i+1, saves[i].name), 100, 80+20*i, 20, RED);
                    DrawText(TextFormat("%.3f", saves[i].time), 560, 80+20*i, 20, RED);
                }
                /*
                else if(i==1){
                    DrawText(TextFormat("%d. %s", i+1, saves[i].name), 100, 80+20*i, 20, RED);
                    DrawText(TextFormat("%.3f", saves[i].time), 560, 80+20*i, 20, RED);
                }
                else if(i==2){
                    DrawText(TextFormat("%d. %s", i+1, saves[i].name), 100, 80+20*i, 20, RED);
                    DrawText(TextFormat("%.3f", saves[i].time), 560, 80+20*i, 20, RED);
                }*/
                else{
                    DrawText(TextFormat("%d. %s", i+1, saves[i].name), 100, 80+20*i, 20, BLACK);
                    DrawText(TextFormat("%.3f", saves[i].time), 560, 80+20*i, 20, BLACK);
                }
            }
        }
        EndDrawing();
    }
    CloseWindow();
}
void putName(float time){
    //InitWindow(alt, lar, "teste");
    Rectangle voltar, avancar, textBox;
    //dimensoes do botao
    voltar.height = 90;
    voltar.width = 220;
    avancar.height = 90;
    avancar.width = 220;
    textBox.height = 70;
    textBox.width = 300;
    //coordenadas do botao
    voltar.x = 80;
    voltar.y = 400;
    avancar.x = 430;
    avancar.y = 400;
    textBox.x = 220;
    textBox.y = 200;
    
    char *name=NULL;
    char *aux=NULL;
    int tam=0;
    
    SetTargetFPS(10);
    int frameCounter=0;
    //InitWindow(lar, alt, "<Nome>");
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        DrawRectangle(80, 60, 570, 325, GRAY);
        
        DrawText(TextFormat("INSIRA SEU NOME"), 180, 80, 40, BLACK);
        
        //animacoes dos "retangulos"
        Vector2 pos = GetMousePosition();
        if (CheckCollisionPointRec(pos, voltar))
        {
            DrawRectangleRec(voltar, RED);
            DrawText("Voltar", 56 + 80, 400 + 25, 35, WHITE);
            if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
                CloseWindow();
            }
        } else {
            DrawRectangleRec(voltar, GRAY);
            DrawText("Voltar", 56 + 80, 400 + 25, 35, BLACK);
        }
        
        if (CheckCollisionPointRec(pos, avancar))
        {
            DrawRectangleRec(avancar, RED);
            DrawText("Avançar", 394 + 80, 400 + 25, 35, WHITE);
            if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
                save(name, time);
                CloseWindow();
            }
        } else {
            DrawRectangleRec(avancar, GRAY);
            DrawText("Avançar", 394 + 80, 400 + 25, 35, BLACK);
        }
        
        if (CheckCollisionPointRec(pos, textBox))
        {
            DrawRectangleRec(textBox, DARKGRAY);
            DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, RED);
            SetMouseCursor(MOUSE_CURSOR_IBEAM);
            frameCounter++;
            if((frameCounter/5)%2==0){
                DrawText("_", (int)textBox.x+10+MeasureText(name, 40), (int)textBox.y + 28, 40, MAROON);
            }
            int key = GetCharPressed();
            while(key > 0){
                if ((key >= 32) && (key <= 125) && (tam < MAX_LEN))
                {   
                    aux = name;
                    name = (char *) realloc(aux, (tam+1));
                    if(name == NULL){
                        printf("Problema de alocacao!\n");
                        free(aux);
                        exit(1);
                    }
                    name[tam] = (char)key;
                    name[tam+1] = '\0';
                    tam++;
                }
                key = GetCharPressed();
            }
            if (IsKeyPressed(KEY_BACKSPACE))
            {
                tam--;
                if (tam < 0) tam = 0;
                name[tam] = '\0';
            }
        } else {
            DrawRectangleRec(textBox, DARKGRAY);
            DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, BLACK);
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
            frameCounter=0;
        }
        DrawText(name, (int)textBox.x + 10, (int)textBox.y + 15, 40, MAROON);
        EndDrawing();
    }

}

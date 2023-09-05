void Manual(){
    botao comecar;
    comecar.frame.height = 90;
    comecar.frame.width = 280;
    comecar.frame.x = 225;
    comecar.frame.y = 400;
    strcpy(comecar.string, "Começar");
    while (!WindowShouldClose())
    {
        Vector2 pos = GetMousePosition();
        BeginDrawing();
        ClearBackground(WHITE);
        DrawRectangle(80, 60, 570, 305, GRAY);
        DrawText(TextFormat("MANUAL:\n\nTestando"), 80, 60, 20, BLACK);
        
        if (CheckCollisionPointRec(pos, comecar.frame))
        {
            if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
                jogo_fase1();
                //viewSaves();
            }
            DrawRectangleRec(comecar.frame, RED);
            DrawText(comecar.string, posX_Ret + 80, 400 + 25, 35, WHITE);
        } else {
            DrawRectangleRec(comecar.frame, GRAY);
            DrawText(comecar.string, posX_Ret + 80, 400 + 25, 35, BLACK);
        }
        EndDrawing();
    }
    
}
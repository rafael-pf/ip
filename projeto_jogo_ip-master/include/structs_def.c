typedef struct{
    Rectangle target;
    Texture2D textura;
    float velo;
} personagem;
typedef struct 
{
    Rectangle target;
    Texture2D textura;
} arma;
typedef struct 
{
    Rectangle frame;
    char string[100];
} botao;

typedef struct{
    char name[50];
    float time;
} Record;
// Posicao do botao do menu
#define posX_Ret 225
// Tamanho da janela
#define lar 720
#define alt 540
// Relacionados a mecanica de pulo
#define G 2000
#define PJS 750.0f
#define PHS 110.0f
#define MAX_LEN 11
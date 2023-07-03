#include <stdio.h>
typedef struct {
    unsigned char red, green, blue;
} RGB;

typedef struct {
    RGB ponto[1280][960];
} Tela;

int main(){
    Tela meuMonitor;
    
    meuMonitor.ponto[0][0].red = 255;
    meuMonitor.ponto[0][0].green = 0;
    meuMonitor.ponto[0][0].blue = 0;

    return 0;
}

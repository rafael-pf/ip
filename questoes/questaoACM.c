#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
    int col;
    float valor;
}Coluna;

typedef struct{
    int linha;
    int qtdCol;
    Coluna *pont;
}Linha;

Linha *preencheMatriz(int *qtdLinhas){
    Linha *matriz=NULL, *auxMat=NULL;
    char comando[4];
    int i=0;
    int l=0, c=0;
    float v=0;
    


    do{
        scanf("%d", &l);
        scanf("%d", &c);
        scanf("%f", &v);

        



        printf("Deseja continuar? Digite sim ou nao\n");
        scanf(" %s", comando);
    }while (strcmp(comando,"nao")!=0);


    


    
}

int main(void){
    int qtdLinhas=0;
    Linha *matriz=NULL;



    printf("Vamos preencher a matriz...\n");
    matriz = preencheMatriz(&qtdLinhas);

    


    return 0;
}

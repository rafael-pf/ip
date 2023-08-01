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
    Linha *mat=NULL, *auxMat=NULL;
    Coluna *auxCol=NULL;
    char comando[4];
    int tag_acheiL=0, tag_acheiC=0;
    int i=0, j=0;
    int l=0, c=0;
    float v=0;
    printf("digite o num da linha: \n");
    scanf("%d", &l);
    printf("digite o num da coluna: \n");
    scanf("%d", &c);
    printf("digite o valor: \n");
    scanf("%f", &v);

    mat = (Linha *) malloc((*qtdLinhas+1) * sizeof(Linha));
    
    (*mat).linha = l;
    (*mat).pont = (Coluna *) malloc(((*mat).qtdCol+1) * sizeof(Coluna));
    (*mat).pont[0].col= c;
    (*mat).pont[0].valor = v;
    mat[0].qtdCol=1;
    (*qtdLinhas)++;
    

    printf("Deseja continuar? Digite sim ou nao\n");
    scanf(" %s", comando);
    while (strcmp(comando,"nao")!=0) {
        tag_acheiL=0;
        tag_acheiC=0;
        printf("digite o num da linha: \n");
        scanf("%d", &l);
        printf("digite o num da coluna: \n");
        scanf("%d", &c);
        printf("digite o valor: \n");
        scanf("%f", &v);

        for(i=0; i<*qtdLinhas; i++){
            if(l==mat[i].linha){
                tag_acheiL=1;
                printf("Achei a linha\n");
                for(j=0; j<mat[i].qtdCol; j++){
                    tag_acheiC=1;
                    if(c==mat[i].pont[j].col){
                        printf("Achei a coluna\n");
                        mat[i].pont[j].valor = v;
                    }
                }
                if(tag_acheiC==0){
                    auxCol = mat[i].pont;
                    mat[i].pont = (Coluna *) realloc(auxCol, ((mat[i].qtdCol)+1) * sizeof(Coluna));
                    if(mat[i].pont==NULL){
                        printf("Problema de alocacao!\n");
                        for(i=0; i<*qtdLinhas; i++){
                            free(mat[i].pont);
                        }
                        free(mat);
                        exit(1);
                    }
                    mat[i].pont[mat[i].qtdCol].col = c;
                    mat[i].pont[mat[i].qtdCol].valor = v;
                    mat[i].qtdCol++;
                }
            }
        }
        if(tag_acheiL==0){
            auxMat=mat;
            mat = (Linha *) realloc(auxMat, ((*qtdLinhas) + 1)*sizeof(Linha));
            if(mat==NULL){
                printf("Problema de alocacao!\n");
                for(i=0; i<*qtdLinhas; i++){
                    free(mat[i].pont);
                }
                free(mat);
                exit(1);
            }  
            mat[*qtdLinhas].linha = l;
            mat[*qtdLinhas].pont = (Coluna *) malloc((mat[*qtdLinhas].qtdCol+1) * sizeof(Coluna));
            mat[*qtdLinhas].pont[0].col= c;
            mat[*qtdLinhas].pont[0].valor = v;
            mat[*qtdLinhas].qtdCol=1;
            (*qtdLinhas)++;
            
        }

         



        printf("Deseja continuar? Digite sim ou nao\n");
        scanf(" %s", comando);
    }
    
    //printf("linha 1: %d\ncoluna 1: %d\nvalor 1,1: %.1f\n", (*mat).linha, (*mat).pont[0].col, (*mat).pont[0].valor);

    


    return mat;
}

int main(){
    int qtdLinhas=0;
    int i=0, j=0;
    Linha *matriz=NULL;



    printf("Vamos preencher a matriz...\n");
    matriz = preencheMatriz(&qtdLinhas);

    for(i=0; i<qtdLinhas; i++){
        for(j=0; j<matriz[i].qtdCol; j++){
            printf("linha %d: %d\ncoluna %d: %d\nvalor %d,%d: %.1f\n", i+1, matriz[i].linha, j+1, matriz[i].pont[j].col, i+1, j+1, matriz[i].pont[j].valor);
        }
        printf("\n");
    }

    


    return 0;
}

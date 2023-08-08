#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int coluna;
    float valor;
} Coluna;

typedef struct{
    int linha;
    int qCol;
    Coluna *colunas;
} Linha;

int encontraLinha(int linha, int tam, Linha *mat){
    int i=0;
    for(i=0; i<tam; i++){
        if(linha == mat[i].linha){
            return i;
        }
    }
    return -1;
}

int encontraColuna(int coluna, int index, Linha* mat){
    int i=0;
    for(i=0; i<mat[index].qCol; i++){
        if(coluna == mat[index].colunas[i].coluna){
            return i;
        }
    }
    return -1;
}

Linha *preencheMatriz(int *qtdLinhas){
    Linha *mat=NULL, *auxLinha=NULL;
    Coluna *auxCol=NULL;
    int linha=0;
    int coluna=0;
    printf("Digite n para LINHA: \n");
    scanf("%d", &linha);
    printf("Digite n para COLUNA: \n");
    scanf("%d", &coluna);
    int respostaLinha = encontraLinha(linha, *qtdLinhas, mat);
    if(respostaLinha!=-1){
        int respostaColuna = encontraColuna(coluna, respostaLinha, mat);
        if(respostaColuna!=-1){
            scanf("%f", &mat[respostaLinha].colunas[respostaColuna].valor);
        }
        else{
            auxCol = mat[respostaLinha].colunas;
            mat[respostaLinha].colunas = (Coluna*) realloc(auxCol, (mat[respostaLinha].qCol+1)*sizeof(Coluna));
            if(mat[respostaLinha].colunas==NULL){
                printf("Problema de alocacao!\n");
                free(mat);
                exit(1);
            }
            mat[respostaLinha].colunas[mat[respostaLinha].qCol].coluna=coluna;
            scanf("%f", &mat[respostaLinha].colunas[mat[respostaLinha].qCol].valor);
            mat[respostaLinha].qCol++;
        }
    }
    else{
        auxLinha = mat;
        mat = (Linha *) realloc(auxLinha, (*qtdLinhas+1) * sizeof(Linha));






        
    }
}



void printMatriz(Linha *matriz){

}

int main(){
    Linha *matriz=NULL;
    int qLinhas=0;
    matriz = preencheMatriz(&qLinhas);


    return 0;
}

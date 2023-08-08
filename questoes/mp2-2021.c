#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char nome[50];
    int pontuacao;
    int tentativas;
} Competidor;

Competidor* leCompetidores(Competidor *competidores, int qtdAtual, int qtdTotal){
    


}

int** colocarTesouros(int **matriz, int n, int *numTesouros){
    int i=0, j=0;
    int **aux;
    aux = matriz;
    matriz = (int **) realloc(aux, n*sizeof(int *));
    if(matriz == NULL){
        printf("Problema de alocacao!\n");
        for(i=0; i<n; i++){
            free(matriz[i]);
        }
        free(matriz);
        exit(1);
    }

    int *aux2;
    
    for(i=0; i<n; i++){
        for(j=0; j<n; j++){
            if((4*i*i+3*j)%11==0){
                aux2 = matriz[i];
                matriz[i] = (int *) realloc(aux2, (j+1)*sizeof(int));
                if(matriz[i]==NULL){
                    printf("Problema de alocacao!\n");
                    for(i=0; i<n; i++){
                        free(matriz[i]);
                    }
                    free(matriz);
                    exit(1);
                }
                matriz[i][j]=1;
                (*numTesouros)--;
            }
        }
    }

    return matriz;
}

void acharVencedor(Competidor* competidores, int qtdTotal){

}


int main(){
    int **matriz=NULL;
    int n, qtdTesouros=0;
    int i=0, j=0;
    Competidor *competidores=NULL;
    printf("Defina o tamanho do lado da matriz: \n");
    scanf("%d", &n);
    printf("Defina a quantidade de tesouros: \n");
    scanf("%d", &qtdTesouros);

    matriz = colocarTesouros(matriz, n, &qtdTesouros);

    // for(i=0; i<n; i++){
    //     for(j=0; j<n; j++){
    //         if(matriz[i]==NULL){
                
    //             i++;
    //             j=0;
    //         }
    //         else if(matriz[i][j]!=1){
    //             printf("0  ");
    //         }
    //         else printf("%d  ", matriz[i][j]);
    //     }
    //     printf("\n");
    // }






    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char timeC[50];
    char timeV[50];
    int golsC;
    int golsV;
} Partida;

typedef struct{
    char nome[50];
    int pts;
    int pj;
    int vit;
    int e;
    int der;
    int gp;
    int gc;
    int sg;
} Time;

Partida *carregaPartidas(int *qtdPartidas){
    Partida *partidas=NULL;
    Partida *aux;
    char nomeC[50], nomeV[50];
    int golsC, golsV;
    FILE *arq;
    arq = fopen("jogos.txt", "r");
    if(arq == NULL){
        printf("Problema ao abrir arquivo!\n");
        exit(1);
    }
    while(!feof(arq)){
        aux = partidas;
        partidas = (Partida *) realloc(aux, ((*qtdPartidas)+1)*sizeof(Partida));
        if(partidas == NULL){ printf("Problema de alocacao!\n"); free(aux); exit(1);}
        fscanf(arq, " %s %d X %d %s ", nomeC, &golsC, &golsV, nomeV);
        strcpy(partidas[*qtdPartidas].timeC, nomeC);
        partidas[*qtdPartidas].golsC = golsC;
        strcpy(partidas[*qtdPartidas].timeV, nomeV);
        partidas[*qtdPartidas].golsV = golsV;
        (*qtdPartidas)++;
    }
    printf("Partidas lidas com sucesso!\n");
    return partidas;
}

void geraTabela(Partida *partidas, int qtdPartidas){
    // Time *times=NULL;
    // Time *aux;
    // int qtdTimes=0;
    // times = (Time *) malloc((qtdTimes+2)*sizeof(Time));
    // if(times == NULL){ printf("Problema de alocacao!\n"); free(partidas); exit(1); }
    // strcpy(times[qtdTimes].nome, partidas[0].timeC);
    // strcpy(times[qtdTimes+1].nome, partidas[0].timeV);
    // if(partidas[0].golsC>partidas[0].golsV){
    //     times[qtdTimes].pts=3;
    //     times[qtdTimes].vit=1;
    //     times[qtdTimes+1].pts=0;
    // }
    // else if(partidas[0].golsV>partidas[0].golsC){

    // }
    // else{

    // }
}

int main(){
    Partida *partidas=NULL;
    int qtdPartidas=0;
    int comando=0;

    do{
        printf("=============MENU=============\n");
        printf("Que operacao deseja realizar?\n");
        printf("1) Carregar partidas\n");
        printf("2) Gerar tabela\n");
        printf("3) Sair\n");
        scanf("%d", &comando);
        switch (comando)
        {
        case 1:
            //carregar partidas
            partidas = carregaPartidas(&qtdPartidas);
            break;
        case 2:
            //gerar tabela
            geraTabela(partidas, qtdPartidas);
            break;
        case 3:
            //sair
            printf("Saindo...\n");
            break;
        default:
            printf("Escolha invalida!\n");
            break;
        }
    }while(comando != 3);

    // for(int i=0; i<qtdPartidas; i++){
    //     printf("\t%s %d X %d %s\n", partidas[i].timeC, partidas[i].golsC, partidas[i].golsV, partidas[i].timeV);
    // }

    return 0;
}

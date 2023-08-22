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
        fscanf(arq, " %49[^ 0-9] %d X %d %49[^\n] ", nomeC, &golsC, &golsV, nomeV);
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
    Time *times=NULL;
    Time *aux;
    int qtdTimes=0, tag_acheiC=0, tag_acheiV=0;
    for(int i=0; i<qtdPartidas; i++){
        tag_acheiC=0;
        tag_acheiV=0;
        for(int j=0; j<qtdTimes; j++){
            if(strcmp(partidas[i].timeC, times[j].nome)==0){
                tag_acheiC=1;
                times[j].pj+=1;
                if(partidas[i].golsC>partidas[i].golsV) {times[j].pts+=3; times[j].vit+=1; times[j].e+=0; times[j].der+=0; times[j].gp+=partidas[i].golsC; times[j].gc+=partidas[i].golsV; times[j].sg += partidas[i].golsC - partidas[i].golsV; }
                else if(partidas[i].golsC<partidas[i].golsV) {times[j].pts+=0; times[j].vit+=0; times[j].e+=0; times[j].der+=1; times[j].gp+=partidas[i].golsC; times[j].gc+=partidas[i].golsV; times[j].sg += partidas[i].golsC - partidas[i].golsV; }
                else {times[j].pts+=1; times[j].vit+=0; times[j].e+=1; times[j].der+=0; times[j].gp+=partidas[i].golsC; times[j].gc+=partidas[i].golsV; times[j].sg += partidas[i].golsC - partidas[i].golsV; }
            }
            else if(strcmp(partidas[i].timeV, times[j].nome)==0){
                tag_acheiV=1;
                times[j].pj+=1;
                if(partidas[i].golsC<partidas[i].golsV) {times[j].pts+=3; times[j].vit+=1; times[j].e+=0; times[j].der+=0; times[j].gp+=partidas[i].golsV; times[j].gc+=partidas[i].golsC; times[j].sg += partidas[i].golsV - partidas[i].golsC; }
                else if(partidas[i].golsC>partidas[i].golsV) {times[j].pts+=0; times[j].vit+=0; times[j].e+=0; times[j].der+=1; times[j].gp+=partidas[i].golsV; times[j].gc+=partidas[i].golsC; times[j].sg += partidas[i].golsV - partidas[i].golsC; }
                else {times[j].pts+=1; times[j].vit+=0; times[j].e+=1; times[j].der+=0; times[j].gp+=partidas[i].golsV; times[j].gc+=partidas[i].golsC; times[j].sg += partidas[i].golsV - partidas[i].golsC; }
            }
        }
        if(tag_acheiC==0){
            aux = times;
            times = (Time *) realloc(aux, (qtdTimes+1)*sizeof(Time));
            strcpy(times[qtdTimes].nome, partidas[i].timeC);
            times[qtdTimes].pj=1;
            if(partidas[i].golsC>partidas[i].golsV) {times[qtdTimes].pts=3; times[qtdTimes].vit=1; times[qtdTimes].e=0; times[qtdTimes].der=0; times[qtdTimes].gp=partidas[i].golsC; times[qtdTimes].gc=partidas[i].golsV; times[qtdTimes].sg = partidas[i].golsC - partidas[i].golsV; }
            else if(partidas[i].golsC<partidas[i].golsV) {times[qtdTimes].pts=0; times[qtdTimes].vit=0; times[qtdTimes].e=0; times[qtdTimes].der=1; times[qtdTimes].gp=partidas[i].golsC; times[qtdTimes].gc=partidas[i].golsV; times[qtdTimes].sg = partidas[i].golsC - partidas[i].golsV; }
            else {times[qtdTimes].pts=1; times[qtdTimes].vit=0; times[qtdTimes].e=1; times[qtdTimes].der=0; times[qtdTimes].gp=partidas[i].golsC; times[qtdTimes].gc=partidas[i].golsV; times[qtdTimes].sg = partidas[i].golsC - partidas[i].golsV; }
            qtdTimes++;
        }
        if(tag_acheiV==0){
            aux = times;
            times = (Time *) realloc(aux, (qtdTimes+1)*sizeof(Time));
            strcpy(times[qtdTimes].nome, partidas[i].timeV);
            times[qtdTimes].pj=1;
            if(partidas[i].golsC<partidas[i].golsV) {times[qtdTimes].pts=3; times[qtdTimes].vit=1; times[qtdTimes].e=0; times[qtdTimes].der=0; times[qtdTimes].gp=partidas[i].golsV; times[qtdTimes].gc=partidas[i].golsC; times[qtdTimes].sg = partidas[i].golsV - partidas[i].golsC; }
            else if(partidas[i].golsC>partidas[i].golsV) {times[qtdTimes].pts=0; times[qtdTimes].vit=0; times[qtdTimes].e=0; times[qtdTimes].der=1; times[qtdTimes].gp=partidas[i].golsV; times[qtdTimes].gc=partidas[i].golsC; times[qtdTimes].sg = partidas[i].golsV - partidas[i].golsC; }
            else {times[qtdTimes].pts=1; times[qtdTimes].vit=0; times[qtdTimes].e=1; times[qtdTimes].der=0; times[qtdTimes].gp=partidas[i].golsV; times[qtdTimes].gc=partidas[i].golsC; times[qtdTimes].sg = partidas[i].golsV - partidas[i].golsC; }
            qtdTimes++;
        }   
    }
    Time auxTroca;
    for(int i=0; i<qtdTimes; i++){
        for(int j=i+1; j<qtdTimes; j++){
            if(times[i].pts<times[j].pts){
                auxTroca = times[i];
                times[i] = times[j];
                times[j] = auxTroca;
            }
            if(times[i].pts==times[j].pts){
                if(times[i].vit<times[j].vit){
                    auxTroca = times[i];
                    times[i] = times[j];
                    times[j] = auxTroca;
                }
                if(times[i].vit==times[j].vit){
                    if(times[i].sg<times[i].sg){
                        auxTroca = times[i];
                        times[i] = times[j];
                        times[j] = auxTroca;
                    }
                    if(times[i].sg==times[j].sg){
                        if(strcmp(times[i].nome, times[i].nome)>0){
                            auxTroca = times[i];
                            times[i] = times[j];
                            times[j] = auxTroca;
                        }
                    }
                }
            }
        }
    }
    printf("POS \tTime\t\t\tPJ\tPTS\tVIT\tE\tDER\tGP\tGC\tSG\n");
    for(int i=0; i<qtdTimes; i++){
        if(strlen(times[i].nome)<=5){
            printf("%d.\t%s    \t\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", i+1,times[i].nome, times[i].pj, times[i].pts, times[i].vit, times[i].e, times[i].der, times[i].gp, times[i].gc, times[i].sg);
        }
        else
            printf("%d.\t%s\t\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", i+1,times[i].nome, times[i].pj, times[i].pts, times[i].vit, times[i].e, times[i].der, times[i].gp, times[i].gc, times[i].sg);
    }
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
    free(partidas);
    return 0;
}

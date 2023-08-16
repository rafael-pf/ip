#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char nome[50];
    char cpf[12];
    int qtdNotas;
    float *notas;
} Aluno;

Aluno *carregaAlunos(int *qtdAlunos){
    Aluno *alunos=NULL;
    Aluno *aux;
    FILE *arq;
    arq = fopen("alunos.txt", "r");
    if(arq == NULL){
        printf("Problema ao abrir arquivo.\n");
        exit(1);
    }
    while(!feof(arq)){
        aux = alunos;
        alunos = (Aluno *) realloc(aux, ((*qtdAlunos)+1) * sizeof(Aluno));
        if(alunos == NULL){printf("Problema de alocacao!\n"); free(aux); exit(1);}
        fscanf(arq, " %49[^\n]", alunos[*qtdAlunos].nome);
        fscanf(arq, " %11[^\n]", alunos[*qtdAlunos].cpf);
        alunos[*qtdAlunos].qtdNotas = 0;
        alunos[*qtdAlunos].notas = NULL;
        (*qtdAlunos)++;
    }
    fclose(arq);
    return alunos;
}
float *leNotas(int *qtdNotas){
    float *vet=NULL, *aux;
    float n;
    printf("Digite as notas (caso deseje parar, digite um numero negativo): \n");
    do{
        scanf("%f", &n);
        if(n>=0){
            aux = vet;
            vet = (float *) realloc(aux, ((*qtdNotas)+1)*sizeof(float));
            if(vet == NULL){
                printf("Problema de alocacao!\n");
                free(aux);
                exit(1);
            }
            vet[*qtdNotas] = n;
            (*qtdNotas)++;
            printf("Nota cadastrada com sucesso.\n");
        }
        else{ printf("Insercao de notas encerrada.\n"); }
    }while(n>=0);
    return vet;
}
float media(float *notas, int qtdNotas){
    int i;
    float soma=0;
    for(i=0; i<qtdNotas; i++){
        soma+=notas[i];
    }
    return (soma/qtdNotas);
}
void ordena(Aluno *alunos, int qtdAlunos){
    int i, j;
    Aluno aux;
    for(i=0; i<qtdAlunos; i++){
        for(j=i+1; j<qtdAlunos; j++){
            if(media(alunos[i].notas, alunos[i].qtdNotas) < media(alunos[j].notas, alunos[j].qtdNotas)){
                aux = alunos[i];
                alunos[i] = alunos[j];
                alunos[j] = aux;
            }
        }
    }
}

void salvaAlunos(Aluno *alunos, int qtdAlunos){
    FILE *arq;
    arq = fopen("alunos.bin", "w");
    if(arq == NULL){
        printf("Problema ao abrir o arquivo.\n");
        free(alunos);
        exit(1);
    }
    int i=0;
    int tamNOME;
    int tamCPF;
    fwrite(&qtdAlunos, sizeof(int), 1, arq);
    for(i=0; i<qtdAlunos; i++){
        tamNOME = strlen(alunos[i].nome)+1;
        tamCPF = strlen(alunos[i].cpf)+1;
        fwrite(&tamNOME, sizeof(int), 1, arq);
        fwrite(&alunos[i].nome, sizeof(char), tamNOME, arq);
        fwrite(&tamCPF, sizeof(int), 1, arq);
        fwrite(&alunos[i].cpf, sizeof(char), tamCPF, arq);
        fwrite(&alunos[i].qtdNotas, sizeof(int), 1, arq);
        for(int j=0; j<alunos[i].qtdNotas; j++){
            fwrite(&alunos[i].notas[j], sizeof(float), 1, arq);
        }
    }
    fclose(arq);
}

int main(){
    Aluno *alunos=NULL;
    int qtdAlunos=0, qtdNotas=0;
    int i=0, j=0;

    alunos = carregaAlunos(&qtdAlunos);
    qtdAlunos--;
    
    for(i=0; i<qtdAlunos; i++){
        printf("Cadastrando notas de %s...\n", alunos[i].nome);
        alunos[i].notas = leNotas(&alunos[i].qtdNotas);
    }
    
    ordena(alunos, qtdAlunos);

    salvaAlunos(alunos, qtdAlunos);

    for(i=0; i<qtdAlunos; i++){
        printf("Nome: %s\nCpf: %s\n", alunos[i].nome, alunos[i].cpf);
        printf("Notas: \n");
        for(j=0; j<alunos[i].qtdNotas; j++){
            printf("\t%.1f\n", alunos[i].notas[j]);
        }
    }

    free(alunos);
    return 0;
}

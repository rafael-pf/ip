#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char nome[50];
    char cpf[12];
    int qtdNotas;
    float *notas;
} Aluno;

int main(){
    FILE *arq;
    int qtdAlunos=0;
    arq = fopen("alunos.bin", "r");
    if(arq == NULL){
        printf("Problema ao abrir o arquivo!\n");
        exit(1);
    }
    int tamNOME;
    int tamCPF;
    int desloc=0;
    fread(&qtdAlunos, sizeof(int), 1, arq);
    fseek(arq, +sizeof(int), SEEK_SET);
    desloc+=sizeof(int);
    Aluno alunos[qtdAlunos];
    for(int i=0; i<qtdAlunos; i++){
        fread(&tamNOME, sizeof(int), 1, arq);
        desloc+=sizeof(int);
        fseek(arq, desloc, SEEK_SET);
        fread(&alunos[i].nome, sizeof(char), tamNOME, arq);
        desloc+=tamNOME;
        fseek(arq, desloc, SEEK_SET);
        fread(&tamCPF, sizeof(int), 1, arq);
        desloc+=sizeof(int);
        fseek(arq, desloc, SEEK_SET);
        fread(&alunos[i].cpf, sizeof(char), tamCPF, arq);
        desloc+=tamCPF;
        fseek(arq, desloc, SEEK_SET);
        fread(&alunos[i].qtdNotas, sizeof(int), 1, arq);
        desloc+=sizeof(int);
        fseek(arq, desloc, SEEK_SET);
        alunos[i].notas = (float*) malloc(alunos[i].qtdNotas * sizeof(float));
        for(int j=0; j<alunos[i].qtdNotas; j++){
            fread(&alunos[i].notas[j], sizeof(float), 1, arq);
            desloc+=sizeof(float);
            fseek(arq, desloc, SEEK_SET);
        }
    }
    fclose(arq);

    //printf("qtd: %d\n", qtdAlunos);
    
    for(int i=0; i<qtdAlunos; i++){
        printf("Nome: %s\nCpf: %s\n", alunos[i].nome, alunos[i].cpf);
        printf("Notas: \n");
        for(int j=0; j<alunos[i].qtdNotas; j++){
            printf("\t%.1f\n", alunos[i].notas[j]);
        }
    }

    return 0;
}

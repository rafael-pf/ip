#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char nome[50];
    char cpf[12];
    int qtdNotas;
    int *notas;
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
        (*qtdAlunos)++;
    }
    fclose(arq);
    return alunos;
}
float *leNotas(int *qtdNotas){

}
float media(float *notas, int qtdNotas){

}
void ordena(Aluno *alunos, int qtdAlunos){

}
void salvaAlunos(Aluno *alunos, int qtdAlunos){

}

int main(){
    Aluno *alunos=NULL;
    float *notas=NULL;
    int qtdAlunos=0;
    alunos = carregaAlunos(&qtdAlunos);
    qtdAlunos--;
    /*for(int i=0; i<qtdAlunos; i++){
        printf("Nome: %s\nCpf: %s\n", alunos[i].nome, alunos[i].cpf);
    }*/
    


    return 0;
}

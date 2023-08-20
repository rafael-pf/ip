#include <stdio.h>
#include <stdlib.h>

typedef struct{
    float pReal;
    float pImag;
} Complexo;

void empilhe(Complexo **cPilha, Complexo umC, int *tPilha){
    Complexo *aux = (*cPilha);
    (*cPilha) = (Complexo *) realloc(aux, ((*tPilha)+1)*sizeof(Complexo));
    if((*cPilha)==NULL){
        printf("Problema de alocacao!\n");
        free(aux);
        exit(1);
    }
    (*cPilha)[*tPilha].pReal = umC.pReal;
    (*cPilha)[*tPilha].pImag = umC.pImag;
    (*tPilha)++;
    printf("Empilhamento bem sucedido!\n");
}

Complexo desempilhe(Complexo **cPilha, int *tPilha){
    Complexo *aux = (*cPilha);
    Complexo rmv = (*cPilha)[(*tPilha)-1];
    (*tPilha)--;
    (*cPilha) = (Complexo *) realloc(aux, (*tPilha) * sizeof(Complexo));
    if((*cPilha) == NULL && (*tPilha>0)){
        printf("Problema de alocacao!\n");
        free(aux);
        exit(1);
    }
    printf("Desempilhamento bem sucedido!\n");
    return rmv;
}

Complexo topo(Complexo *cPilha, int tPilha){
    return cPilha[tPilha-1];
}

int pilhaVazia(Complexo *cPilha, int tPilha){
    if(cPilha==NULL || tPilha==0) return 1; 
    else return 0;
}

void salvePilha(Complexo *cPilha, int tPilha){
    FILE *arq;
    arq = fopen("pilha.bin", "w");
    if(arq == NULL){
        printf("Problema ao abrir o arquivo!\n");
        free(cPilha);
        exit(1);
    }
    fwrite(&tPilha, sizeof(int), 1, arq);
    for(int i=0; i<tPilha; i++){
        fwrite(&cPilha[i], sizeof(Complexo), 1, arq);
    }
    fclose(arq);
    printf("Pilha salva com sucesso.\n");
}

Complexo *recuperePilha(int *tPilha){
    Complexo *pilha=NULL;
    FILE *arq;
    arq = fopen("pilha.bin", "rb");
    if(arq == NULL){
        printf("Problema ao abrir arquivo!\n");
        free(pilha);
        exit(1);
    }
    fread(&*tPilha, sizeof(int), 1, arq);
    pilha = (Complexo *) malloc((*tPilha) * sizeof(Complexo));
    for(int i=0 ; i<*tPilha; i++){
        fread(&pilha[i], sizeof(Complexo), 1, arq);
    }
    fclose(arq);
    return pilha;
}

int main(){
    Complexo  *pilha=NULL;
    Complexo compADD, compTOP;
    int tamPilha=0;
    int comando=0;
    do{
        printf("=============MENU=============\n");
        printf("Que operacao deseja realizar?\n");
        printf("1)Empilhar\n");
        printf("2)Desempilhar\n");
        printf("3)Ver topo\n");
        printf("4)Verificar se esta vazia\n");
        printf("5)Salvar pilha\n");
        printf("6)Recuperar pilha\n");
        printf("7)Sair\n->");
        scanf("%d", &comando);
        switch (comando)
        {
        case 1:
            //empilhar
            printf("Digite a parte real:\n");
            scanf("%f", &compADD.pReal);
            printf("Digite a parte imaginaria:\n");
            scanf("%f", &compADD.pImag);
            empilhe(&pilha, compADD, &tamPilha);
            break;
        case 2:
            //desempilhar
            if(pilhaVazia(pilha, tamPilha) == 0){
                desempilhe(&pilha, &tamPilha);
            }
            else printf("A pilha esta vazia!\n");
            break;
        case 3:
            //ver topo
            if(pilhaVazia(pilha, tamPilha) == 0){
                compTOP = topo(pilha, tamPilha);
                if(compTOP.pImag>0)
                    printf("Topo: \n\t%.1f + %.1fi\n", compTOP.pReal, compTOP.pImag);
                else if(compTOP.pImag<0)
                    printf("Topo: \n\t%.1f - %.1fi\n", compTOP.pReal, -compTOP.pImag);
                else
                    printf("Topo: \n\t%.1f\n", compTOP.pReal);
            }
            else printf("A pilha esta vazia!\n");
            break;
        case 4:
            //verificar se esta vazia
            if(pilhaVazia(pilha, tamPilha) == 1) printf("A pilha ESTA vazia.\n");
            else printf("A pilha NAO ESTA vazia.\n");
            break;
        case 5:
            //salvar
            salvePilha(pilha, tamPilha);
            break;
        case 6:
            //recuperar
            pilha = recuperePilha(&tamPilha);
            for(int i=0; i<tamPilha; i++){
                if(pilha[i].pImag>0)
                    printf("Complexo: \n\t%.1f + %.1fi\n", pilha[i].pReal, pilha[i].pImag);
                else if(pilha[i].pImag<0)
                    printf("Complexo: \n\t%.1f - %.1fi\n", pilha[i].pReal, -pilha[i].pImag);
                else
                    printf("Complexo: \n\t%.1f\n", pilha[i].pReal);
            }
            break;
        case 7:
            //sair
            printf("Saindo...\n");
            break;
        default:
            //comando invalido
            printf("Comando invalido!\n");
            break;
        }
    }while(comando!=7);

    
    free(pilha);
    return 0;
}

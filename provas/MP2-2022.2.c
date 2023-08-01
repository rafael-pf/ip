#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
    char Placa[6];
}Caminhao;

typedef struct{
    int codigo;
    float loc_x, loc_y;
    Caminhao *caminhao;
    int n_caminhao;
}Filial;

typedef struct{
    float origem_x, origem_y;
    float destino_x, destino_y;
}Produto;

void limpar(Filial *filiais){
    

};

Filial *cadastrar_filial(Filial *filiais, int *n_filiais){
    float x=0, y=0;
    Filial *auxFil=NULL;
    auxFil = filiais;
    filiais = (Filial *) realloc(auxFil, ((*n_filiais)+1)*sizeof(Filial));
    if(filiais==NULL){
        printf("Problema de alocacao!\n");
        limpar(filiais);
        exit(1);
    }
    filiais[*n_filiais].codigo = *n_filiais;
    printf("Digite a coordenada x da filial: \n");
    scanf(" %f", &filiais[*n_filiais].loc_x);
    printf("Digite a coordenada y da filial: \n");
    scanf(" %f", &filiais[*n_filiais].loc_y);
    (*n_filiais)++;
    return filiais;
}

Filial *cadastrar_caminhao(Filial *filiais, Caminhao caminhao, int codigo_filial){
    Caminhao *auxCam=NULL;
    auxCam = filiais[codigo_filial].caminhao;
    filiais[codigo_filial].caminhao = (Caminhao *) realloc(auxCam, (filiais[codigo_filial].n_caminhao+1)*sizeof(Caminhao));
    if(filiais[codigo_filial].caminhao==NULL){
        printf("Problema de alocacao!\n");
        limpar(filiais);
        exit(1);
    }
    filiais[codigo_filial].caminhao[filiais[codigo_filial].n_caminhao] = caminhao;
    filiais[codigo_filial].n_caminhao++;
    return filiais;
}

Caminhao remover_caminhao(Filial **filiais, int codigo_filial){
    int i=0, j=0;
    Caminhao *auxCam=NULL;
    auxCam = (*filiais)[codigo_filial].caminhao;
    Caminhao camREMOVIDO;
    camREMOVIDO = (*filiais)[codigo_filial].caminhao[(*filiais)[codigo_filial].n_caminhao-1];
    (*filiais)[codigo_filial].caminhao = (Caminhao *) realloc(auxCam, ((*filiais)[codigo_filial].n_caminhao-1)*sizeof(Caminhao));
    if((*filiais)[codigo_filial].caminhao==NULL){
        printf("Problema de alocacao!\n");
        limpar(filiais);
        exit(1);
    }
    (*filiais)[codigo_filial].n_caminhao--;
    return camREMOVIDO;
}

void realizar_entrega(Filial *filiais, Produto produto, int n_filiais){
    int i=0, j=0;
    float menorDistIr=100000, menorDistVoltar=100000;
    for(i=0; i<n_filiais; i++){
        if(filiais[i].loc_x*filiais[i].loc_x + filiais[i].loc_y*filiais[i].loc_y < menorDistIr){
            
        }
    }



}

void imprimir_filiais(Filial *filiais, int n_filiais){
    int i=0, j=0;
    for(i=0; i<n_filiais; i++){
        printf("Filial %d :\n", i);
        printf("\t x: %.2f\n", filiais[i].loc_x);
        printf("\t y: %.2f\n", filiais[i].loc_y);
        printf("\tCaminhoes: \n");
        for(j=0; j<filiais[i].n_caminhao; j++){
            printf("\t\t%d. %s\n", j+1, filiais[i].caminhao[j].Placa);
        }
    }
}


int main(){
    int comando;
    int filialADD;
    Caminhao caminhaoADD, caminhaoREMOVIDO;
    Filial *filial=NULL;
    Produto produto;printf("Digite a : \n");
    int n_filiais=0;

    int teste;

    do{
        printf("Qual operacao deseja realizar?\nDigite 1 se deseja CADASTRAR FILIAL\nDigite 2 se deseja CADASTRAR CAMINHAO\nDigite 3 se deseja REALIZAR ENTREGA\nDigite 4 se deseja IMPRIMIR FILIAIS\nDigite 5 se deseja SAIR\n->");
        scanf("%d", &comando);
        if(comando==1){
            printf("->Cadastrando filial...\n");
            filial = cadastrar_filial(filial, &n_filiais);
        }
        else if(comando==2){
            printf("->Cadastrando caminhao...\n");
            printf("Digite o codigo da filial: \n");
            scanf("%d", &filialADD);
            printf("Digite a placa do caminhao: \n");
            scanf("%s", caminhaoADD.Placa);
            filial = cadastrar_caminhao(filial, caminhaoADD, filialADD);
        }
        else if(comando==3){
            printf("->Realizando entrega...\n");
            printf("Digite a coordenada x da origem: \n");
            scanf("%f", &produto.origem_x);
            printf("Digite a coordenada y da origem: \n");
            scanf("%f", &produto.origem_y);
            printf("Digite a coordenada x do destino: \n");
            scanf("%f", &produto.destino_x);
            printf("Digite a coordenada y do destino: \n");
            scanf("%f", &produto.destino_y);

            realizar_entrega(filial, produto, n_filiais);



            /*printf("Digite o codigo da filial: \n");
            scanf("%d", &teste);
            caminhaoREMOVIDO = remover_caminhao(&filial, teste);
            printf("Placa do caminhao removido: %s\n", caminhaoREMOVIDO.Placa);*/
        }
        else if(comando==4){
            imprimir_filiais(filial, n_filiais);
        }
        else if(comando>5){
            printf("Escolha invalida!\n");
        }
    }while(comando!=5);
    printf("Saindo...\n");





    return 0;
}

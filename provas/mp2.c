#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char nome[50];
    char raca[50];
    int idade;
    float salario;
    char CPF[12];
} Pessoa;

typedef struct{
    char nome[50];
    int codigo;
    Pessoa* cidadaos;
    int capacidade;
} Cidade;

Cidade* NovaCidade(Cidade* censo, int* tam);
void InserirOuAtualizar(Cidade* censo, int tam);
void Remover(Cidade* censo, int tam);
void Procura(Cidade* censo, int tam);
void ViewTable(Cidade* censo, int tam);
void Desaloca(Cidade* censo, int tam);

int main(){
    Cidade *cidades=NULL;
    int nCidades=0;
    int comando=0;

    printf("Bem vindo!\n");

    do{
    printf("==============================MENU==============================\n");
    printf("Que operacao deseja realizar?\n");
    printf("Digite 1 se deseja CADASTRAR UMA CIDADE\n");
    printf("Digite 2 se deseja PROCURAR AS INFORMACOES DE UM CPF ESPECIFICO\n");
    printf("Digite 3 se deseja VER TODOS OS DADOS REGISTRADOS\n");
    printf("Digite 4 se deseja ADICIONAR/ATUALIZAR OS DADOS DE UMA PESSOA\n");
    printf("Digite 5 se deseja REMOVER UMA PESSOA\n");
    printf("Digite 6 se deseja SAIR DO PROGRAMA\n->");
    scanf("%d", &comando);
    if(comando == 1){
        cidades = NovaCidade(cidades, &nCidades);
    }
    else if(comando == 2){
        Procura(cidades, nCidades);
    }
    else if(comando == 3){
        ViewTable(cidades, nCidades);
    }
    else if(comando == 4){
        InserirOuAtualizar(cidades, nCidades);
    }
    else if(comando == 5){
        Remover(cidades, nCidades);
    }
    else if(comando == 6){
        printf("Saindo...\n");
    }
    else{
        printf("Escolha invalida!\n");
    }
    } while(comando!=6);
    
    Desaloca(cidades, nCidades);

    return 0;
}


////////////////////////////////////FUNCOES//////////////////////////////////////


Cidade* NovaCidade(Cidade* censo, int* tam){
    Cidade *aux=censo;
    char name[50];
    int cod=0;
    int i=0;
    printf("Digite o nome da cidade: \n");
    scanf(" %s", name);
    printf("Digite o codigo da cidade: \n");
    scanf("%d", &cod);
    //se sobrar tempo, conferir se esse codigo ja existe
    for(i=0; i<*tam; i++){
        if(cod == censo[i].codigo){
            printf("Esse codigo ja existe!\n");
            return censo;
        }
    }
    //realoca
    censo = (Cidade*) realloc(aux, ((*tam)+1) * sizeof(Cidade));
    if(censo == NULL){
        printf("Problema de alocacao!\n");
        for(int i=0; i<*tam; i++){
            free(aux[i].cidadaos);
        }
        free(aux);
        exit(1);
    }
    //adiciona dados
    strcpy(censo[*tam].nome,name);
    censo[*tam].codigo = cod;
    censo[*tam].capacidade = 0;
    (*tam)++;
    
    printf("Cidade adicionada com sucesso!\n");
    return censo;
}

void InserirOuAtualizar(Cidade* censo, int tam){
    char name[50];
    int i=0, j=0;
    char nomeADD[50], racaADD[50], cpfADD[12];
    int idadeADD=0;
    float salarioADD=0;
    int tag_acheiCidade=0, tag_acheiCPF=0;
    printf("Digite o nome da cidade: \n");
    scanf(" %s", name);
    for(i=0; i<tam; i++){
        if(strcmp(censo[i].nome, name)==0){
            tag_acheiCidade=1;
            printf("Digite o nome do cidadao: \n");
            scanf(" %s", nomeADD);
            printf("Digite a raca do cidadao: \n");
            scanf(" %s", racaADD);
            printf("Digite a idade do cidadao: \n");
            scanf("%d", &idadeADD);
            printf("Digite o salario do cidadao: \n");
            scanf("%f", &salarioADD);
            printf("Digite o CPF do cidadao: \n");
            scanf(" %s", cpfADD);
            for(j=0; j<censo[i].capacidade; j++){
                if(strcmp(cpfADD, censo[i].cidadaos[j].CPF)==0){ //se ja existir cpf, atualiza
                    tag_acheiCPF=1;
                    strcpy(censo[i].cidadaos[j].nome, nomeADD);
                    strcpy(censo[i].cidadaos[j].raca, racaADD);
                    censo[i].cidadaos[j].idade = idadeADD;
                    censo[i].cidadaos[j].salario = salarioADD;
                    printf("Dados atualizados com sucesso!\n");
                }
            }
            if(tag_acheiCPF == 0){ //caso nao exista o cpf, adiciona
                Cidade *aux=censo;
                censo[i].cidadaos = (Pessoa*) realloc(aux[i].cidadaos, (censo[i].capacidade+1) * sizeof(Pessoa));
                if(censo[i].cidadaos == NULL){
                    printf("Problema de alocacao!\n");
                    for(i=0; i<tam; i++){
                        free(aux[i].cidadaos);
                    }
                    free(aux);
                    exit(1);
                }
                strcpy(censo[i].cidadaos[censo[i].capacidade].nome, nomeADD);
                strcpy(censo[i].cidadaos[censo[i].capacidade].raca, racaADD);
                censo[i].cidadaos[censo[i].capacidade].idade = idadeADD;
                censo[i].cidadaos[censo[i].capacidade].salario = salarioADD;
                strcpy(censo[i].cidadaos[censo[i].capacidade].CPF, cpfADD);
                censo[i].capacidade++;
                printf("Dados adicionados com sucesso!\n");
            }
        }
    }

    if(tag_acheiCidade == 0){
        printf("Cidade nao encontrada.\n");
    }
}

void Remover(Cidade* censo, int tam){
    int cod = 0;
    char cpfRemove[12];
    int i=0, j=0;
    int tag_acheiCidade=0, tag_acheiCPF;
    Cidade *auxPont;
    Pessoa auxTroca;
    printf("Digite o codigo da cidade: \n");
    scanf("%d", &cod);
    printf("Digite o CPF do cidadao: \n");
    scanf(" %s", cpfRemove);
    for(i=0; i<tam; i++){
        if(cod == censo[i].codigo){
            tag_acheiCidade = 1;
            for(j=0; j<censo[i].capacidade; j++){
                if(strcmp(cpfRemove, censo[i].cidadaos[j].CPF)==0 && censo[i].capacidade>1){ 
                    //caso acha o cpf, troca-o com o ultimo da lista,  diminui a capacidade e realoca
                    //OBS: se a capacidade for menor ou igual a 1 nao ha removao devido a problemas de realocacao
                    tag_acheiCPF = 1;
                    auxTroca = censo[i].cidadaos[j];
                    censo[i].cidadaos[j] = censo[i].cidadaos[censo[i].capacidade-1];
                    censo[i].cidadaos[censo[i].capacidade-1] = auxTroca;
                    censo[i].capacidade--;
                    auxPont = censo;
                    censo[i].cidadaos = (Pessoa*) realloc(auxPont[i].cidadaos, (censo[i].capacidade) * sizeof(Pessoa));
                    if(censo[i].cidadaos==NULL){
                        printf("Problema de alocacao!\n");
                        for(i=0; i<tam; i++){
                            free(auxPont[i].cidadaos);
                        }
                        free(auxPont);
                    }
                    printf("Pessoa removida com sucesso!\n");
                }
            }
        }
    }
    if(tag_acheiCidade == 0){
        printf("Cidade nao encotrada.\n");
    }
    else if(tag_acheiCidade == 1 && tag_acheiCPF ==0){
        printf("CPF nao encontrado ou remocao impossibilitada.\n");
    }
}

void Procura(Cidade* censo, int tam){
    int cod=0;
    char cpf[12];
    int i=0, j=0;
    int tag_acheiCidade=0, tag_acheiCPF=0;
    printf("Digite o codigo da cidade: \n");
    scanf("%d", &cod);
    printf("Digite o CPF do cidadao: \n");
    scanf(" %s", cpf);
    for(i=0; i<tam; i++){
        if(cod == censo[i].codigo){
            tag_acheiCidade = 1;
            for(j=0; j<censo[i].capacidade; j++){
                if(strcmp(cpf, censo[i].cidadaos[j].CPF)==0){ 
                    tag_acheiCPF = 1;
                    printf("DADOS: \n");
                    printf("\t.NOME: %s\n", censo[i].cidadaos[j].nome);
                    printf("\t.RACA: %s\n", censo[i].cidadaos[j].raca);
                    printf("\t.IDADE: %d\n", censo[i].cidadaos[j].idade);
                    printf("\t.SALARIO: %.2f\n", censo[i].cidadaos[j].salario);
                    printf("\t.CPF: %s\n", censo[i].cidadaos[j].CPF);
                }
            }
        }
    }
    if(tag_acheiCidade==0){
        printf("Cidade nao encontrada.\n");
    }
    else if(tag_acheiCidade==1 && tag_acheiCPF==0){
        printf("CPF nao encontrado.\n");
    }

}

void ViewTable(Cidade* censo, int tam){
    int i=0, j=0;
    for(i=0; i<tam; i++){
        printf("%d. [%d] %s:\n", i+1, censo[i].codigo, censo[i].nome); 
        for(j=0; j<censo[i].capacidade; j++){
            printf("\t%d. %s\n", j+1, censo[i].cidadaos[j].CPF); //Printa os dados por cpf
            printf("\tDADOS: \n");
            printf("\t\t.NOME: %s\n", censo[i].cidadaos[j].nome);
            printf("\t\t.RACA: %s\n", censo[i].cidadaos[j].raca);
            printf("\t\t.IDADE: %d\n", censo[i].cidadaos[j].idade);
            printf("\t\t.SALARIO: %.2f\n", censo[i].cidadaos[j].salario);
        }
        if(censo[i].capacidade==0){
            printf("Essa cidade nao tem cidadaos registrados.\n");
        }
    }
    if(tam == 0){
        printf("Nao ha cidades registradas.\n");
    }
}

void Desaloca(Cidade* censo, int tam){
    int i=0;
    for(i=0; i<tam; i++){
        free(censo[i].cidadaos);
    }
    free(censo);
}

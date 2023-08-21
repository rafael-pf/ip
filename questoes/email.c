#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char remetente[50];
    char assunto[50];
    char mensagem[200];
} Email;

typedef struct{
    char nome[50];
    char senha[50];
    int qtdRecebidos, qtdEnviados;
    Email *recebidos;
    Email *enviados;
} Usuario;

void cadastrarUsuario(char *nome, char *senha){
    Usuario usuarioADD;
    FILE *arq;
    arq = fopen("users.bin", "a+b");
    if(arq == NULL){
        printf("Erro ao abrir arquivo!\n");
        exit(1);
    }
    strcpy(usuarioADD.nome, nome);
    strcpy(usuarioADD.senha, senha);
    usuarioADD.qtdEnviados=0;
    usuarioADD.qtdRecebidos=0;
    usuarioADD.enviados=NULL;
    usuarioADD.recebidos=NULL;
    fwrite(&usuarioADD, sizeof(Usuario), 1, arq);
    fclose(arq);
    printf("Cadastro realizado com sucesso!\n");
}

void enviarEmail(char *nomeRemetente){
    FILE *arq;
    Usuario procura;
    int tag_acheiUser=0;
    arq = fopen("users.bin", "r");
    if(arq == NULL){
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }
    while(!feof(arq) && tag_acheiUser == 0){
        fread(&procura, sizeof(Usuario), 1, arq);
        if(strcmp(procura.nome, nomeRemetente)==0){
            tag_acheiUser=1;
        }
    }
    if(tag_acheiUser==1){
        
    }
    else{
        printf("Usuario nao encontrado!\n");
    }
}

void verRecebidos(Usuario usuario){

}

void verEnviados(Usuario usuario){

}

void login(char *nome, char *senha){
    FILE *arq;
    Usuario procura;
    int tag_acheiUser=0;
    int tag_acheiPass=0;
    arq = fopen("users.bin", "r");
    if(arq == NULL){
        printf("Erro ao abrir arquivo!\n");
        exit(1);
    }
    while(!feof(arq)){
        fread(&procura, sizeof(Usuario), 1, arq);
        if(strcmp(procura.nome, nome)==0){
            tag_acheiUser=1;
            if(strcmp(procura.senha, senha)==0){
                tag_acheiPass=1;
                printf("Login realizado com sucesso!\n");
                break;
            }
        }
    }
    if(tag_acheiUser==0){
        printf("Usuario nao encontrado.\n");
    }
    else if(tag_acheiUser==1 && tag_acheiPass==0){
        printf("Senha incorreta.\n");
    }
    fclose(arq);

    int comando=0;
    char remetente[50];
    while(comando!=4 && tag_acheiPass == 1){
        printf("=======SEU EMAIL=======\n");
        printf("1. Enviar email\n");
        printf("2. Ver emails enviados\n");
        printf("3. Ver emails recebidos\n");
        printf("4. Voltar para o menu\n->");
        scanf("%d", &comando);
        switch (comando)
        {
        case 1:
            printf("Digite o usuario do remetente:\n");
            scanf(" %49[^\n]", remetente);
            enviarEmail(remetente);
            break;
        case 2:
            //verEnviados();
            break;
        case 3:
            //verRecebidos();
            break;
        case 4:
            printf("Voltando para o menu...\n");
            break;
        default:
            printf("Escolha invalida!\n");
            break;
        }
    }
}

int main(){
    int comando=0;
    Usuario *usuarios;
    int qtdUsuarios=0; 
    char nome[50], senha[50];
       
    do{
        printf("Qual operacao deseja realizar?\n");
        printf("1) Cadastrar usuario\n");
        printf("2) Fazer login\n");
        printf("3) Sair\n");
        scanf("%d", &comando);
        switch (comando)
        {
        case 1:
            printf("->CADASTRO: \n");
            printf("Digite o nome do usuario: \n");
            scanf(" %49[^\n]", nome);
            printf("Digite a senha: \n");
            scanf(" %49[^\n]", senha);
            cadastrarUsuario(nome, senha);
            break;
        case 2:
            printf("->LOGIN: \n");
            printf("Digite o nome do usuario: \n");
            scanf(" %49[^\n]", nome);
            printf("Digite a senha: \n");
            scanf(" %49[^\n]", senha);
            login(nome, senha);
            break;
        case 3:
            printf("Saindo...\n");
            break;
        default:
            printf("Escolha invalida!\n");
            break;
        }
    }while (comando!=3);

    return 0;
}

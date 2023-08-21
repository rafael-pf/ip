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
    Usuario *users=NULL, *aux;
    Email *auxR, *auxE;
    int qtdUsers=0;
    int tag_acheiDest=0, tag_acheiRemet=0;
    char assunto[50], mensagem[200];
    arq = fopen("users.bin", "rb");
    if(arq == NULL){
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }
    //ler o arquivo e guardar os dados em um vetor dinamico
    while(!feof(arq)){
        aux = users;
        users = (Usuario *) realloc(aux, (qtdUsers+1)*sizeof(Usuario));
        if(users == NULL){
            printf("Problema de alocacao!\n");
            free(aux);
            exit(1);
        }
        fread(&users[qtdUsers], sizeof(Usuario), 1, arq);
        qtdUsers++;
    }
    fclose(arq);
    qtdUsers--;
    users = (Usuario *) realloc(aux, (qtdUsers)*sizeof(Usuario)); //o eof estava alocando mais um espaço desnecessario
    if(users == NULL){
        printf("Problema de alocacao!\n");
        free(aux);
        exit(1);
    }
    //procurar o nome do remetente
    char destinatario[50];
    printf("Digite o nome do destinatario: \n");
    scanf(" %49[^\n]", destinatario);
    for(int i=0; i<qtdUsers && tag_acheiDest==0; i++){
        if(strcmp(users[i].nome, destinatario)==0){
            tag_acheiDest = 1;
            printf("Digite o assunto: \n");
            scanf(" %49[^\n]", assunto);
            printf("Digite a mensagem: \n");
            scanf(" %199[^\n]", mensagem);
            auxR = users[i].recebidos;
            users[i].recebidos = (Email *) realloc(auxR, (users[i].qtdRecebidos+1)*sizeof(Email));
            if(users[i].recebidos==NULL){ printf("Problema de alocacao!\n"); free(auxR); exit(1); }
            strcpy(users[i].recebidos[users[i].qtdRecebidos].assunto, assunto);
            strcpy(users[i].recebidos[users[i].qtdRecebidos].mensagem, mensagem);
            strcpy(users[i].recebidos[users[i].qtdRecebidos].remetente, nomeRemetente);
            users[i].qtdRecebidos++;
            for(int j=0; j<qtdUsers && tag_acheiRemet==0; j++){
                if(strcmp(users[j].nome, nomeRemetente)==0){
                    tag_acheiRemet=1;
                    auxE = users[j].enviados;
                    users[j].enviados = (Email *) realloc(auxE, (users[j].qtdEnviados+1)*sizeof(Email));
                    if(users[j].enviados==NULL){ printf("Problema de alocacao!\n"); free(auxE); exit(1); }
                    strcpy(users[j].enviados[users[j].qtdEnviados].assunto, assunto);
                    strcpy(users[j].enviados[users[j].qtdEnviados].mensagem, mensagem);
                    strcpy(users[j].enviados[users[j].qtdEnviados].remetente, users[i].nome);
                    users[j].qtdEnviados++;
                }
            }
        }
    }

    FILE *file;
    file = fopen("users.bin", "wb");
    if(file == NULL){
        printf("Erro ao abrir arquivo!\n");
        free(users);
        exit(1);
    }
    for(int i=0; i<qtdUsers; i++){
        fwrite(&users[i], sizeof(Usuario), 1, file);
    }
    fclose(file);
    if(tag_acheiDest==1){
        printf("Mensagem enviada com sucesso!\n");
    }
    else{
        printf("Usuario nao encontrado!\n");
    }
}

void verRecebidos(Usuario usuario){
    FILE *arq;
    Usuario procura;
    arq = fopen("users.bin", "rb");
    if(arq == NULL){
        printf("Problema ao abrir arquivo!\n");
        exit(1);
    }
    while(!feof(arq)){
        fread(&procura, sizeof(Usuario), 1, arq);
        if(strcmp(procura.nome, usuario.nome)==0){
            if(procura.qtdRecebidos==0){
                printf("Voce nao possui emails recebidos.\n");
                break;
            }
            printf("Recebidos de %s:\n", procura.nome);
            for(int i=0; i<procura.qtdRecebidos; i++){
                printf("\n\tRemetente: %s\n", procura.recebidos[i].remetente);
                printf("\tAssunto: %s\n", procura.recebidos[i].assunto);
                printf("\tMensagem: %s\n\n", procura.recebidos[i].mensagem);
            }
        }
    }
    fclose(arq);
}

void verEnviados(Usuario usuario){
    FILE *arq;
    Usuario procura;
    arq = fopen("users.bin", "rb");
    if(arq == NULL){
        printf("Problema ao abrir arquivo!\n");
        exit(1);
    }
    while(!feof(arq)){
        fread(&procura, sizeof(Usuario), 1, arq);
        if(strcmp(procura.nome, usuario.nome)==0){
            if(procura.qtdEnviados==0){
                printf("Voce nao possui emails enviados.\n");
                break;
            }
            printf("Enviados de %s:\n", procura.nome);
            for(int i=0; i<procura.qtdEnviados; i++){
                printf("\n\tDestinatario: %s\n", procura.enviados[i].remetente);
                printf("\tAssunto: %s\n", procura.enviados[i].assunto);
                printf("\tMensagem: %s\n\n", procura.enviados[i].mensagem);
            }
        }
    }
    fclose(arq);
}

void *login(char *nome, char *senha){
    FILE *arq;
    Usuario procura;
    int tag_acheiUser=0;
    int tag_acheiPass=0;
    arq = fopen("users.bin", "r");
    if(arq == NULL){
        printf("Erro ao abrir arquivo!\n");
        exit(1);
    }
    while(!feof(arq) && tag_acheiPass == 0){
        fread(&procura, sizeof(Usuario), 1, arq);
        if(strcmp(procura.nome, nome)==0){
            tag_acheiUser=1;
            if(strcmp(procura.senha, senha)==0){
                tag_acheiPass=1;
                printf("Login realizado com sucesso!\n");
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
            enviarEmail(procura.nome);
            break;
        case 2:
            verEnviados(procura);
            break;
        case 3:
            verRecebidos(procura);
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
    Usuario *usuarios=NULL;
    int qtdUsuarios=0; 
    char nome[50], senha[50];
       
    do{
        printf("Qual operacao deseja realizar?\n");
        printf("1) Cadastrar usuario\n");
        printf("2) Fazer login\n");
        printf("3) Sair\n.");
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

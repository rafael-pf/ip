#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
    char nome[30];
    int ataque;
    int defesa;
} Pokemon;

typedef struct{
    char nome[30];
    Pokemon *pokebola;
    int nPokemons, pontuacao;
} Treinador;

Treinador *addTreinador(Treinador *treinadores, int *qtdCompetidores){
    Treinador *aux;
    aux = treinadores;
    treinadores = (Treinador*) realloc(aux, (*qtdCompetidores+1)*sizeof(Treinador));
    if(treinadores == NULL){
        printf("Problema de alocacao!\n");
        free(treinadores);
        exit(1);
    }
    printf("Digite o nome do treinador: \n");
    scanf(" %s", treinadores[*qtdCompetidores].nome);
    (*qtdCompetidores)++;
    treinadores[*qtdCompetidores].nPokemons=0;
    treinadores[*qtdCompetidores].pontuacao=0;
    printf("Treinador adicionado com sucesso!\n");
    return treinadores;
}

Treinador *addPokemon(Treinador *treinadores, char *nomeTreinador, Pokemon pokemon, int qtdCompetidores){
    int i=0;
    Pokemon *aux;
    for(i=0; i<qtdCompetidores; i++){
        if(strcmp(nomeTreinador, treinadores[i].nome)==0){
            aux = treinadores[i].pokebola;
            treinadores[i].pokebola = (Pokemon*) realloc(aux, (treinadores[i].nPokemons+1)*sizeof(Pokemon));
            if(treinadores[i].pokebola == NULL){
                printf("Problema de alocacao!\n");
                for(i=0; i<qtdCompetidores; i++){
                    free(treinadores[i].pokebola);
                }
                free(treinadores);
                exit(1);
            }
            treinadores[i].pokebola[treinadores[i].nPokemons] = pokemon;
            treinadores[i].nPokemons++;
        }
    }
    printf("Pokemon Adicionado com sucesso!\n");
    return treinadores;
}

Treinador *removeTreinador(Treinador *treinadores, int *qtdCompetidores, int indexTreinador){

}

char *batalha(Treinador **treinadores, char *nomeCompetidor1, char *nomeCompetidor2, int indexPokemon1, int indexPokemon2, int *qtdCompetidores){
    int iCompet1, vantCompet1;
    int iCompet2, vantCompet2;
    int i=0;
    for(i=0; i<*qtdCompetidores; i++){
        if(strcmp((*treinadores)[i].nome, nomeCompetidor1)==0){
            iCompet1 = i;
        }
        else if(strcmp((*treinadores)[i].nome, nomeCompetidor1)==0){
            iCompet2 = i;
        }
    }

    vantCompet1 = (*treinadores)[iCompet1].pokebola[indexPokemon1].ataque - (*treinadores)[iCompet2].pokebola[indexPokemon2].defesa;
    vantCompet2 = (*treinadores)[iCompet2].pokebola[indexPokemon2].ataque - (*treinadores)[iCompet1].pokebola[indexPokemon1].defesa;
    if(vantCompet1 > vantCompet2){
        (*treinadores)[iCompet1].pontuacao++;
        (*treinadores)[iCompet2].pontuacao--;
        if((*treinadores)[iCompet2].pontuacao==-5){
            (*treinadores) = removeTreinador(*treinadores, &qtdCompetidores, iCompet2);
        }
        return (*treinadores)[iCompet1].nome;
    }
    else if(vantCompet2 > vantCompet1){
        (*treinadores)[iCompet2].pontuacao++;
        (*treinadores)[iCompet1].pontuacao--;
        if((*treinadores)[iCompet1].pontuacao==-5){
            (*treinadores) = removeTreinador(*treinadores, &qtdCompetidores, iCompet1);
        }
        return (*treinadores)[iCompet2].nome;
    }
}

int main(){
    int comando;
    Treinador *treinadores=NULL;
    int qtdTreinadores=0;
    Pokemon pokemon;
    char nomeAdd[30];
    char compet1[30], compet2[30];
    int indPoke1, indPoke2;

    printf("Bem vindo!\n");

    do{

        printf("Qual operacao deseja realizar?\n");
        printf("1)Adicionar competidor;\n");
        printf("2)Adicionar pokemon;\n");
        printf("3)Batalhar;\n");
        printf("4)Sair do programa;\n");
        scanf("%d", &comando);
        printf("\n");
        switch (comando)
        {
        case 1:
            treinadores = addTreinador(treinadores, &qtdTreinadores);
            break;
        case 2:
            printf("Digite o nome do treinador: \n");
            scanf(" %s", nomeAdd);
            printf("Digite o nome do pokemon: \n");
            scanf(" %s", pokemon.nome);
            printf("Digite o ataque do pokemon: \n");
            scanf("%d", &pokemon.ataque);
            printf("Digite a defesa do pokemon: \n");
            scanf("%d", &pokemon.defesa);
            treinadores = addPokemon(treinadores, nomeAdd, pokemon, qtdTreinadores);
            break;
        case 3:
            printf("Digite o nome do comepetidor 1\n");
            scanf(" %s", compet1);
            printf("Digite o nome do competidor 2\n");
            scanf(" %s", compet2);
            printf("Digite o indice do pokemon de %s", compet1);
            scanf("%d", &indPoke1);
            printf("Digite o indice do pokemon de %s", compet2);
            scanf("%d", &indPoke2);
            printf("Vencedor: %s", batalha(&treinadores, compet1, compet2, indPoke1, indPoke2, &qtdTreinadores));
            break;
        case 4:
            printf("Saindo...");
            break;
        default:
            printf("Comando invalido!\n");
            break;
        }
        printf("\n");
    }while(comando!=4);

    return 0;
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int main(){
    srand(time(NULL));
    
    //int c = 
    //int k = rand() % 26 + 65; //SORTEAR LETRA PARA PREENCHER

    int N=0, i=0, j=0, qtdPalavras=0;
    scanf("%d", &N);
    char palavras[50][21];
    for(i=0; i<50 && palavras[i-1][0]!='.'; i++){  //escanear até o ponto
        scanf(" %20[^\n]", palavras[i]);
        qtdPalavras++;
    }

    /*for(i=0; i<qtdPalavras; i++){
        printf("%s\n", palavras[i]);
    } */

    qtdPalavras=qtdPalavras-1; //tira-se o ponto da contagem de palavras

    int DIRECAO[i]; //vetor com as direcoes
    int tamanhos[qtdPalavras];  //vetores com os tamanhos da palavras
    int LINHA[qtdPalavras], COLUNA[qtdPalavras];  //vetores com as coordenadas sorteadas de cada palavra

    for(i=0; i<qtdPalavras; i++){
        tamanhos[i]=strlen(palavras[i]); 
    }

    /*for(i=0; i<qtdPalavras; i++){
        printf("palavra: %s, tamanho: %d", palavras[i], tamanhos[i]);
        printf("\n");
    }*/
    

    for(i=0; i<qtdPalavras; i++){
        LINHA[i] = rand() % (N-tamanhos[i]);
        COLUNA[i] = rand() % (N-tamanhos[i]);
        DIRECAO[i] = rand() % 8; //0=N, 1=NE, 2=L, 3=SE, 4=S, 5=SO, 6=0, 7=NO
    }

    

    char cacapalavras[N][N]; // agora vamos fazer o cacapalavras
    

    for(i=0; i<N; i++){
        for(j=0; j<N; j++){
            cacapalavras[i][j] = rand() % 26 + 65; //aleatorizar todas as letras da matriz
        }
    }

    /*char contadores[N][N]; //contar quantas vezes cada char da matriz foi alterado
    for(i=0; i<N; i++){
        for(j=0; j<N; j++){
            contadores[N][N]='0'; //minha ideia e deixar a mtriz toda zerada, exceto nas posicoes em que as letras foram alteradas
        } // infelizmente nao vai dar tempo de ajeitar :(
    } */

    for(i=0; i<qtdPalavras; i++){  // colocar as palavras na matriz 
        switch (DIRECAO[i])
        {
        case 0: //NORTE
            if(LINHA[i]>=strlen(palavras[i])){  //restricao
                for(int k=0; k<strlen(palavras[i]); k++){
                    cacapalavras[LINHA[i]-k][COLUNA[i]] = palavras[i][k];
                    //contadores[LINHA[i]-k][COLUNA[i]] = palavras[i][k];
                }
            }
            break;
        case 1: //NORDESTE
            if(LINHA[i]>=strlen(palavras[i]) && COLUNA[i]<=  N - strlen(palavras[i])){ //restricao
                for(int k=0; k<strlen(palavras[i]); k++){
                    cacapalavras[LINHA[i]-k][COLUNA[i]+k] = palavras[i][k];
                    //contadores[LINHA[i]-k][COLUNA[i]+k] = palavras[i][k];
                }
            }
            break;
        case 2: //LESTE
            if(COLUNA[i]<= N - strlen(palavras[i])){ //restricao
                for(int k=0; k<strlen(palavras[i]); k++){
                    cacapalavras[LINHA[i]][COLUNA[i]+k] = palavras[i][k];
                    //contadores[LINHA[i]][COLUNA[i]+k] = palavras[i][k];
                }
            }
            break;
        case 3: //SUDESTE
            if(LINHA[i]<= N - strlen(palavras[i]) && COLUNA[i]<= N - strlen(palavras[i])){ //restricao
                for(int k=0; k<strlen(palavras[i]); k++){
                    cacapalavras[LINHA[i]+k][COLUNA[i]+k] = palavras[i][k];
                    //contadores[LINHA[i]+k][COLUNA[i]+k] = palavras[i][k];
                }
            }
            break;
        case 4: //SUL
            if(LINHA[i]<= N - strlen(palavras[i])){ //restricao
                for(int k=0; k<strlen(palavras[i]); k++){
                    cacapalavras[LINHA[i]+k][COLUNA[i]] = palavras[i][k];
                    //contadores[LINHA[i]+k][COLUNA[i]] = palavras[i][k];
                }
            }
            break;
        case 5: //SUDOESTE
            if(LINHA[i]<= N - strlen(palavras[i]) && COLUNA[i]>=strlen(palavras[i])){ //restricao
                for(int k=0; k<strlen(palavras[i]); k++){
                    cacapalavras[LINHA[i]+k][COLUNA[i]-k] = palavras[i][k];
                    //contadores[LINHA[i]+k][COLUNA[i]-k] = palavras[i][k];
                }
            }
            break;
        case 6: //OESTE
            if(COLUNA[i]>=strlen(palavras[i])){ //restricao
                for(int k=0; k<strlen(palavras[i]); k++){
                    cacapalavras[LINHA[i]][COLUNA[i]-k] = palavras[i][k];
                    //contadores[LINHA[i]][COLUNA[i]-k] = palavras[i][k];
                }
            }
            break;
        case 7: //NOROESTE
            if(LINHA[i]>=strlen(palavras[i]) && COLUNA[i]>=strlen(palavras[i])){ //restricao
                for(int k=0; k<strlen(palavras[i]); k++){
                    cacapalavras[LINHA[i]-k][COLUNA[i]-k] = palavras[i][k];
                    //contadores[LINHA[i]-k][COLUNA[i]-k] = palavras[i][k];
                }
            }
            break;
        }
    }

    for(i=0; i<N; i++){
        for(j=0; j<N; j++){
        printf("%c ", cacapalavras[i][j]);
        }
        printf("\n");
    } 

    //É ISSO AI, DA DANDO TUDO CERTO, EXCETO QUANDO HA INTERSECAO DE PALAVRAS
    //POR FAVOR TENHA PIEDADE

    /* for(i=0; i<qtdPalavras; i++){
        printf("palavra: %s, linha sorteada: %d, coluna sorteada: %d, direcao: %d", palavras[i], LINHA[i]+1, COLUNA[i]+1, DIRECAO[i]);
        printf("\n");
    } */



    return 0;
}

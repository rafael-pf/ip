#include <stdio.h>
#include <string.h>

int main(){
    char text1[5050], text2[5050], aux[5050], matriz1[50][100]={}, matriz2[50][100]={};
    int i=0, j=0, k=0, pLetra=0, pPlagiadas=0;
    float qtdP1;
    scanf("%[^\n]%*c%[^\n]%*c", text1, text2);

    for(i=0; text1[i]!='\n';i++){   //bloco para jogar cada palavra para uma linha diferente de uma matriz
        if(text1[i]!=' '){
            matriz1[j][k]=text1[i];  
            k++;
        }
        else{
            j++;
            k=0;
            qtdP1++;
        }
    }
    //comparar se existem linhas iguais (palavras repetidas)
    
    for(i=0; i<qtdP1; i++){
        for(j=0; i+j<qtdP1; j++){
            if(strcmp(matriz1[i], matriz1[i+j])==0 && i!=i+j)
                for(k=0; k<strlen(matriz1[i+j]); k++)
                    matriz1[i+j][k]='\0';
        }
    }

    //aplica-se o mesmo procedimento para o outro texto
    k=0;
    i=0;
    j=0;
    float qtdP2=1;


    for(i=0; text2[i]!='\n';i++){   //bloco para jogar cada palavra para uma linha diferente de uma matriz
        if(text2[i]!=' '){
            matriz2[j][k]=text2[i];  
            k++;
        }
        else{
            j++;
            k=0;
            qtdP2++;
        }
    }
    //comparar se existem linhas iguais (palavras repetidas)
    
    for(i=0; i<qtdP2; i++){
        for(j=0; i+j<qtdP2; j++){
            if(strcmp(matriz2[i], matriz2[i+j])==0 && i!=i+j)
                for(k=0; k<strlen(matriz2[i+j]); k++)
                    matriz2[i+j][k]='\0';
        }
    }
    
    //bloco para contar as linhas iguais entre as duas matrizes
    for(i=0; i<qtdP1; i++){
        for(j=0; i+j<qtdP2; j++){
            if(strcmp(matriz1[i], matriz2[i+j])==0 && matriz1[i][0]!='\0'){
                pPlagiadas++;
            }
        }
    }

    float indice = pPlagiadas/(qtdP1+qtdP2) *100;

    printf("%.1f", indice);
    return 0;
}

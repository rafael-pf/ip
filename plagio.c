#include <stdio.h>
#include <string.h>

int main (){
    char text1[5050]={}, text2[5050]={}, matriz1[50][100]={}, matriz2[50][100]={};
    int i = 0, j = 0, k = 0, qtdP1 = 1, qtdP2 = 1, pLetra = 0, pPlagiadas = 0;
    scanf(" %5049[^\n]%*c", text1);
    
    for(i=0; i<strlen(text1); i++){
        if(text1[i]>='a' && text1[i] <='z'){
            text1[i]-=32;
        }
    }
    
    for (i=0; i<strlen(text1); i++){		//bloco para jogar cada palavra para uma linha diferente de uma matriz
        if(text1[i] == ' '){
            j++;
            k = 0;
            qtdP1++;
        }
        else if(text1[i] != ' '){
            matriz1[j][k] = text1[i];
            k++;
        }
    }
    
    for(i=0; i<qtdP1; i++){
        for(j=0; i+j<qtdP1; j++){
            if(strcmp(matriz1[i], matriz1[i+j])==0 && i!=i+j){
                for(k=0; k<strlen(matriz1[i+j]); k++){
                    matriz1[i+j][k]='\0';
                }
            }
        }
    }
    
    /*for(i=0; i<qtdP1; i++){
        printf("%s\n", matriz1[i]);
    } */
    
    /////////////////BLOCO PARA O TEXTO 2/////////////////////
    
    scanf(" %5049[^\n]%*c", text2);
    k=0;
    i=0;
    j=0;
    
    for(i=0; i<strlen(text2); i++){
        if(text2[i]>='a' && text2[i] <='z'){
            text2[i]-=32;
        }
    }
    
    for (i = 0; i<strlen(text2); i++){		//bloco para jogar cada palavra para uma linha diferente de uma matriz
        if(text2[i] == ' '){
            j++;
            k = 0;
            qtdP2++;
        }
        else if(text2[i] != ' '){
            matriz2[j][k] = text2[i];
            k++;
        }
    }
    
    for(i=0; i<qtdP2; i++){
        for(j=0; i+j<qtdP2; j++){
            if(strcmp(matriz2[i], matriz2[i+j])==0 && i!=i+j){
                for(k=0; k<strlen(matriz2[i+j]); k++){
                    matriz2[i+j][k]='\0';
                }
            }
        }
    }
    
    /* for(i=0; i<qtdP2; i++){
        printf("%s\n", matriz2[i]);
    } */
    
    for(i=0; i<qtdP1; i++){
        for(j=0; j<qtdP2; j++){
            if(strcmp(matriz1[i], matriz2[j])==0 && matriz1[i][0]!='\0'){
                pPlagiadas++;
            }
        }
    }
    
    float q1=qtdP1;
    float q2=qtdP2;
    
    //printf("\n%d\n", pPlagiadas);
    //printf("%d\n", qtdP1);
    //printf("%d\n", qtdP2);
    printf("%.1f", (pPlagiadas/(q1+q2))*100);
    
    return 0;
}
    

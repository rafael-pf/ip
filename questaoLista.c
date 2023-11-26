#include <stdio.h>
#include <string.h>

typedef struct{
    char nome[50];
    int pts;
    int vit;
    int e;
    int der;
    int sg;
    int gp;
    int gc;
}Time;

int main(){
    //intuito do programa: ler jogos de 1 rodada e gerar uma tabela com base neles. Criterios de desempate: Pts->Vit->SG->GP->Ordem alfabetica

    int qtd_partidas, i, j, cnt=0;

    //qtd de jogos a serem lidos
    scanf("%d", &qtd_partidas);

    int qtd_times=2*qtd_partidas;
    Time times[qtd_times];

    //ler dados dos jogos
    //OBS: nao havera repetiçao de times
    for(i=0; i<qtd_partidas; i++){
        scanf(" %49[^ 0-9] %d x %d %49[^\n]", times[cnt].nome, &times[cnt].gp, &times[cnt+1].gp, times[cnt+1].nome);
        times[cnt].gc = times[cnt+1].gp;
        times[cnt+1].gc = times[cnt].gp;
        times[cnt].sg = times[cnt].gp - times[cnt].gc;
        times[cnt+1].sg = times[cnt+1].gp - times[cnt+1].gc;
        if(times[cnt].gp>times[cnt+1].gp){
            times[cnt].vit=1;
            times[cnt].e=0;
            times[cnt].der=0;
            times[cnt].pts=3;
            times[cnt+1].vit=0;
            times[cnt+1].e=0;
            times[cnt+1].der=1;
            times[cnt+1].pts=0;
        }
        else if(times[cnt].gp<times[cnt+1].gp){
            times[cnt].vit=0;
            times[cnt].e=0;
            times[cnt].der=1;
            times[cnt].pts=0;
            times[cnt+1].vit=1;
            times[cnt+1].e=0;
            times[cnt+1].der=0;
            times[cnt+1].pts=3;
        }
        else{
            times[cnt].vit=0;
            times[cnt].e=1;
            times[cnt].der=0;
            times[cnt].pts=1;
            times[cnt+1].vit=0;
            times[cnt+1].e=1;
            times[cnt+1].der=0;
            times[cnt+1].pts=1;
        }
        cnt+=2;
    }

    Time aux;
    for(i=0; i<qtd_times; i++){
        for(j=i+1; j<qtd_times; j++){
            if(times[i].pts<times[j].pts){
                aux = times[i];
                times[i] = times[j];
                times[j] = aux;
            }
            else if(times[i].pts==times[j].pts){
                if(times[i].vit<times[j].vit){
                    aux = times[i];
                    times[i] = times[j];
                    times[j] = aux;
                }
                else if(times[i].vit==times[j].vit){
                    if(times[i].sg<times[j].sg){
                        aux = times[i];
                        times[i] = times[j];
                        times[j] = aux;
                    }
                    else if(times[i].sg==times[j].sg){
                        if(times[i].gp<times[j].gp){
                            aux = times[i];
                            times[i] = times[j];
                            times[j] = aux;
                        }
                        else if(times[i].gp==times[j].gp){
                            if(strcmp(times[i].nome, times[j].nome)>0){
                                aux = times[i];
                                times[i] = times[j];
                                times[j] = aux;
                            }
                        }
                    }
                }
            }
        }
    }


    for(i=0; i<qtd_times; i++){
        printf("TIME: %s \n\tPTS: %d \n\tVIT: %d \n\tE: %d \n\tDER: %d \n\tGP: %d \n\tGC: %d \n\tSG: %d\n", times[i].nome, times[i].pts, times[i].vit, times[i].e, times[i].der, times[i].gp, times[i].gc, times[i].sg);
    }

    //entrada teste:
    /*10
    America-MG 8 x 0 Flamengo
    Fortaleza 1 x 1 Palmeiras
    Botafogo 0 x 2 Santos
    Corinthians 1 x 5 Bahia
    Athletico-PR 1 x 1 Vasco
    Fluminense 2 x 1 Coritiba
    Sao-Paulo 3 x 0 Cuiaba
    Atletico-MG 2 x 0 Gremio
    Bragantino 1 x 0 Internacional
    Cruzeiro 5 x 0 Goias*/


    return 0;
}

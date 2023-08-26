#define PI 3.14
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
#include "extApi.h"
}

void lerArquivo(int handler, int clientID);
void botao_1(int handler, int clientID);
void botao_2(int handler, int clientID);
void botao_3(int handler, int clientID);
void botao_4(int handler, int clientID);
void botao_5(int handler, int clientID);
void botao_6(int handler, int clientID);
void botao_7(int handler, int clientID);
void botao_8(int handler, int clientID);
void botao_9(int handler, int clientID);
void botao_0(int handler, int clientID);
void botao_branco(int handler, int clientID);
void botao_corrige(int handler, int clientID);
void botao_confirma(int handler, int clientID);
void reset1(int handler, int clientID);
void reset2(int handler, int clientID);
void reset3(int handler, int clientID);
void reset(int handler, int clientID);

int main(int argc, char* argv[])
{
    //variavei para handler das juntas
    int handler = 0;

    //conecta com o coppelia
    int clientID = simxStart((simxChar*)"127.0.0.1", 19999, true, true, 2000, 5);

    extApi_sleepMs(500);

    //verifica conexao com simulador
    if (clientID == -1) {
        printf("Erro conectando ao Coppelia!\n");
        return 0;
    }
    else {
        printf("Conectado ao Coppelia!\n");
    }


    lerArquivo(handler, clientID);


    // Fecha a conexao 
    simxFinish(clientID);

    return(0);
}

void lerArquivo(int handler, int clientID){
    FILE* arq;
    arq = fopen("votos.txt", "rt");
    if (arq == NULL) {
        printf("Erro ao abrir arquivo!\n");
        exit(1);
    }
    char voto[11];
    while (fscanf(arq, " %10[^;]; ", voto) != EOF) {
        for (int i = 0; i < strlen(voto); i++) {
            if (voto[i] == '0') {
                //funcao voto 0
                botao_0(handler, clientID);
                extApi_sleepMs(6000);
                reset(handler, clientID);
                extApi_sleepMs(6000);
            }
            else if (voto[i] == '1') {
                //funcao voto 1
                botao_1(handler, clientID);
                extApi_sleepMs(8000);
                reset(handler, clientID);
                extApi_sleepMs(6000);
            }
            else if (voto[i] == '2') {
                //funcao voto 2
                botao_2(handler, clientID);
                extApi_sleepMs(6000);
                reset(handler, clientID);
                extApi_sleepMs(6000);
            }
            else if (voto[i] == '3') {
                //funcao voto 3
                botao_3(handler, clientID);
                extApi_sleepMs(6000);
                reset(handler, clientID);
                extApi_sleepMs(6000);
            }
            else if (voto[i] == '4') {
                //funcao voto 4
                botao_4(handler, clientID);
                extApi_sleepMs(6000);
                reset(handler, clientID);
                extApi_sleepMs(6000);
            }
            else if (voto[i] == '5') {
                //funcao voto 5
                botao_5(handler, clientID);
                extApi_sleepMs(6000);
                reset(handler, clientID);
                extApi_sleepMs(6000);
            }
            else if (voto[i] == '6') {
                //funcao voto 6
                botao_6(handler, clientID);
                extApi_sleepMs(6000);
                reset(handler, clientID);
                extApi_sleepMs(6000);
            }
            else if (voto[i] == '7') {
                //funcao voto 7
                botao_7(handler, clientID);
                extApi_sleepMs(6000);
                reset(handler, clientID);
                extApi_sleepMs(6000);
            }
            else if (voto[i] == '8') {
                //funcao voto 8
                botao_8(handler, clientID);
                extApi_sleepMs(6000);
                reset(handler, clientID);
                extApi_sleepMs(6000);
            }
            else if (voto[i] == '9') {
                //funcao voto 9
                botao_9(handler, clientID);
                extApi_sleepMs(6000);
                reset(handler, clientID);
                extApi_sleepMs(6000);
            }
            else if (voto[i] == 'C') {
                //funcao voto corrige
                botao_corrige(handler, clientID);
                extApi_sleepMs(5000);
                reset(handler, clientID);
                extApi_sleepMs(5000);

            }
            else if (voto[i] == 'B') {
                //funcao voto branco
                botao_branco(handler, clientID);
                extApi_sleepMs(5000);
                reset(handler, clientID);
                extApi_sleepMs(6000);
            }
        }
        //funcao "confirmar"
        botao_confirma(handler, clientID);
        extApi_sleepMs(5000);
        reset(handler, clientID);
        extApi_sleepMs(5000);
        printf("Seu voto %s, foi computado\n", voto);
    }
    fclose(arq);
}

void botao_1(int handler, int clientID) {

    simxChar handlerName[150] = "/base_link_respondable[0]";
    strcat(handlerName, "/joint_1");
    simxGetObjectHandle(clientID, handlerName, &handler, (simxInt)simx_opmode_oneshot_wait);

    simxSetJointTargetPosition(clientID, handler, (simxFloat)-1 / 16 * PI, (simxInt)simx_opmode_oneshot_wait);
    extApi_sleepMs(1000);

    strcat(handlerName, "/joint_2");
    simxGetObjectHandle(clientID, handlerName, &handler, (simxInt)simx_opmode_oneshot_wait);

    simxSetJointTargetPosition(clientID, handler, (simxFloat)-0.264 * PI, (simxInt)simx_opmode_oneshot_wait);
    extApi_sleepMs(1000);

    strcat(handlerName, "/joint_3");
    simxGetObjectHandle(clientID, handlerName, &handler, (simxInt)simx_opmode_oneshot_wait);

    simxSetJointTargetPosition(clientID, handler, (simxFloat)0.027 * PI, (simxInt)simx_opmode_oneshot_wait);
    extApi_sleepMs(1000);


}

void botao_2(int handler, int clientID) {
    simxChar handlerName[150] = "/base_link_respondable[0]";
    strcat(handlerName, "/joint_1");
    simxGetObjectHandle(clientID, handlerName, &handler, (simxInt)simx_opmode_oneshot_wait);

    simxSetJointTargetPosition(clientID, handler, (simxFloat)-0.09 * PI, (simxInt)simx_opmode_oneshot_wait);
    extApi_sleepMs(1000);

    strcat(handlerName, "/joint_2");
    simxGetObjectHandle(clientID, handlerName, &handler, (simxInt)simx_opmode_oneshot_wait);

    simxSetJointTargetPosition(clientID, handler, (simxFloat)-0.276 * PI, (simxInt)simx_opmode_oneshot_wait);
    extApi_sleepMs(1000);

    strcat(handlerName, "/joint_3");
    simxGetObjectHandle(clientID, handlerName, &handler, (simxInt)simx_opmode_oneshot_wait);

    simxSetJointTargetPosition(clientID, handler, (simxFloat)0.043 * PI, (simxInt)simx_opmode_oneshot_wait);
    extApi_sleepMs(1000);

}

void botao_3(int handler, int clientID) {
    simxChar handlerName[150] = "/base_link_respondable[0]";
    strcat(handlerName, "/joint_1");
    simxGetObjectHandle(clientID, handlerName, &handler, (simxInt)simx_opmode_oneshot_wait);

    simxSetJointTargetPosition(clientID, handler, (simxFloat)-0.1 * PI, (simxInt)simx_opmode_oneshot_wait);
    extApi_sleepMs(1000);

    strcat(handlerName, "/joint_2");
    simxGetObjectHandle(clientID, handlerName, &handler, (simxInt)simx_opmode_oneshot_wait);

    simxSetJointTargetPosition(clientID, handler, (simxFloat)-0.282 * PI, (simxInt)simx_opmode_oneshot_wait);
    extApi_sleepMs(1000);

    strcat(handlerName, "/joint_3");
    simxGetObjectHandle(clientID, handlerName, &handler, (simxInt)simx_opmode_oneshot_wait);

    simxSetJointTargetPosition(clientID, handler, (simxFloat)0.055 * PI, (simxInt)simx_opmode_oneshot_wait);
    extApi_sleepMs(1000);

}

void botao_4(int handler, int clientID) {
    simxChar handlerName[150] = "/base_link_respondable[0]";
    strcat(handlerName, "/joint_1");
    simxGetObjectHandle(clientID, handlerName, &handler, (simxInt)simx_opmode_oneshot_wait);

    simxSetJointTargetPosition(clientID, handler, (simxFloat)-1 / 16 * PI, (simxInt)simx_opmode_oneshot_wait);
    extApi_sleepMs(1000);

    strcat(handlerName, "/joint_2");
    simxGetObjectHandle(clientID, handlerName, &handler, (simxInt)simx_opmode_oneshot_wait);

    simxSetJointTargetPosition(clientID, handler, (simxFloat)-0.26 * PI, (simxInt)simx_opmode_oneshot_wait);
    extApi_sleepMs(1000);


}

void botao_5(int handler, int clientID) {
    simxChar handlerName[150] = "/base_link_respondable[0]";

    strcat(handlerName, "/joint_1");
    simxGetObjectHandle(clientID, handlerName, &handler, (simxInt)simx_opmode_oneshot_wait);

    simxSetJointTargetPosition(clientID, handler, (simxFloat)-0.09 * PI, (simxInt)simx_opmode_oneshot_wait);
    extApi_sleepMs(1000);

    strcat(handlerName, "/joint_2");
    simxGetObjectHandle(clientID, handlerName, &handler, (simxInt)simx_opmode_oneshot_wait);

    simxSetJointTargetPosition(clientID, handler, (simxFloat)-0.27 * PI, (simxInt)simx_opmode_oneshot_wait);
    extApi_sleepMs(1000);

    strcat(handlerName, "/joint_3");
    simxGetObjectHandle(clientID, handlerName, &handler, (simxInt)simx_opmode_oneshot_wait);

    simxSetJointTargetPosition(clientID, handler, (simxFloat)0.02 * PI, (simxInt)simx_opmode_oneshot_wait);
    extApi_sleepMs(1000);



}

void botao_6(int handler, int clientID) {
    simxChar handlerName[150] = "/base_link_respondable[0]";

    strcat(handlerName, "/joint_1");
    simxGetObjectHandle(clientID, handlerName, &handler, (simxInt)simx_opmode_oneshot_wait);

    simxSetJointTargetPosition(clientID, handler, (simxFloat)-0.105 * PI, (simxInt)simx_opmode_oneshot_wait);
    extApi_sleepMs(1000);

    strcat(handlerName, "/joint_2");
    simxGetObjectHandle(clientID, handlerName, &handler, (simxInt)simx_opmode_oneshot_wait);

    simxSetJointTargetPosition(clientID, handler, (simxFloat)-0.28 * PI, (simxInt)simx_opmode_oneshot_wait);
    extApi_sleepMs(1000);

    strcat(handlerName, "/joint_3");
    simxGetObjectHandle(clientID, handlerName, &handler, (simxInt)simx_opmode_oneshot_wait);

    simxSetJointTargetPosition(clientID, handler, (simxFloat)0.035 * PI, (simxInt)simx_opmode_oneshot_wait);
    extApi_sleepMs(1000);



}

void botao_7(int handler, int clientID) {
    simxChar handlerName[150] = "/base_link_respondable[0]";

    strcat(handlerName, "/joint_1");
    simxGetObjectHandle(clientID, handlerName, &handler, (simxInt)simx_opmode_oneshot_wait);

    simxSetJointTargetPosition(clientID, handler, (simxFloat)-0.0625 * PI, (simxInt)simx_opmode_oneshot_wait);
    extApi_sleepMs(3000);

    strcat(handlerName, "/joint_2");
    simxGetObjectHandle(clientID, handlerName, &handler, (simxInt)simx_opmode_oneshot_wait);

    simxSetJointTargetPosition(clientID, handler, (simxFloat)-0.25 * PI, (simxInt)simx_opmode_oneshot_wait);
    extApi_sleepMs(3000);

    strcat(handlerName, "/joint_3");
    simxGetObjectHandle(clientID, handlerName, &handler, (simxInt)simx_opmode_oneshot_wait);

    simxSetJointTargetPosition(clientID, handler, (simxFloat)-0.02 * PI, (simxInt)simx_opmode_oneshot_wait);
    extApi_sleepMs(3000);

    simxChar handlerName2[150] = "/base_link_respondable[0]";
    strcat(handlerName2, "/joint_2");
    simxGetObjectHandle(clientID, handlerName2, &handler, (simxInt)simx_opmode_oneshot_wait);

    simxSetJointTargetPosition(clientID, handler, (simxFloat)-0.257 * PI, (simxInt)simx_opmode_oneshot_wait);
    extApi_sleepMs(1000);
}

void botao_8(int handler, int clientID) {
    simxChar handlerName[150] = "/base_link_respondable[0]";

    strcat(handlerName, "/joint_1");
    simxGetObjectHandle(clientID, handlerName, &handler, (simxInt)simx_opmode_oneshot_wait);

    simxSetJointTargetPosition(clientID, handler, (simxFloat)-0.09 * PI, (simxInt)simx_opmode_oneshot_wait);
    extApi_sleepMs(1000);

    strcat(handlerName, "/joint_2");
    simxGetObjectHandle(clientID, handlerName, &handler, (simxInt)simx_opmode_oneshot_wait);

    simxSetJointTargetPosition(clientID, handler, (simxFloat)-0.20 * PI, (simxInt)simx_opmode_oneshot_wait);
    extApi_sleepMs(4000);

    strcat(handlerName, "/joint_3");
    simxGetObjectHandle(clientID, handlerName, &handler, (simxInt)simx_opmode_oneshot_wait);

    simxSetJointTargetPosition(clientID, handler, (simxFloat)-0.006 * PI, (simxInt)simx_opmode_oneshot_wait);
    extApi_sleepMs(4000);

    simxChar handlerName2[150] = "/base_link_respondable[0]";
    strcat(handlerName2, "/joint_2");
    simxGetObjectHandle(clientID, handlerName2, &handler, (simxInt)simx_opmode_oneshot_wait);

    simxSetJointTargetPosition(clientID, handler, (simxFloat)-0.267 * PI, (simxInt)simx_opmode_oneshot_wait);
    extApi_sleepMs(1000);

}

void botao_9(int handler, int clientID) {
    simxChar handlerName[150] = "/base_link_respondable[0]";

    strcat(handlerName, "/joint_1");
    simxGetObjectHandle(clientID, handlerName, &handler, (simxInt)simx_opmode_oneshot_wait);

    simxSetJointTargetPosition(clientID, handler, (simxFloat)-0.11 * PI, (simxInt)simx_opmode_oneshot_wait);
    extApi_sleepMs(4000);

    strcat(handlerName, "/joint_2");
    simxGetObjectHandle(clientID, handlerName, &handler, (simxInt)simx_opmode_oneshot_wait);

    simxSetJointTargetPosition(clientID, handler, (simxFloat)-0.27 * PI, (simxInt)simx_opmode_oneshot_wait);
    extApi_sleepMs(4000);

    strcat(handlerName, "/joint_3");
    simxGetObjectHandle(clientID, handlerName, &handler, (simxInt)simx_opmode_oneshot_wait);

    simxSetJointTargetPosition(clientID, handler, (simxFloat)0.015 * PI, (simxInt)simx_opmode_oneshot_wait);
    extApi_sleepMs(4000);

    simxChar handlerName2[150] = "/base_link_respondable[0]";
    strcat(handlerName2, "/joint_2");
    simxGetObjectHandle(clientID, handlerName2, &handler, (simxInt)simx_opmode_oneshot_wait);

    simxSetJointTargetPosition(clientID, handler, (simxFloat)-0.28 * PI, (simxInt)simx_opmode_oneshot_wait);
    extApi_sleepMs(1000);
}

void botao_0(int handler, int clientID) {
    simxChar handlerName[150] = "/base_link_respondable[0]";

    strcat(handlerName, "/joint_1");
    simxGetObjectHandle(clientID, handlerName, &handler, (simxInt)simx_opmode_oneshot_wait);

    simxSetJointTargetPosition(clientID, handler, (simxFloat)-0.09 * PI, (simxInt)simx_opmode_oneshot_wait);
    extApi_sleepMs(1000);

    strcat(handlerName, "/joint_2");
    simxGetObjectHandle(clientID, handlerName, &handler, (simxInt)simx_opmode_oneshot_wait);

    simxSetJointTargetPosition(clientID, handler, (simxFloat)-0.18 * PI, (simxInt)simx_opmode_oneshot_wait);
    extApi_sleepMs(4000);

    strcat(handlerName, "/joint_3");
    simxGetObjectHandle(clientID, handlerName, &handler, (simxInt)simx_opmode_oneshot_wait);

    simxSetJointTargetPosition(clientID, handler, (simxFloat)-0.028 * PI, (simxInt)simx_opmode_oneshot_wait);
    extApi_sleepMs(4000);

    simxChar handlerName2[150] = "/base_link_respondable[0]";
    strcat(handlerName2, "/joint_2");
    simxGetObjectHandle(clientID, handlerName2, &handler, (simxInt)simx_opmode_oneshot_wait);

    simxSetJointTargetPosition(clientID, handler, (simxFloat)-0.267 * PI, (simxInt)simx_opmode_oneshot_wait);
    extApi_sleepMs(1000);
}

void botao_branco(int handler, int clientID) {
    simxChar handlerName[150] = "/base_link_respondable[0]";

    strcat(handlerName, "/joint_1");
    simxGetObjectHandle(clientID, handlerName, &handler, (simxInt)simx_opmode_oneshot_wait);

    simxSetJointTargetPosition(clientID, handler, (simxFloat)-0.0625 * PI, (simxInt)simx_opmode_oneshot_wait);
    extApi_sleepMs(1000);

    strcat(handlerName, "/joint_2");
    simxGetObjectHandle(clientID, handlerName, &handler, (simxInt)simx_opmode_oneshot_wait);

    simxSetJointTargetPosition(clientID, handler, (simxFloat)-0.2 * PI, (simxInt)simx_opmode_oneshot_wait);
    extApi_sleepMs(4000);

    strcat(handlerName, "/joint_3");
    simxGetObjectHandle(clientID, handlerName, &handler, (simxInt)simx_opmode_oneshot_wait);

    simxSetJointTargetPosition(clientID, handler, (simxFloat)-0.06 * PI, (simxInt)simx_opmode_oneshot_wait);
    extApi_sleepMs(5000);

    simxChar handlerName2[150] = "/base_link_respondable[0]";
    strcat(handlerName2, "/joint_2");
    simxGetObjectHandle(clientID, handlerName2, &handler, (simxInt)simx_opmode_oneshot_wait);

    simxSetJointTargetPosition(clientID, handler, (simxFloat)-0.26 * PI, (simxInt)simx_opmode_oneshot_wait);
    extApi_sleepMs(1000);

}

void botao_corrige(int handler, int clientID) {
    simxChar handlerName[150] = "/base_link_respondable[0]";

    strcat(handlerName, "/joint_1");
    simxGetObjectHandle(clientID, handlerName, &handler, (simxInt)simx_opmode_oneshot_wait);

    simxSetJointTargetPosition(clientID, handler, (simxFloat)-0.096 * PI, (simxInt)simx_opmode_oneshot_wait);
    extApi_sleepMs(1000);

    strcat(handlerName, "/joint_2");
    simxGetObjectHandle(clientID, handlerName, &handler, (simxInt)simx_opmode_oneshot_wait);

    simxSetJointTargetPosition(clientID, handler, (simxFloat)-0.25 * PI, (simxInt)simx_opmode_oneshot_wait);
    extApi_sleepMs(4000);

    strcat(handlerName, "/joint_3");
    simxGetObjectHandle(clientID, handlerName, &handler, (simxInt)simx_opmode_oneshot_wait);

    simxSetJointTargetPosition(clientID, handler, (simxFloat)-0.045 * PI, (simxInt)simx_opmode_oneshot_wait);
    extApi_sleepMs(6500);

    simxChar handlerName2[150] = "/base_link_respondable[0]";
    strcat(handlerName2, "/joint_2");
    simxGetObjectHandle(clientID, handlerName2, &handler, (simxInt)simx_opmode_oneshot_wait);

    simxSetJointTargetPosition(clientID, handler, (simxFloat)-0.27 * PI, (simxInt)simx_opmode_oneshot_wait);
    extApi_sleepMs(1000);

}

void botao_confirma(int handler, int clientID) {
    simxChar handlerName[150] = "/base_link_respondable[0]";

    strcat(handlerName, "/joint_1");
    simxGetObjectHandle(clientID, handlerName, &handler, (simxInt)simx_opmode_oneshot_wait);

    simxSetJointTargetPosition(clientID, handler, (simxFloat)-0.12 * PI, (simxInt)simx_opmode_oneshot_wait);
    extApi_sleepMs(4000);

    strcat(handlerName, "/joint_2");
    simxGetObjectHandle(clientID, handlerName, &handler, (simxInt)simx_opmode_oneshot_wait);

    simxSetJointTargetPosition(clientID, handler, (simxFloat)-0.27 * PI, (simxInt)simx_opmode_oneshot_wait);
    extApi_sleepMs(5000);

    strcat(handlerName, "/joint_3");
    simxGetObjectHandle(clientID, handlerName, &handler, (simxInt)simx_opmode_oneshot_wait);

    simxSetJointTargetPosition(clientID, handler, (simxFloat)-0.0255 * PI, (simxInt)simx_opmode_oneshot_wait);
    extApi_sleepMs(5000);

    simxChar handlerName2[150] = "/base_link_respondable[0]";
    strcat(handlerName2, "/joint_2");
    simxGetObjectHandle(clientID, handlerName2, &handler, (simxInt)simx_opmode_oneshot_wait);

    simxSetJointTargetPosition(clientID, handler, (simxFloat)-0.2815 * PI, (simxInt)simx_opmode_oneshot_wait);
    extApi_sleepMs(1000);
}

void reset1(int handler, int clientID) {
    simxChar handlerName[150] = "/base_link_respondable[0]";
    strcat(handlerName, "/joint_1");
    simxGetObjectHandle(clientID, handlerName, &handler, (simxInt)simx_opmode_oneshot_wait);

    simxSetJointTargetPosition(clientID, handler, (simxFloat)0 * PI, (simxInt)simx_opmode_oneshot_wait);
    extApi_sleepMs(1000);
}

void reset2(int handler, int clientID) {
    simxChar handlerName[150] = "/base_link_respondable[0]";

    strcat(handlerName, "/joint_2");
    simxGetObjectHandle(clientID, handlerName, &handler, (simxInt)simx_opmode_oneshot_wait);

    simxSetJointTargetPosition(clientID, handler, (simxFloat)0 * PI, (simxInt)simx_opmode_oneshot_wait);
    extApi_sleepMs(1000);

}

void reset3(int handler, int clientID) {
    simxChar handlerName[150] = "/base_link_respondable[0]";

    strcat(handlerName, "/joint_3");
    simxGetObjectHandle(clientID, handlerName, &handler, (simxInt)simx_opmode_oneshot_wait);

    simxSetJointTargetPosition(clientID, handler, (simxFloat)0 * PI, (simxInt)simx_opmode_oneshot_wait);
    extApi_sleepMs(1000);
}

void reset(int handler, int clientID) {
    reset2(handler, clientID);
    reset3(handler, clientID);
    reset1(handler, clientID);
}

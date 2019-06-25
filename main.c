#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "src/func.c"

int main(){
    int ag = 0;
    int conta = 0;
    int senha = 0;
    int op;
    while(1){
        system("cls");
        printf("Bem vindo ao Hulema\n");
        printf("1. Realizar Login\n");
        printf("2. Depositar\n");
        scanf("%d", &op);

        switch (op)
        {
        case 1:
            printf("Agencia: ");
            scanf("%d",&ag);
            printf("Conta: ");
            scanf("%d",&conta);
            printf("Senha: ");
            scanf("%d", &senha);
            system("cls");
            login(ag, conta, senha);
            break;
        case 2:
            printf("Agencia do Deposito: ");
            scanf("%d",&ag);
            printf("Conta do Deposito: ");
            scanf("%d",&conta);
            deposito(ag, conta, verConta(ag, conta));
            break;        
        default:
            printf("Operacao inexistente!");
            break;
        }
        system("sleep 03");
        system("cls");
    };
    return 0;
}
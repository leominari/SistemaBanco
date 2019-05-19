#include "func.h"

//Erro na abertura arquivo
void erroAbert(int e){
    if(e == 1)
        printf("[Erro 101]\n");
    else if(e == 2)
            printf("[Erro 102]\n");
            else if(e == 3)
                    printf("[Erro 103]\n");  
                    else if(e == 4)
                            printf("[Erro 104]\n");  
}

//veficia agencia
//1 se existir 0 se nao
boolean verAg(int ver){
    //verif
    FILE* listaAgencia = fopen("agencias/lista-agencias.txt", "r+");
    if(listaAgencia == NULL){
        erroAbert(1);
        fclose(listaAgencia);
        return 0;
    }
    //logica
    int ag=0;
    while(!feof(listaAgencia)){
        fscanf(listaAgencia, "%d", &ag);
        if(ag == ver){
            fclose(listaAgencia);
            return 1;
        }
    }
    fclose(listaAgencia);
    return 0;
}

//veficia Conta
//1 se existir 0 se nao
boolean verConta(int ag, int ver){
    //verif
    char caminho[100];
    sprintf(caminho, "agencias/%d/lista-contas.txt", ag);
    FILE* listaConta = fopen(caminho, "r+");
    if(listaConta == NULL){
        erroAbert(2);
        fclose(listaConta);
        return 0;
    }
    //logica
    int conta=0;
    while(!feof(listaConta)){
        fscanf(listaConta, "%d", &conta);
        if(conta == ver){
            fclose(listaConta);
            return 1;
        }
    }
    fclose(listaConta);
    return 0;
}

//veficia senha
//1 se correta 0 se incorreta
boolean verSenha(int ag, int conta, int ver){
    //verif
    char caminho[100];
    sprintf(caminho, "agencias/%d/%d/infos.txt", ag, conta);
    FILE* infos = fopen(caminho, "r+");
    if(infos == NULL){
        erroAbert(3);
        fclose(infos);
        return 0;
    }
    //logica
    int senha=0;
    char tipo;
        fscanf(infos, "%c%d",&tipo, &senha);
        if(senha == ver){
            fclose(infos);
            return 1;
        }
    fclose(infos);
    return 0;
}

char* pegaNome(int ag, int conta){
    //verif
    char caminho[100];
    sprintf(caminho, "agencias/%d/%d/infos.txt", ag, conta);
    FILE* infos = fopen(caminho, "r+");
    if(infos == NULL){
        erroAbert(4);
        fclose(infos);
        return NULL;
    }
    char tipo = 32;
    char* nome = malloc(50*sizeof(char));
    char nome1[15];
    char nome2[15];
    char nome3[15];
    while(!feof(infos)){
        fscanf(infos, "%s %s %s", nome1, nome2, nome3);
        if(nome1[0] == 35)
            break;
    }
    
    if(nome1[0] == 35){ //35 é a #
        if(nome3[0] == 35){
            sprintf(nome,"%s %s", (nome1+1), nome2);
            fclose(infos);
            return nome;
        }
        else{
            sprintf(nome,"%s %s %s", (nome1+1), nome2, nome3);
            fclose(infos);
            return nome;
        }
    }
    fclose(infos);
    return NULL;
}

TDia* tempo(){
    time_t mytime;
    TDia* hoje = malloc(sizeof(TDia));
    mytime = time(NULL);
    struct tm tm = *localtime(&mytime);
    printf("Data: %d%d%d\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    hoje->dia = tm.tm_mday;
    hoje->mes = tm.tm_mon + 1;
    hoje->ano = tm.tm_year + 1900;
    return hoje;
}

void extrato(){

}

void consultarSaldo(){

}

void saque(){

}

void deposito(int ag, int conta){
    char caminho[100];
    sprintf(caminho, "agencias/%d/%d/caixa.txt", ag, conta);
    FILE* infos = fopen(caminho, "r+");
    if(infos == NULL){
        erroAbert(4);
        fclose(infos);
        return ;
    }

    
}

void login(int ag, int conta, int senha){

    if(verAg(ag) && verConta(ag, conta) && verSenha(ag, conta, senha)){
        char* nome = pegaNome(ag, conta);
        if(nome == NULL){
            printf("[Falha no Sistema]\n");
            erroAbert(4);
            return;
        }

        int op = 0;
        printf("[Login Efetuado]\n\n");
        printf("Ola %s,\n", nome);
        
        do{
            printf("\nO que deseja fazer?\n");
            printf("1. Extrato\n");
            printf("2. Consultar Saldo\n");
            printf("3. Saque\n");
            printf("4. Deposito\n");
            printf("0. Sair\n");
            
            scanf("%d", &op);
            switch (op)
            {
            case 1:
                extrato();
                break;
            case 2:
                consultarSaldo();
                break;
            case 3:
                saque();
                break;
            case 4:
                deposito(ag, conta);
                break;
            case 0:
                printf("\nObrigado por utilizar nosso Banco!");
                break;
            default:
                printf("Opção errada %s tente outra!");
                break;
            }
        }while(op != 0);
    }
    else{
        printf("Falha no Login: Informacoes Erradas.\n");
    }
}
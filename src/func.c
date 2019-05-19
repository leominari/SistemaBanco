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
    hoje->dia = tm.tm_mday;
    hoje->mes = tm.tm_mon + 1;
    hoje->ano = tm.tm_year + 1900;
    return hoje;
}

double pegaSaldo(int ag, int conta){
    char valorS[30];
    double valor;
    char caminho[100];
    sprintf(caminho, "agencias/%d/%d/caixa.txt", ag, conta);
    FILE* caixa = fopen(caminho, "r+");
    if(caixa == NULL){
        erroAbert(4);
        system("sleep 02");
        fclose(caixa);
        return 0;
    }

    fscanf(caixa, "%s", valorS);
    valor = atof(valorS);
    fclose(caixa);
    return valor;
}

boolean salvaSaldo(int ag, int conta, double saldo){
    char caminho[100];
    sprintf(caminho, "agencias/%d/%d/caixa.txt", ag, conta);
    // remove(caminho);
    FILE* caixa = fopen(caminho, "w+");
    if(caixa == NULL){
        erroAbert(4);
        system("sleep 02");
        fclose(caixa);
        return 0;
    }

    fprintf(caixa, "%lf", saldo);
    fclose(caixa);
    return 1;
}


boolean gravaOperacao(int ag, int conta, int op, double valor, double saldo){
    char caminho[100];
    TDia* dta = tempo();
    sprintf(caminho, "agencias/%d/%d/operacoes.txt", ag, conta);
    FILE* operacoes = fopen(caminho, "r+");
    if(operacoes == NULL){
        FILE* operacoes = fopen(caminho, "w+");
    }
    fseek(operacoes, 0, SEEK_END);
    
    fprintf(operacoes, "\n%d %d %d %d %lf %lf", dta->dia, dta->mes, dta->ano, op, valor, saldo);
    fclose(operacoes);
}

void consultarSaldo(int ag, int conta){
    char* nome = pegaNome(ag, conta);

    printf("Nome do Titular: %s\n", nome);    
    printf("Agencia: %d\n", ag);
    printf("Conta: %d\n", conta);    
    printf("Saldo: %lf\n", pegaSaldo(ag, conta));
}

void saque(int ag, int conta){
    double valor;
    double saldo = pegaSaldo(ag, conta);
    printf("Qual valor deseja sacar?\n");
    scanf("%lf", &valor);
    if((saldo-valor) < 0){
        printf("Valor não disponivel para saque!\n");
        return;
    }
        salvaSaldo(ag, conta, (saldo-valor));
        gravaOperacao(ag, conta, 0, valor, (saldo-valor));
        printf("Saque realizado!");
}

void deposito(int ag, int conta){
    //Verifica se a conta pro deposito é valida
    if(!(verAg(ag) && verConta(ag, conta))){
        printf("Dados Invalidos!\n");
        return;
    }
    double saldo = pegaSaldo(ag, conta);
    char* nome = pegaNome(ag, conta);
    int op;
    double valorDep = 0;

    printf("Qual o valor do Deposito?\n");
    scanf("%lf", &valorDep);

    printf("Beneficiado: %s\nAg: %d\nConta: %d\nValor: %lf\n", nome, ag, conta, valorDep);
    printf("Informacoes Corretas?\n1.Sim | 2.Nao\n");
    scanf("%d", &op);

    if(op == 2){
        system("cls");
        printf("Operacao Cancelada!\n");
        system("sleep 02");
        return;
    }
saldo += valorDep;
    if(salvaSaldo(ag, conta, saldo)){
        printf("Deposito realizado.\n");
    }
    else{
        printf("Deposito não realizado.\n");
    } 

    gravaOperacao(ag, conta, 1, valorDep, saldo);
    
}

void extrato(int ag, int conta){
    TDia data;
    TDia* atual = tempo();
    char* nome = pegaNome(ag, conta);
    int op;
    char caminho[100];
    double valor, saldo;
    sprintf(caminho, "agencias/%d/%d/operacoes.txt", ag, conta);
    FILE* operacoes = fopen(caminho, "r+");
    if(operacoes == NULL){
        printf("Nenhuma operacao foi realizada ainda.");
        return;   
    }
    printf("Titular: %s Agencia: %d Conta: %d\n", nome);
    printf("_________________________________________");
    while(!feof(operacoes)){
        fscanf(operacoes, "%d %d %d %d %lf %ld",data.dia, data.mes, data.ano, op, valor, saldo);
        if(data.mes == atual->mes){
            printf("%d/%d/%d - ");
            if(op){
                printf("Deposito no valor de: R$%lf totalizando R$%lf", valor, saldo);
            }
            else{
                printf("Saque no valor de: R$%lf totalizando R$%lf", valor, saldo);
            }
        }
    }
    fclose(operacoes);
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
        int agDep;
        int contaDep;
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
                extrato(ag, conta);
                break;
            case 2:
                consultarSaldo(ag, conta);
                break;
            case 3:
                saque(ag, conta);
                break;
            case 4:
                printf("Agencia do Deposito: ");
                scanf("%d",&agDep);
                printf("Conta do Deposito: ");
                scanf("%d",&contaDep);
                deposito(agDep, contaDep);
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
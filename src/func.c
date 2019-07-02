#include "func.h"
#include "estrutura.c"
#define LMT 500
//Erro na abertura arquivo
void erroAbert(int e)
{
    if (e == 1)
        printf("[Erro 101]\n");
    else if (e == 2)
        printf("[Erro 102]\n");
    else if (e == 3)
        printf("[Erro 103]\n");
    else if (e == 4)
        printf("[Erro 104]\n");
}

//veficia agencia
//1 se existir 0 se nao
boolean verAg(int ver)
{
    //verif
    FILE *listaAgencia = fopen("agencias/lista-agencias.txt", "r+");
    if (listaAgencia == NULL)
    {
        erroAbert(1);
        fclose(listaAgencia);
        return 0;
    }
    //logica
    int ag = 0;
    while (!feof(listaAgencia))
    {
        fscanf(listaAgencia, "%d", &ag);
        if (ag == ver)
        {
            fclose(listaAgencia);
            return 1;
        }
    }
    fclose(listaAgencia);
    return 0;
}

//veficia Conta
//1 se existir 0 se nao
int verConta(int ag, int conta)
{
    //verif
    char caminho[100];
    sprintf(caminho, "agencias/%d/lista-contas.txt", ag);
    FILE *listaConta = fopen(caminho, "r+");
    if (listaConta == NULL)
    {
        erroAbert(2);
        fclose(listaConta);
        return 0;
    }
    //logica
    int ver = 0;
    int tipoConta;
    while (!feof(listaConta))
    {
        fscanf(listaConta, "%d %d", &ver, &tipoConta);
        if (ver == conta)
        {
            fclose(listaConta);
            return tipoConta;
        }
    }
    fclose(listaConta);
    return 3;
}

//veficia senha
//1 se correta 0 se incorreta
boolean verSenha(int ag, int conta, int ver)
{
    //verif
    char caminho[100];
    sprintf(caminho, "agencias/%d/%d/infos.txt", ag, conta);
    FILE *infos = fopen(caminho, "r+");
    if (infos == NULL)
    {
        erroAbert(3);
        fclose(infos);
        return 0;
    }
    //logica
    int senha = 0;
    char tipo;
    fscanf(infos, "%c%d", &tipo, &senha);
    if (senha == ver)
    {
        fclose(infos);
        return 1;
    }
    fclose(infos);
    return 0;
}

char *pegaNome(int ag, int conta)
{
    //verif
    char caminho[100];
    sprintf(caminho, "agencias/%d/%d/infos.txt", ag, conta);
    FILE *infos = fopen(caminho, "r+");
    if (infos == NULL)
    {
        erroAbert(4);
        fclose(infos);
        return NULL;
    }
    char tipo = 32;
    char *nome = malloc(50 * sizeof(char));
    char nome1[15];
    char nome2[15];
    char nome3[15];
    while (!feof(infos))
    {
        fscanf(infos, "%s %s %s", nome1, nome2, nome3);
        if (nome1[0] == 35)
            break;
    }

    if (nome1[0] == 35)
    { //35 é a #
        if (nome3[0] == 35)
        {
            sprintf(nome, "%s %s", (nome1 + 1), nome2);
            fclose(infos);
            return nome;
        }
        else
        {
            sprintf(nome, "%s %s %s", (nome1 + 1), nome2, nome3);
            fclose(infos);
            return nome;
        }
    }
    fclose(infos);
    return NULL;
}

TDia *tempo()
{
    time_t mytime;
    TDia *hoje = malloc(sizeof(TDia));
    mytime = time(NULL);
    struct tm tm = *localtime(&mytime);
    hoje->dia = tm.tm_mday;
    hoje->mes = tm.tm_mon + 1;
    hoje->ano = tm.tm_year + 1900;
    return hoje;
}

double pegaSaldo(int ag, int conta)
{
    double valor;
    double limite;
    char caminho[100];
    sprintf(caminho, "agencias/%d/%d/caixa.txt", ag, conta);
    FILE *caixa = fopen(caminho, "r+");
    if (caixa == NULL)
    {
        erroAbert(4);
        system("sleep 02");
        fclose(caixa);
        return 0;
    }

    fscanf(caixa, "%lf %lf", &valor, &limite);
    fclose(caixa);
    return valor;
}

double pegaLimite(int ag, int conta)
{
    double valor;
    double limite;
    char caminho[100];
    sprintf(caminho, "agencias/%d/%d/caixa.txt", ag, conta);
    FILE *caixa = fopen(caminho, "r+");
    if (caixa == NULL)
    {
        erroAbert(4);
        system("sleep 02");
        fclose(caixa);
        return 0;
    }

    fscanf(caixa, "%lf %lf", &valor, &limite);
    fclose(caixa);
    return limite;
}

boolean salvaSaldoLimite(int ag, int conta, double saldo, double limite)
{
    char caminho[100];
    sprintf(caminho, "agencias/%d/%d/caixa.txt", ag, conta);
    // remove(caminho);
    FILE *caixa = fopen(caminho, "w+");
    if (caixa == NULL)
    {
        erroAbert(4);
        system("sleep 02");
        fclose(caixa);
        return 0;
    }

    fprintf(caixa, "%lf %lf", saldo, limite);
    fclose(caixa);
    return 1;
}

boolean gravaOperacao(int ag, int conta, int op, double valor, double saldo, double limite, int tipoConta)
{
    char caminho[100];
    TDia *dataAtual = tempo();
    sprintf(caminho, "agencias/%d/%d/operacoes.txt", ag, conta);
    FILE *operacoes = fopen(caminho, "a+");
    if (operacoes == NULL)
    {
        erroAbert(4);
        fclose(operacoes);
        return 0;
    }
    if (tipoConta == 1)
        fprintf(operacoes, "%d %d %d %d %lf %lf\n", dataAtual->dia, dataAtual->mes, dataAtual->ano, op, valor, saldo);
    else
        fprintf(operacoes, "%d %d %d %d %lf %lf %lf\n", dataAtual->dia, dataAtual->mes, dataAtual->ano, op, valor, saldo, limite);
    fclose(operacoes);
}

void consultarSaldo(int ag, int conta, int tipoConta)
{
    char *nome = pegaNome(ag, conta);

    printf("Nome do Titular: %s\n", nome);
    printf("Agencia: %d\n", ag);
    printf("Conta: %d\n", conta);
    if (tipoConta == 1)
        printf("Saldo: R$%.2lf\n", pegaSaldo(ag, conta));
    if (tipoConta == 2)
    {
        printf("Saldo: R$%.2lf\n", pegaSaldo(ag, conta));
        printf("Limite: R$%.2lf\n", pegaLimite(ag, conta));
    }
}

void sacar(int ag, int conta, double valor, int tipoConta)
{
    double saldo = pegaSaldo(ag, conta);
    double limite = pegaLimite(ag, conta);
    double auxConta;
    if (tipoConta == 1)
    {
        if ((saldo - valor) < 0)
        {
            printf("Valor nao disponivel!\n");
            return;
        }
        gravaOperacao(ag, conta, 0, valor, (saldo - valor), 0, tipoConta);
        salvaSaldoLimite(ag, conta, (saldo - valor), 0);
    }
    else
    {
        auxConta = saldo - valor;
        if (auxConta >= 0)
        {
            salvaSaldoLimite(ag, conta, (saldo - valor), limite);
            gravaOperacao(ag, conta, 0, valor, (saldo - valor), auxConta, tipoConta);
        }
        else
        {
            auxConta = limite + auxConta;
            if (auxConta >= 0)
            {
                salvaSaldoLimite(ag, conta, 0, auxConta);
                gravaOperacao(ag, conta, 0, valor, 0, auxConta, tipoConta);
            }
            else
            {
                printf("Valor nao disponivel!\n");
            }
        }
    }
}

void saque(int ag, int conta, int tipoConta)
{
    double valor;
    double saldo = pegaSaldo(ag, conta);
    double limite = pegaLimite(ag, conta);
    double auxConta;
    printf("Qual valor deseja sacar?\n");
    scanf("%lf", &valor);

    sacar(ag, conta, valor, tipoConta);
    printf("Saque realizado!");
}

void depositar(int ag, int conta, double valor, int tipoConta)
{
    int saldo = pegaSaldo(ag, conta);
    int limite = 0;
    double aux;
    double auxVal;
    if (tipoConta == 1)
    {
        saldo += valor;
        salvaSaldoLimite(ag, conta, saldo, limite);
    }
    else
    {
        limite = pegaLimite(ag, conta);
        if (limite < LMT)
        {
            aux = limite - LMT;
            auxVal = valor + aux;
            if ((auxVal) >= 0)
            {
                saldo += auxVal;
                limite = LMT;
            }
            else
            {
                limite = LMT + aux;
            }
        }
        else
        {
            saldo += valor;
        }
        salvaSaldoLimite(ag, conta, saldo, limite);
    }
    gravaOperacao(ag, conta, 1, valor, saldo, limite, tipoConta);
}

void deposito(int ag, int conta, int tipoConta)
{
    //Verifica se a conta pro deposito é valida
    if (!verAg(ag))
    {
        printf("Dados Invalidos!\n");
        return;
    }
    else
    {
        if (verConta(ag, conta) == 3)
        {
            printf("Dados Invalidos!\n");
            return;
        }
    }
    double saldo = pegaSaldo(ag, conta);
    char *nome = pegaNome(ag, conta);
    int op;
    double valorDep = 0;
    printf("\nQual o valor do Deposito?\n");
    scanf("%lf", &valorDep);

    printf("\nBeneficiado: %s\nAg: %d\nConta: %d\nValor: %.2lf\n", nome, ag, conta, valorDep);
    printf("Informacoes Corretas?\n1.Sim | 2.Nao\n");
    scanf("%d", &op);

    if (op == 2)
    {
        system("cls");
        printf("Operacao Cancelada!\n");
        system("sleep 02");
        return;
    }
    depositar(ag, conta, valorDep, tipoConta);
    printf("Deposito Realizado!\n");
    free(nome);
}

void extrato(int ag, int conta, int tipoConta)
{
    TDia data;
    TDia *atual = tempo();
    char *nome = pegaNome(ag, conta);
    int op, i;
    char caminho[100];
    double valor, saldo, limite;
    sprintf(caminho, "agencias/%d/%d/operacoes.txt", ag, conta);
    FILE *operacoes = fopen(caminho, "r+");
    if (operacoes == NULL)
    {
        printf("Nenhuma operacao foi realizada ainda.");
        return;
    }
    if (!feof(operacoes))
    {
        printf("Titular: %s Agencia: %d Conta: %d\n", nome, ag, conta);
        printf("_________________________________________\n\n");
    }
    i = 0;
    while (!feof(operacoes))
    {
        if (tipoConta == 1)
        {
            fscanf(operacoes, "%d %d %d %d %lf %lf\n", &data.dia, &data.mes, &data.ano, &op, &valor, &saldo);
            if (data.mes == atual->mes)
            {
                printf("%d/%d/%d - ", data.dia, data.mes, data.ano);
                i++;
                if (op)
                {
                    printf("Deposito de: R$%.2lf totalizando R$%.2lf\n", valor, saldo);
                }
                else
                {
                    printf("Saque de: R$%.2lf totalizando R$%.2lf\n", valor, saldo);
                }
            }
        }
        else
        {
            fscanf(operacoes, "%d %d %d %d %lf %lf %lf\n", &data.dia, &data.mes, &data.ano, &op, &valor, &saldo, &limite);
            if (data.mes == atual->mes)
            {
                printf("%d/%d/%d - ", data.dia, data.mes, data.ano);
                i++;
                if (op)
                {
                    printf("Deposito de: R$%.2lf totalizando R$%.2lf e limite R$%.2lf\n", valor, saldo, limite);
                }
                else
                {
                    printf("Saque de: R$%.2lf totalizando R$%.2lf e limite R$%.2lf\n", valor, saldo, limite);
                }
            }
        }
    }
    if (i == 0)
        printf("Nenhuma operacao foi encontrada neste mes.\n");
    fclose(operacoes);
}

boolean salvarNumeroCelular(int ag, int conta, int operadora, int ddd, int telefone)
{
    char caminho[100];
    sprintf(caminho, "agencias/%d/%d/celulares.txt", ag, conta);
    FILE *celulares = fopen(caminho, "a+");
    if (celulares == NULL)
    {
        erroAbert(4);
        fclose(celulares);
        return 0;
    }
    fprintf(celulares, "%d %d %d\n", operadora, ddd, telefone);
    fclose(celulares);
    return 1;
}

boolean recarga(int ag, int conta)
{
    TCel *celular = NULL;
    TCel *celRecarga;
    char caminho[100];
    int operadora, ddd, telefone;
    int preCadastrado;
    int i = 0;
    int selecionado;
    int valor;
    int dddVer;
    int telefoneVer;
    sprintf(caminho, "agencias/%d/%d/celulares.txt", ag, conta);
    FILE *celulares = fopen(caminho, "rw+");
    if (celulares == NULL)
    {
        erroAbert(4);
        fclose(celulares);
        return 0;
    }
    printf(".:Recarga:.\n");
    printf("____________\n");
    printf("Usar numeros pre cadastrados?\n");
    printf("1.Sim | 2. Nao\n");
    scanf("%d", &preCadastrado);
    if (preCadastrado == 1)
    {
        while (!feof(celulares))
        {
            i++;
            fscanf(celulares, "%d %d %d", &operadora, &ddd, &telefone);
            printf("%d. ", i);
            switch (operadora)
            {
            case 1:
                printf("TIM -");
                break;
            case 2:
                printf("CLARO -");
                break;
            case 3:
                printf("VIVO -");
                break;
            default:
                printf("Erro!");
                return 0;
                fclose(celulares);
                break;
            }
            printf(" (%d) %d\n", ddd, telefone);
            insere(&celular, i, ddd, telefone);
        }
        printf("Qual quer utilizar?\n");
        scanf("%d", &selecionado);
        if (selecionado > i)
        {
            printf("O selecionado nao existe!\n");
            fclose(celulares);
            return 0;
        }
        celRecarga = busca(celular, selecionado);
    }
    else
    {
        printf("Escolha a Operadora.\n");
        printf("1. TIM\n");
        printf("2. CLARO\n");
        printf("3. VIVO\n");
        scanf("%d", &operadora);
        printf("Qual o DDD?\n");
        scanf("%d", &ddd);
        printf("Qual o Numero?\n");
        scanf("%d", &telefone);
        printf("Repita o DDD?\n");
        scanf("%d", &dddVer);
        printf("Repita o Numero?\n");
        scanf("%d", &telefoneVer);
        if (!((ddd == dddVer) && (telefone == telefoneVer)))
        {
            printf("Telefone Invalido!");
            fclose(celulares);
            return 0;
        }
        fclose(celulares);
        FILE *celulares = fopen(caminho, "a+");
        if (celulares == NULL)
        {
            erroAbert(4);
            fclose(celulares);
            return 0;
        }
        salvarNumeroCelular(ag, conta, operadora, ddd, telefone);
        fclose(celulares);
    }

    printf("Qual valor deseja recarregar?\n");
    printf("1. R$15,00\n");
    printf("2. R$20,00\n");
    printf("3. R$30,00\n");
    printf("4. R$50,00\n");
    scanf("%d", &valor);

    switch (valor)
    {
    case 1:
        sacar(ag, conta, 15, verConta(ag, conta));
        break;
    case 2:
        sacar(ag, conta, 20, verConta(ag, conta));
        break;
    case 3:
        sacar(ag, conta, 30, verConta(ag, conta));
        break;
    case 4:
        sacar(ag, conta, 50, verConta(ag, conta));
        break;
    default:
        printf("Valor invalido!");
        fclose(celulares);
        return 0;
        break;
    }
    fclose(celulares);
    return 1;
}

int verEmprestimo(int ag, int conta)
{
    //verif
    char caminho[100];
    sprintf(caminho, "agencias/%d/%d/infos.txt", ag, conta);
    FILE *infos = fopen(caminho, "r+");
    if (infos == NULL)
    {
        erroAbert(4);
        fclose(infos);
        return 0;
    }
    char tipo = 32;
    char *nome = malloc(50 * sizeof(char));
    char nome1[15];
    char nome2[15];
    char nome3[15];
    while (!feof(infos))
    {
        fscanf(infos, "%s %s %s", nome1, nome2, nome3);
        if (nome1[0] == 36)
            break;
    }

    if (nome1[0] == 36)
    { //36 é a $

        fclose(infos);
        return atoi(nome2);
    }
    fclose(infos);
    return 3;
}

boolean attInfoEmprestimo(int ag, int conta, int op)
{
    //verif
    char caminho[100];
    sprintf(caminho, "agencias/%d/%d/infos.txt", ag, conta);
    FILE *infos = fopen(caminho, "r+");
    if (infos == NULL)
    {
        erroAbert(4);
        fclose(infos);
        return 0;
    }
    char tipo = 32;
    char *nome = malloc(50 * sizeof(char));
    char conta1[15];
    char conta2[15];
    char conta3[15];
    char nome1[15];
    char nome2[15];
    char nome3[15];
    char emprestimo1[15];
    char emprestimo2[15];
    char emprestimo3[15];
    fscanf(infos, "%s %s %s", conta1, conta2, conta3);
    fscanf(infos, "%s %s %s", nome1, nome2, nome3);
    fscanf(infos, "%s %s %s", emprestimo1, emprestimo2, emprestimo3);
    fclose(infos);
    infos = fopen(caminho, "w+");
    if (infos == NULL)
    {
        erroAbert(4);
        fclose(infos);
        return 0;
    }
    fprintf(infos, "%s %s %s\n", conta1, conta2, conta3);
    fprintf(infos, "%s %s %s\n", nome1, nome2, nome3);
    fprintf(infos, "%s %d %s\n", emprestimo1, op, emprestimo3);

    fclose(infos);
    return 3;
}

boolean atualizaEmprestimo(int ag, int conta, int numParcelas, double valorParcela, int diaEmp, int mesEmp, int anoEmp)
{
    TDia *dtaUltPag = tempo();
    char caminho[100];
    sprintf(caminho, "agencias/%d/%d/emprestimoJuros.txt", ag, conta);
    FILE *emprestimoJuros = fopen(caminho, "w+");
    if (emprestimoJuros == NULL)
    {
        erroAbert(4);
        fclose(emprestimoJuros);
        return 0;
    }
    //1. Numero de parcelas
    //2. Valor Parcela
    //3. Dia do emprestimo
    //4. Mes do emprestimo
    //5. Ano do emprestimo
    fprintf(emprestimoJuros, "%d %lf %d %d %d %d %d %d\n", numParcelas, valorParcela, diaEmp, mesEmp, anoEmp, dtaUltPag->dia, dtaUltPag->mes, dtaUltPag->ano);
    if (valorParcela == 0)
    {
        attInfoEmprestimo(ag, conta, 0);
    }
    fclose(emprestimoJuros);
    return 1;
}
boolean cobraEmprestimo(int ag, int conta)
{
    int verifEmp = verEmprestimo(ag, conta);
    if (verifEmp == 3)
    {
        printf("Erro na verificacao do emprestimo!\n");
        return 0;
    }
    if (verifEmp == 0)
    {
        printf("Nao ha emprestimo ativo!\n");
        return 0;
    }
    TDia dtaEmp;
    TDia dtaUltPag;
    TDia *dtaAtual = tempo();
    TDia help;
    double saldoDev;
    int numPar;
    int mesAtras;
    int diaTemp, mesTemp, anoTemp;
    double vlrPar;
    char caminho[100];
    double valor = 0;
    int dias = 0;
    int parcelas;
    sprintf(caminho, "agencias/%d/%d/emprestimoJuros.txt", ag, conta);
    FILE *emprestimoJuros = fopen(caminho, "rw+");
    if (emprestimoJuros == NULL)
    {
        erroAbert(4);
        fclose(emprestimoJuros);
        return 0;
    }

    fscanf(emprestimoJuros, "%d %lf %d %d %d %d %d %d", &numPar, &vlrPar, &dtaEmp.dia, &dtaEmp.mes, &dtaEmp.ano, &dtaUltPag.dia, &dtaUltPag.mes, &dtaUltPag.ano);
    printf("%d", dtaUltPag.ano);
    if (dtaUltPag.ano == -1)
    {

        help.ano = dtaAtual->ano - dtaEmp.ano;
        if (help.ano == 0)
        {
            help.mes = dtaAtual->mes - dtaEmp.mes;
            if (mes > 0)
            {
                help.dia = dtaEmp.dia - dtaAtual.dia;
                if (help.dia < 0)
                {
                    help.mes--;
                }
            }
        }
        else
        {
            help.mes = dtaAtual->mes - dtaEmp.mes;
            if (help.mes < 0)
            {
                help.ano--;
            }
            else
            {
                help.dia = dtaAtual->dia - dtaEmp.dia;
                if (help.dia < 0)
                {
                    help.mes--;
                }
            }
        }
    }
    else
    {
        help.ano = dtaAtual->ano - dtaUltPag.ano;
        if (help.ano == 0)
        {
            help.mes = dtaAtual->mes - dtaUltPag.mes;
            if (mes > 0)
            {
                help.dia = dtaUltPag.dia - dtaAtual.dia;
                if (help.dia < 0)
                {
                    help.mes--;
                }
            }
        }
        else
        {
            help.mes = dtaAtual->mes - dtaUltPag.mes;
            if (help.mes < 0)
            {
                help.ano--;
            }
            else
            {
                help.dia = dtaAtual->dia - dtaUltPag.dia;
                if (help.dia < 0)
                {
                    help.mes--;
                }
            }
        }
    }
    parcelas = ((help.ano * 12) + help.mes) ;
    valor = parcelas * vlrPar;
    //     while ((help.dia != dtaAtual->dia) && (help.mes != dtaAtual->mes) && (help.ano != dtaAtual->ano))
    //     {
    //         help.dia++;
    //         dias++;
    //         if (help.dia == 30)
    //         {

    //             if (help.mes == 12)
    //             {
    //                 help.ano++;
    //                 help.mes = 1;
    //             }
    //             else
    //                 help.mes++;
    //             help.dia = dtaEmp.dia;
    //         }
    //     }
    //     parcelas = (int)(dias / 30);
    //     if (parcelas > numPar)
    //     {
    //         valor = numPar * vlrPar;
    //         numPar = 0;
    //     }
    //     else
    //     {
    //         if (parcelas == numPar)
    //         {
    //             valor = numPar * vlrPar;
    //             numPar = 0;
    //         }
    //         else
    //         {
    //             valor = vlrPar + (vlrPar * (int)(dias / 30));
    //             dtaUltPag.dia = dtaEmp.dia;
    //             dtaUltPag.mes = dtaAtual->mes;
    //             dtaUltPag.ano = dtaAtual->ano;
    //             numPar = numPar - parcelas;
    //         }
    //     }
    // }
    // else
    // {
    //     help.dia = dtaUltPag.dia;
    //     help.mes = dtaUltPag.mes;
    //     help.ano = dtaUltPag.ano;
    //     while (help.dia != dtaAtual->dia && help.mes != dtaAtual->mes && help.ano != dtaAtual->ano)
    //     {
    //         help.dia++;
    //         dias++;
    //         if (help.dia == 30)
    //         {
    //             if (help.mes == 12)
    //             {
    //                 help.ano++;
    //                 help.mes = 1;
    //             }
    //             else
    //                 help.mes++;
    //             help.dia = dtaEmp.dia;
    //         }
    //     }
    //     parcelas = (int)(dias / 30);
    //     if (parcelas > numPar)
    //     {
    //         valor = numPar * vlrPar;
    //         numPar = 0;
    //     }
    //     else
    //     {
    //         if (parcelas == numPar)
    //         {
    //             valor = numPar * vlrPar;
    //             numPar = 0;
    //         }
    //         else
    //         {
    //             valor = vlrPar + (vlrPar * (int)(dias / 30));
    //             dtaUltPag.dia = dtaEmp.dia;
    //             dtaUltPag.mes = dtaAtual->mes;
    //             dtaUltPag.ano = dtaAtual->ano;
    //             numPar = numPar - parcelas;
    //         }
    //     }
    // }
    atualizaEmprestimo(ag, conta, numPar, vlrPar, dtaEmp.dia, dtaEmp.mes, dtaEmp.ano);
    printf("%lf", valor);
    sacar(ag, conta, valor, verConta(ag, conta));
    free(dtaAtual);
    fclose(emprestimoJuros);
    return 1;
}
boolean salvaEmprestimo(int ag, int conta, int numParcelas, double valorParcela)
{
    TDia *dtaEmprestimo = tempo();
    char caminho[100];
    sprintf(caminho, "agencias/%d/%d/emprestimoJuros.txt", ag, conta);
    FILE *emprestimoJuros = fopen(caminho, "w+");
    if (emprestimoJuros == NULL)
    {
        erroAbert(4);
        fclose(emprestimoJuros);
        return 0;
    }
    //1. Numero de parcelas
    //2. Valor Parcela
    //3. Dia do emprestimo
    //4. Mes do emprestimo
    //5. Ano do emprestimo
    fprintf(emprestimoJuros, "%d %lf %d %d %d -1 -1 -1\n", numParcelas, valorParcela, dtaEmprestimo->dia, dtaEmprestimo->mes, dtaEmprestimo->ano);
    attInfoEmprestimo(ag, conta, 1);
    fclose(emprestimoJuros);
    free(dtaEmprestimo);
    return 1;
}

boolean emprestimo(int ag, int conta)
{
    int tempEmprestimo;
    double valorEmprestimo;
    double valorParcela;
    int numParcela;
    int verifEmp = verEmprestimo(ag, conta);
    if (verifEmp == 3)
    {
        printf("Emprestimo não disponivel no momento!\n");
        return 0;
    }
    else if (verifEmp)
    {
        printf("Voce ja tem um emprestimo em andamento!\n");
        return 0;
    }

    printf("Qual valor do emprestimo?\n");
    scanf("%lf", &valorEmprestimo);
    if ((valorEmprestimo > 50000) || (valorEmprestimo < 0))
    {
        if (valorEmprestimo > 50000)
        {
            printf("[Valor incorreto] Valor maximo R$50.000,00\n");
            return 0;
        }
        if (valorEmprestimo < 0)
        {
            printf("[Valor incorreto] Valor tem que ser positivo\n");
            return 0;
        }
    }
    printf("Em quantos meses quer pagar?\n");
    printf("1. 12\n");
    printf("2. 24\n");
    printf("3. 36\n");
    printf("4. 48\n");
    printf("5. 60\n");
    printf("6. 72\n");
    printf("7. 84\n");
    printf("8. 96\n");
    scanf("%d", &tempEmprestimo);
    switch (tempEmprestimo)
    {
    case 1:
        valorParcela = (((valorEmprestimo / 100) * (1 * 13.08)) + valorEmprestimo) / 12;
        depositar(ag, conta, valorEmprestimo, verConta(ag, conta));
        numParcela = 12;
        break;
    case 2:
        valorParcela = (((valorEmprestimo / 100) * (2 * 13.08)) + valorEmprestimo) / 24;
        depositar(ag, conta, valorEmprestimo, verConta(ag, conta));
        numParcela = 24;
        break;
    case 3:
        valorParcela = (((valorEmprestimo / 100) * (3 * 13.08)) + valorEmprestimo) / 36;
        depositar(ag, conta, valorEmprestimo, verConta(ag, conta));
        numParcela = 36;
        break;
    case 4:
        valorParcela = (((valorEmprestimo / 100) * (4 * 13.08)) + valorEmprestimo) / 48;
        depositar(ag, conta, valorEmprestimo, verConta(ag, conta));
        numParcela = 48;
        break;
    case 5:
        valorParcela = (((valorEmprestimo / 100) * (5 * 13.08)) + valorEmprestimo) / 60;
        depositar(ag, conta, valorEmprestimo, verConta(ag, conta));
        numParcela = 60;
        break;
    case 6:
        valorParcela = (((valorEmprestimo / 100) * (6 * 13.08)) + valorEmprestimo) / 72;
        depositar(ag, conta, valorEmprestimo, verConta(ag, conta));
        numParcela = 72;
        break;
    case 7:
        valorParcela = (((valorEmprestimo / 100) * (7 * 13.08)) + valorEmprestimo) / 84;
        depositar(ag, conta, valorEmprestimo, verConta(ag, conta));
        numParcela = 84;
        break;
    case 8:
        valorParcela = (((valorEmprestimo / 100) * (8 * 13.08)) + valorEmprestimo) / 96;
        depositar(ag, conta, valorEmprestimo, verConta(ag, conta));
        numParcela = 96;
        break;
    default:
        printf("Opcao incorreta!");
        return 0;
        break;
    }
    salvaEmprestimo(ag, conta, numParcela, valorParcela);
    return 1;
}

void login(int ag, int conta, int senha)
{
    boolean verifAg = verAg(ag);
    int tipoConta = verConta(ag, conta);
    if (tipoConta == 3)
    {
        printf("Falha no Login: Informacoes Erradas.\n");
        return;
    }
    boolean verifSenha = verSenha(ag, conta, senha);
    if (verifAg && verSenha)
    {
        char *nome = pegaNome(ag, conta);
        if (nome == NULL)
        {
            printf("[Falha no Sistema]\n");
            erroAbert(4);
            return;
        }

        int op = 0;
        int agDep;
        int contaDep;
        double valor;
        int ope;
        cobraEmprestimo(ag, conta);
        printf("[Login Efetuado]\n\n");
        printf("Ola %s,\n", nome);

        do
        {
            printf("\nO que deseja fazer?\n");
            printf("1. Extrato\n");
            printf("2. Consultar Saldo\n");
            printf("3. Saque\n");
            printf("4. Deposito\n");
            printf("5. Transferencia\n");
            printf("6. Recarga de Celular\n");
            printf("7. Emprestimo\n");
            printf("0. Sair\n");

            scanf("%d", &op);
            switch (op)
            {
            case 1:
                extrato(ag, conta, tipoConta);
                break;
            case 2:
                consultarSaldo(ag, conta, tipoConta);
                break;
            case 3:
                saque(ag, conta, tipoConta);
                break;
            case 4:
                printf("Agencia do Deposito: ");
                scanf("%d", &agDep);
                printf("Conta do Deposito: ");
                scanf("%d", &contaDep);
                deposito(agDep, contaDep, tipoConta);
                break;
            case 5:
                printf("Agencia do Beneficiado: ");
                scanf("%d", &agDep);
                printf("Conta do Beneficiado: ");
                scanf("%d", &contaDep);
                printf("Valor da transferencia: ");
                scanf("%lf", &valor);
                char *nome = pegaNome(agDep, contaDep);
                printf("\nBeneficiado: %s\nAg: %d\nConta: %d\nValor: %.2lf\n", nome, agDep, contaDep, valor);
                printf("Informacoes Corretas?\n1.Sim | 2.Nao\n");
                scanf("%d", &ope);
                if (ope == 1)
                {
                    sacar(ag, conta, valor, verConta(ag, conta));
                    depositar(agDep, contaDep, valor, verConta(ag, conta));
                    printf("Transferencia Realizada!\n");
                }
                else
                {
                    printf("Operacao Cancelada!\n");
                }
                free(nome);
                break;
            case 6:
                if (recarga(ag, conta))
                {
                    printf("Recarga Efetuada!");
                }
                break;
            case 7:
                emprestimo(ag, conta);
                break;
            case 0:
                printf("\nObrigado por utilizar nosso Banco!");
                break;
            default:
                printf("Opcao errada %s tente outra!");
                break;
            }
            // system("sleep 20");
            // system("cls");
        } while (op != 0);
    }
    else
    {
        printf("Falha no Login: Informacoes Erradas.\n");
    }
}
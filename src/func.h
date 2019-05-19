typedef struct dia{
    int dia;
    int mes;
    int ano;
}TDia;

typedef struct extrato{
    int dia;
    int mes;
    int ano;
    int op;
    double valor;
    double saldo;
    struct extrato* prox;
}TExt;
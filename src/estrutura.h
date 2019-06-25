typedef struct telefone{
    int identificador;
    int ddd;
    int telefone;
    struct telefone *prox;
}TCel;
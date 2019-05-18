//Erro na abertura arquivo
void erroAbert(){
    printf("Erro 101");
}

//veficia agencia
//1 se existir 0 se nao
boolean verAg(int ver){
    //verif
    FILE* listaAgencia = fopen("agencias/lista-agencias.txt", "r+");
    if(listaAgencia == NULL){
        erroAbert();
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
        erroAbert();
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
        erroAbert();
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

void login(int ag, int conta, int senha){
    if(verAg(ag) && verConta(ag, conta) && verSenha(ag, conta, senha)){
        printf("Login Efetuado\n");
    }
}
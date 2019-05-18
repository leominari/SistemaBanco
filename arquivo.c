FILE* abreArquivoConta(){
    if(system("mkdir agencias\\contas")){
        printf("CRIO");
    }
    else
    {
        printf("Não criou");
    }
    
}
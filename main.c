#include <stdio.h>
#include <windows.h>

int main(){
    int op = 7;
    do{
        printf("1. OP\n");
        printf("2. OP\n");
        printf("3. OP\n");
        printf("4. OP\n");
        printf("5. OP\n");
        printf("6. OP\n");
        printf("0. OP\n");
        scanf("%d", &op);

        switch (op)
        {
        case 1:
            funcao();
            break;
        
        default:
            break;
        }

        
    }while(op != 0);
    return 0;
}
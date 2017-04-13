#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//#include "conta_bancaria.h"
//#include "transacao.h"

int main(void) 
{
   
    unsigned int opcao = 0;

    /*  Implementaçao do menu inicial   */

    do  {

        printf("MENU INICIAL\t\n");
        printf("\tDigite a opção desejada:\n");
        printf("\t\t1 - Criação de conta;\n");
        printf("\t\t2 - Depósito em conta;\n");
        printf("\t\t3 - Saque de conta;\n");
        printf("\t\t4 - Tranferência entre contas;\n");
        printf("\t\t0 - Sair do menu.\nOpção>> ");

        scanf("%ud", &opcao);                                                               // Recebe a opçao.

        // Comparar expressao de opcao
        switch(opcao)   {
            case 0:                                                                         // Sai do menu e do programa.
                printf("Operação encerrada.\n");
                break;
            case 1:                                                                         // Criaçao de conta.
                //
                break;
            case 2:                                                                         // Deposito em conta.
                //
                break;
            case 3:                                                                         // Saque de conta.
                //
                break;
            case 4:                                                                         // Tranferencia entre contas.
                //
                break;
            default:                                                                        // Erro de escolha de opcao.
                printf("Opção inválida!!!\n\tEntre com um valor entre 0 e 4.\n");
                break;
        }
    }   while(opcao != 0);                                                                  // Loop enquanto o cliente nao sai do menu.

    return 0;
}

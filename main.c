#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "conta_bancaria.h"
#include "transacao.h"

#define INI_CLI 30                                                                          // Numero inicial de clientes.

int main(void) 
{
   
    unsigned int opcao = 0;

    ContaBancaria *contas = malloc(INI_CLI * sizeof(ContaBancaria));                        // Arranjo que guardara informações das contas.

    for(int i = 0; i < INI_CLI; i++)
        contas[i].numero = CONTA_VAZIA;

    int ncontas = 0;                                                                        // Guarda o numero de contas ativas.
    //time_t tempo;

    int daConta = CONTA_VAZIA;
    int paraConta = CONTA_VAZIA;
    double valor = 0.0;

    Transacao *transacao;                                                                   // TAD auxiliar para guardar informaçoes sobre transaçoes.

    Extrato *banco = malloc(INI_CLI * sizeof(Extrato));                                     // Extrato geral do banco que guarda transaçoes por tempo.

    /*  Implementaçao do menu inicial   */
    do  {

        int posicao = 0;
        time_t inicio = 0;
        time_t fim = 0;

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
                return 0;

            // Criacao de conta
            case 1:                                                                         
                printf("Entre com o número da conta (não negativo): ");
                scanf("%d", &daConta);

                //printf("Entre com o nome do titular da conta: ");

                inicio = time(NULL);
                //  Verifica existencia do numero da conta
                if(existeConta(ncontas, contas, daConta, &posicao))   {                   
                    printf("Numero de conta ja existente.");
                    break;
                }

                ContaBancaria *conta_aux = NovaConta(daConta, 0.0);                         // Cria nova conta.
                contas[posicao] = *conta_aux;
                ncontas++;                                                                  // Incrementa o numero de contas.
                fim = time(NULL);
                break;

            //  Deposito em conta
            case 2:                                                                         
                printf("Entre com o número da conta (positivo): ");
                scanf("%d", &daConta);
                printf("Entre com o valor do depósito: ");
                scanf("%lf", &valor);

                inicio = time(NULL);
                //  Verifica existencia da conta
                if(!(existeConta(ncontas, contas, daConta, &posicao)))  {
                    printf("Conta não existe.");
                    break;
                }

                transacao = Deposito(&contas[posicao], valor);                               // Coloca deposito em transacao.

                //  Coloca ordenado por valor a transacao no extrato da conta
               
                fim = time(NULL);
                //  Coloca ordenado por tempo a transacao no extrato do banco
                break;

            //  Saque de conta
            case 3:                                                                         
                printf("Entre com o número da conta (positivo): ");
                scanf("%d", &daConta);
                printf("Entre com o valor do depósito: ");
                scanf("%lf", &valor);

                inicio = time(NULL);
                //  Verifica existencia da conta
                if(!(existeConta(ncontas, contas, daConta, &posicao)))  {
                    printf("Conta não existe.");
                    break;
                }

                transacao = Saque(&contas[posicao], valor);                                  // Coloca saque em transacao.

                //  Coloca ordenado por valor a transacao no extrato da conta
               
                fim = time(NULL);
                //  Coloca ordenado por tempo a transacao no extrato do banco
                break;

            //  Transferencia entre contas
            case 4:                                                                         
                printf("Entre com o número da conta que realiza a transferência: ");
                scanf("%d", &daConta);
                printf("Entre com o número da conta de destino: ");
                scanf("%d", &paraConta);
                printf("Entre com o valor da transferência: ");
                scanf("%lf", &valor);

                inicio = time(NULL);
                //  Verifica existencia da conta remetente
                if(!(existeConta(ncontas, contas, daConta, &posicao)))  {
                    printf("Conta não existe.");
                    break;
                }

                //  Verifica existencia da conta de destino
                int posicao2 = CONTA_VAZIA;
                if(!(existeConta(ncontas, contas, daConta, &posicao2)))  {
                    printf("Conta não existe.");
                    break;
                }
               
                transacao = Transferencia(&contas[posicao], &contas[posicao2], valor);      // Coloca a transferencia em transacao.
                Transacao *transacao2 = Inverte(transacao);                                 // Coloca o inverso da transferencia em transacao2.

                //  Coloca ordenado por valor a transacao no extrato da conta remetente
                //  Coloca ordenado por valor a transacao no extrato da conta de destino
               
                fim = time(NULL);
                //  Coloca ordenados por tempo as transacoes no extrato do banco

                break;
            default:                                                                        // Erro de escolha de opcao.
                printf("Opção inválida!!!\n\tEntre com um valor entre 0 e 4.\n");
                break;
        }

        if((opcao == 1) || (opcao == 2) || (opcao == 3) || (opcao == 4))
            printf("Operação durou %ld segundos.\n", (fim - inicio));

    }   while(opcao != 0);                                                                  // Loop enquanto o cliente nao sai do menu.

    return 0;
}


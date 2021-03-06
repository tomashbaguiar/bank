#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "conta_bancaria.h"
#include "transacao.h"
#include "comandos.h"

#define INI_CLI 50                                                                          // Numero inicial de clientes.
#define ARQUIVO "cmd.txt"                                                                   // Define o nome do arquivo se simulação.

int main(int argc, char **argv) 
{
    //  Verifica número de argumentos   //
    if((argc > 3) || (argc == 2))    {
        printf("Utilização:\n");
        printf("\t./banco ou ./banco teste [numero_de_transações]\n");
        printf("se opção = teste, numero_de_transações > 1\n");
        return 1;
    }
    
    char *opt = NULL;
    int n = 0;
    if(argc == 3)   {
        opt = argv[1];
        n = atoi(argv[2]);                                                                  // Recebe o número de transações a serem simuladas.
    }

    unsigned int opcao = 0;

    Lista *contas = criaLista();                                                            // Lista que guarda a posicao do primeiro nó de conta.

    FILE *file = NULL;                                                                      // Recebe o arquivo para leitura e escrita.
    if(argc == 3)   {
        if(!strcmp("teste", opt))   {
            file = fopen(ARQUIVO, "w");                                                     // Abre o arquivo para escrita dos comandos.
            geraComandos(file, n);                                                          // Gera os comandos e escreve no arquivo.
            fclose(file);                                                                   // Fecha o arquivo.
            file = fopen(ARQUIVO, "r");
        }
    }

    char comando[CMD_TAM];

    //  Implementaçao do menu inicial   //
    do  {

        clock_t inicio = 0;
        clock_t fim = 0;
    
        //  Define qual o tipo de entrada de comandos   //
        if((file != NULL) && (!feof(file)))    {
            fgets(comando, CMD_TAM, file);                                                  // Recebe o comando do arquivo.
            comando[strlen(comando) - 1] = '\0';
        }
        else if(argc == 1)
            recebeComando(comando);                                                         // Recebe o comando do usuário.
        else    {
            printf("Argumento errado ou falta de argumento.\n");
            return 1;
        }

        // Comparar expressao de opcao
        Comando *cmd = trataComando(comando);
        opcao = cmd->operacao;
        switch(cmd->operacao)   {

            // Criacao de conta
            case 1:                                                                         
                inicio = clock();
                criarconta(contas, cmd->usuario, cmd->numeroContaDe);                       // Insere nova conta em contas.
                fim = clock();
                break;

            //  Deposito em conta
            case 2:                                                                         
                inicio = clock();
                depositoOuSaque(contas, cmd->numeroContaDe, cmd->valor, 0);                 // Deposito em conta.
                fim = clock();
                break;

            //  Saque de conta
            case 3:                                                                         
                inicio = clock();
                depositoOuSaque(contas, cmd->numeroContaDe, cmd->valor, 1);                 // Deposito em conta.
                fim = clock();
                break;

            //  Transferencia entre contas
            case 4:                                                                         
                inicio = clock();
                transferencia(contas, cmd->numeroContaDe, cmd->numeroContaPara, cmd->valor);// Transferencia entre contas.
                fim = clock();
                break;

            //  Listar extrato de uma conta
            case 5:
                inicio = clock();
                imprimeExtrato(contas, cmd->numeroContaDe, cmd->numeroContaPara);           // Lista as transacoes no extrato da conta.
                fim = clock();
                break;
        }
        if((cmd->operacao == 1) || (cmd->operacao == 2) || 
                (cmd->operacao == 3) || (cmd->operacao == 4) || (cmd->operacao == 5))   {
            double tempo = (double) ((fim - inicio) * 1000000.0/CLOCKS_PER_SEC);
            printf("Operação durou %lf micro segundos.\n", tempo);
        }
    }   while(opcao != 0);                                                                  // Loop enquanto o cliente nao sai do menu.

    if(file != NULL)
        fclose(file);                                                                       // Fecha o arquivo. 

    return 0;
}


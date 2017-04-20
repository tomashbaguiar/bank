#ifndef COMANDOS_H
    #define COMANDOS_H
    
    #include <stdio.h>
    
    #include "conta_bancaria.h"

    #define CMD_TAM 50                                                  // Tamanho máximo de entrada de comando.
    #define OPE_MAX 10                                                  // Número máximo de caracteres que uma op tem. (criaconta = 10).
    #define USU_MAX 28                                                  // Número máximo de caracteres que um nome pode conter.
    #define CON_MAX 10                                                  // Número máximo de caracteres que um número de conta tem.  
                                                                        //  [2^(32)-1]/2 - 1.
    #define VAL_MAX 7                                                   // Número máximo de caracteres que o valor de uma op tem.   
                                                                        //  (máx.: 1000,00/op).
    #define TIP_MAX 5                                                   // Número máximo de caracteres que "data" ou "valor" tem.
    #define CONTA_VAZIA -1

    typedef struct  {
        unsigned int operacao;                                          // Operação requerida pelo usuário.
        char usuario[28];                                               // Nome do usuário da conta.
        int numeroContaDe;                                              // Número da conta que realiza a operação.
        int numeroContaPara;                                            // Número da conta que recebe uma transferencia.
        double valor;                                                   // Valor da operação. (Máx.: R$ 1000,00)
    }
    Comando;

    //  Função que recebe o comando digitado pelo usuário e 
    //  retorna um ponteiro para tal comando.
    void recebeComando(char*);

    //  Função que trata o comando digitado e retorna a 
    //  TAD Comando.
    Comando *trataComando(const char*);

    //  Função que descobre qual comando foi digitado e 
    //  retorna seu número. 
    unsigned int descobreComando(const char*, int*);

    //  Função que descobre o nome do usuário e
    //  retorna ponteiro para ele.
    char *descobreNome(const char*, int*);

    //  Função que descobre números de contas digitados
    //  e retorna em formato de inteiro.
    int descobreConta(const char*, int*);

    //  Função que descobre valores digitados e 
    //  retorna em formato de long float (double).
    double descobreValor(const char*, int*);

    //  Função que descobre qual o tipo de impressão,
    //  por valor ou por data.
    int descobreTipo(const char*, int*);

    //  Função que gera n comandos de cada comando para 
    //  testes.
    void geraComandos(FILE*,unsigned int);
    
    /*
     * Procedimento que chama a função de criar novas
     * contas
     */
    void criarconta(Lista*, const char*, const int);

    /*
     * Procedimento que chama umas das funções 
     * saque ou depósito
     */
    void depositoOuSaque(Lista*, const int, const double, const int);

    /*
     * Procedimento que chama a função Transfere
     */
    void transferencia(Lista*, const int, const int, const double);

    /*
     * Procedimento que imprime o extrato de uma
     * conta
     */
    void imprimeExtrato(Lista*, const int, const int);

#endif  //  COMANDOS_H

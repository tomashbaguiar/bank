#ifndef CONTA_BANCARIA_H
#define CONTA_BANCARIA_H

#define TAMANHO_INICIAL 30
//typedef Transacao Extrato[TAMANHO_INICIAL];
//
#include "transacao.h"

typedef struct {
    int numero;
    double saldo;
    char nome[20];
    //Extrato extrato;
    Node *extrato;
} ContaBancaria;

typedef struct lista    {
    struct lista *anterior;
    ContaBancaria conta;
    struct lista *proximo;
}
Lista;

/*
 * Cria uma nova conta bancaria com o devido número de conta, valor de 
 * saldo e nome do titular.
 */
ContaBancaria* NovaConta(int, double);

/* 
 * Faz um deposito e retorna a operação que identifica este deposito
 */
Transacao* Deposito(ContaBancaria*, double);

/* 
 * Realiza um saque da conta corrente e retorna a operação que identifica o
 * saque.
 */
Transacao* Saque(ContaBancaria*, double);

/* 
 * Realiza uma transferencia entre duas contas bancarias retornando a operação
 * onde o deConta é a primeira conta e o paraConta é a segunda.
 */
Transacao* Transferencia(ContaBancaria*, ContaBancaria*, double);

void ImprimeConta(ContaBancaria*);

//int existeConta(int, ContaBancaria*, int, unsigned int*);
int existeConta(Lista*, const int, Lista**);

/*
 * Cria nova lista
 */
Lista *criaLista();

/*
 * Insere nó na lista
 */
void insereLista(Lista*, ContaBancaria*);

#endif

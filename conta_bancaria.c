#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "conta_bancaria.h"
#include "transacao.h"
#include "comandos.h"

double TransacaoDeMaiorValor(int n, Transacao extrato[n]) {
    double maiorValor = extrato[0].valor;
    for (int i = 1; i < n; i++) {
        if (extrato[i].valor > maiorValor) {
            maiorValor = extrato[i].valor;
        }
    }
    return maiorValor;
}

ContaBancaria *NovaConta(int num, double saldo) {
    ContaBancaria *conta = malloc(sizeof(ContaBancaria));                                   // Aloca espaço na memoria para nova conta.
    conta->numero = num;                                                                    // Insere o numero da conta.
    conta->saldo = saldo;                                                                   // Insere o saldo.
    conta->extrato = criaExtrato();                                                         // Cria o nó inicial do extrato.

    printf("conta criada com sucesso. ");

    return conta;
}
 
Transacao* Deposito(ContaBancaria *conta, double valor) {
    conta->saldo += valor;                                                                  // Incrementa saldo da conta.

    Transacao *transacao = malloc(sizeof(Transacao));                                       // Aloca espaço para nova transacao.
    //  Coloca valores nos campos da TAD transacao
    transacao->valor = valor;
    transacao->daConta = conta->numero;
    transacao->paraConta = CONTA_VAZIA;

    printf("Valor depositado com sucesso. Saldo é %lf. ", conta->saldo);

    return transacao;                                                                       // Retorna a transacao.
}
 
Transacao* Saque(ContaBancaria *conta, double valor) {
    conta->saldo -= valor;                                                                  // Decrementa saldo da conta.

    Transacao *transacao = malloc(sizeof(Transacao));                                       // Aloca espaço para nova transacao.
    //  Coloca valores nos campos da TAD transacao
    transacao->daConta = conta->numero;
    transacao->paraConta = CONTA_VAZIA;
    transacao->valor = valor;

    printf("Saque realizado com sucesso. Saldo é %lf. ", conta->saldo);

    return transacao;                                                                       // Retorna a transação.
}

Transacao
*Transferencia(ContaBancaria *ContaDe, ContaBancaria *ContaPara, double valor)
{
    ContaDe->saldo -= valor;                                                                // Decrementa saldo de transferido de.
    ContaPara->saldo += valor;                                                              // Incrementa saldo de transferido para.

    Transacao *transacao = malloc(sizeof(Transacao));                                       // Aloca espaço para transacao.
    // Insere valores na TAD da transacao
    transacao->daConta = ContaDe->numero;
    transacao->paraConta = ContaPara->numero;
    transacao->valor = valor;

    printf("Transferência realizada com sucesso. SaldoDe %lf. SaldoPara %lf. ", ContaDe->saldo, ContaPara->saldo);

    return transacao;                                                                       // Retorna transacao.
}
 
void ImprimeConta(ContaBancaria *conta) {
    printf("Numero: %d\n", conta->numero);
    printf("Saldo: %lf\n", conta->saldo);
}

int
existeConta(Lista *contas, const int numero, Lista **posicao)
{
    Lista *aux = contas;
    int achou = 0;
    while(aux != NULL)  {
        if(aux->conta.numero == numero) {
            achou = 1;
            break;
        }
        aux = aux->proximo;
    }
    *posicao = aux;

    return achou;
}

Lista*
criaLista()
{
    Lista *lista = malloc(sizeof(Lista));
    lista->anterior = NULL;
    lista->proximo = NULL;
    lista->conta.numero = CONTA_VAZIA;

    return lista;
}

void
insereLista(Lista *lista, ContaBancaria *conta)
{
    Lista *nova = (Lista *) malloc(sizeof(Lista));
    nova->conta = *conta;
    nova->proximo = NULL;
    nova->anterior = NULL;

    Lista *aux = lista;
    while(aux->proximo != NULL)
        aux = aux->proximo;

    nova->proximo = aux->proximo;
    nova->anterior = aux;
    aux->proximo = nova;
}


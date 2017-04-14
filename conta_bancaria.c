#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "conta_bancaria.h"
#include "transacao.h"

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

    return transacao;                                                                       // Retorna a transacao.
}
 
Transacao* Saque(ContaBancaria *conta, double valor) {
    conta->saldo -= valor;                                                                  // Decrementa saldo da conta.

    Transacao *transacao = malloc(sizeof(Transacao));                                       // Aloca espaço para nova transacao.
    //  Coloca valores nos campos da TAD transacao
    transacao->daConta = conta->numero;
    transacao->paraConta = CONTA_VAZIA;
    transacao->valor = valor;

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

    return transacao;                                                                       // Retorna transacao.
}
 
void Imprime(ContaBancaria *conta) {
    printf("Numero: %d\n", conta->numero);
    printf("Saldo: %f\n", conta->saldo);
}

int
existeConta(int n, ContaBancaria *contas, int numero, int *posicao)
{
    for(*posicao = 0; *posicao < n; (*posicao)++)                     // Verifica numero no vetor.
        if(contas[*posicao].numero == numero)
            break;

    return !(*posicao == n);                                                                 // Se pos = n, não existe a conta.
}

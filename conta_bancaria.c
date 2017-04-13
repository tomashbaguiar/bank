#include <stdio.h>
#include <stdlib.h>

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

//ContaBancaria *NovaConta(int num, double saldo) {
ContaBancaria *NovaConta(int num, double saldo, char *nome) {
    ContaBancaria *conta = malloc(sizeof(ContaBancaria));                                   // Aloca espaço na memoria para nova conta.
    conta->numero = num;                                                                    // Insere o numero da conta.
    conta->saldo = saldo;                                                                   // Insere o saldo.
    strcpy(conta->nome, nome);                                                              // Insere o nome do titular da conta.

    return conta;
}
 
Transacao* Deposito(ContaBancaria *conta, double valor) {
    conta->saldo += valor;
}
 
Transacao* Saque(ContaBancaria *conta, double valor) {
    conta->saldo -= valor;
}
 
void Imprime(ContaBancaria *conta) {
    printf("Numero: %d\n", conta->numero);
    printf("Saldo: %f\n", conta->saldo);
}

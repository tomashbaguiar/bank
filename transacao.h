#ifndef OPERACAO_H
#define OPERACAO_H

#define CONTA_VAZIA -1

#include <time.h>

typedef struct {
    int daConta;                                                                            //conta que originou a operação
    int paraConta;                                                                          //conta receptora da operação
    double valor;
    time_t data;                                                                            // Recebe a data da operaçao.
} Transacao;

typedef struct node  {
    struct node *anterior;
    Transacao transacao;
    struct node *proximo;
}
Node;
    
/*
 * Função auxiliar para casos de transferências.
 * Inverte do daConta com o paraConta
 */
Transacao* Inverte(Transacao*);

void ImprimeTransacao(Transacao*);

Node *criaExtrato();                                                                // Cria uma lista para n elementos.
void insereNodeValor(Node*);
void insereNodeTempo(Node*, Transacao*);                                            // Insere um nó na lista ordenadamente, por tempo.
void imprimeLista(Node*);                                                           // Imprime a lista.
void insereNodeData(Transacao*, Node*);                                             // Insere um nó na lista ordenadamente, por data,
                                                                                    // ou seja, insere o nó.

#endif

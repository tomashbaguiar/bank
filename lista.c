#include "lista.h"

#include <stdio.h>
#include <stdlib.h>

Node*
criaLista()
{
    Node *inicio = malloc(sizeof(Node));                                                    // Aloca espaço para o nó inicial.
    inicio->anterior = NULL;                                                                // Não tem nó anterior.
    inicio->transacao.valor = -999999999;                                                   // Menor valor que as entradas.
    inicio->proximo = NULL;                                                                 // Não tem nó posterior inicialmente.
    return inicio;                                                                          // Retorna o nó inicial.
}

void
insereNodeValor(Transacao *transacao, Node *inicio)
{
    Node *novo = malloc(sizeof(Node));                                                      // Aloca espaço para o novo nó.
    novo->transacao = *transacao;                                                           // Recebe no nó a transação.
    novo->anterior = NULL;                                                                  // Inicialmente sem nó anterior.
    novo->proximo = NULL;                                                                   // Inicialmente sem nó posterior.

    Node *aux = inicio;                                                                     // Nó auxiliar para comparar valores com o novo.
    Node *prev = NULL;                                                                      // Nó auxiliar para guardar nós anteriores ao novo.

    /*  Loop para inserir ordenadamente o novo nó   */
    do  {
        if(novo->transacao.valor < aux->transacao.valor)    {
            novo->anterior = aux->anterior;
            novo->proximo = aux;
            aux->anterior = novo;
            prev->proximo = novo;
            return;
        }
        prev = aux;
        aux = aux->proximo;
    }
    while(aux != NULL);

    novo->proximo = prev->proximo;
    prev->proximo = novo;
    novo->anterior = prev;
}

void imprimeLista(Node *inicio)
{
    Node *aux = inicio->proximo;                                                            // Nó auxiliar para receber o inicial.
    do  {
        printf("%lf ", aux->transacao.valor);
        aux = aux->proximo;                                                                 // Pula para o próximo nó.
    }   while(aux != NULL);
    printf("\n");
}


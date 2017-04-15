#ifndef LISTA_H
    #define LISTA_H

    #include "transacao.h"

    typedef struct Node  {
        struct Node *anterior;
        Transacao transacao;
        struct Node *proximo;
    }
    Node;

    Node *criaLista();                                                                  // Cria uma lista para n elementos.
    void insereNodeValor(Transacao*, Node*);                                            // Insere um nó na lista ordenadamente, por valor.
    void insereNodeTempo(Node*, Transacao*);                                            // Insere um nó na lista ordenadamente, por tempo.
    void imprimeLista(Node*);                                                           // Imprime a lista.

#endif  /* LISTA_H */

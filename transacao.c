#include <stdio.h>
#include <stdlib.h>

#include "transacao.h"
//#include "conta_bancaria.h"

Transacao* Inverte(Transacao* transacao) {
    Transacao* novaOperecao = malloc(sizeof(Transacao));
    (*novaOperecao).daConta = (*transacao).paraConta;
    (*novaOperecao).paraConta = (*transacao).daConta;
    (*novaOperecao).valor = -(*transacao).valor;
    return novaOperecao;
}

void ImprimeTransacao(Transacao* transacao) {
    printf("De: %d\n", (*transacao).daConta);
    printf("Para: %d\n", (*transacao).paraConta);
    printf("Valor: %.2f\n", (*transacao).valor);
}

Node*
criaExtrato()
{
    Node *inicio = malloc(sizeof(Node));                                                    // Aloca espaço para o nó inicial.
    inicio->anterior = NULL;                                                                // Não tem nó anterior.
    inicio->transacao.valor = -999999999;                                                   // Menor valor que as entradas.
    inicio->proximo = NULL;                                                                 // Não tem nó posterior inicialmente.
    
    return inicio;                                                                          // Retorna o nó inicial.
}

void imprimeLista(Node *inicio)
{
    Node *aux = inicio->proximo;                                                            // Nó auxiliar para receber o inicial.
    do  {
        printf("%s ", ctime(&(aux->transacao.data)));
        printf(" %lf\n", aux->transacao.valor);
        aux = aux->proximo;                                                                 // Pula para o próximo nó.
    }   while(aux != NULL);
}

void
insereNodeData(Transacao *transacao, Node *inicio)
{
    Node *novo = malloc(sizeof(Node));                                                      // Aloca espaço para o novo nó.
    novo->transacao = *transacao;                                                           // Recebe no nó a transação.
    novo->anterior = NULL;                                                                  // Inicialmente sem nó anterior.
    novo->proximo = NULL;                                                                   // Inicialmente sem nó posterior.
    time(&(novo->transacao.data));

    Node *aux = inicio;                                                                     // Nó auxiliar para comparar valores com o novo.

    //  Encontra o fim da lista //
    while(aux->proximo != NULL)
        aux = aux->proximo;

    //  Coloca o novo nó na lista   //
    novo->proximo = aux->proximo;
    novo->anterior = aux;
    aux->proximo = novo;
}

void
insereNodeValor(Node *inicio)
{
    Node *aux = inicio;
    int i = 0;

    //  Verifica o tamanho da lista //
    do  {
        i++;
        aux = aux->proximo;
    }
    while(aux->proximo != NULL);
    aux = inicio->proximo;
    
    //  Coloca a lista no array //
    Node *lista = (Node *) malloc(i * sizeof(Node));
    for(int j = 0; j < i; j++)  {
        lista[j] = *aux;
        aux = aux->proximo;
    }
    
    //  Ordena utilizando Selection Sort    //
    for(int j = 0; j < (i - 1); j++)    {
        int min = j;
        for(int k = (j + 1); k < i; k++)
            if(lista[k].transacao.valor < lista[min].transacao.valor)
                min = k;
        if(j != min)    {
            Node aux = lista[j];
            lista[j] = lista[min];
            lista[min] = aux;
        }
    }
    for(int j = 0; j < i; j++)  {
        printf("%s", ctime(&(lista[j].transacao.data)));
        printf("%lf\n", lista[j].transacao.valor);
    }
}


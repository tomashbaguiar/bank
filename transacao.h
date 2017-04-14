#ifndef OPERACAO_H
#define OPERACAO_H

#define CONTA_VAZIA -1

typedef struct {
    int daConta;                                                                            //conta que originou a operação
    int paraConta;                                                                          //conta receptora da operação
    double valor;
    time_t tempo;                                                                           // Recebe o tempo de duraçao da operaçao.
} Transacao;

/*
 * Função auxiliar para casos de transferências.
 * Inverte do daConta com o paraConta
 */
Transacao* Inverte(Transacao*);

void ImprimeTransacao(Transacao*);

#endif

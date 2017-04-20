#include "comandos.h"
#include "transacao.h"
#include "conta_bancaria.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void
recebeComando(char *comando)
{
    printf("Digite o comando:\n");
    int i = 0;
    char c;

    do {
        scanf("%c", &c);
        if((c == '\n') || (i == CMD_TAM))
            c = '\0';
        comando[i] = c;

        if((comando[i - 1] == ' ') && (c == ' '))                           // Testa excesso de caracteres de espaço.
            i = i;
        else if(c == '\b')
            i = i;
        else if((c == ' ') && (i == 0))                                     // Testa backspace e inicio de comando com espaço.
            i = i;
        else
            i++;
    }
    while(c != '\0');
}

Comando*
trataComando(const char *comando)
{
    int i = 0;                                                              // Guarda a posição de leitura do buffer.
    Comando *cmd = (Comando *) malloc(sizeof(Comando));                     // TAD para guardar informações do comando.
    unsigned int operacao = descobreComando(comando, &i);                   // Recebe o número do comando digitado.
    cmd->operacao = operacao;

    if(operacao == 0)
        printf("Atencao.\n");
    else if(operacao == 1)  {                                               // Criar conta.
        strcpy(cmd->usuario, descobreNome(comando, &i));                    // Guarda o nome do usuário.
        cmd->numeroContaDe = descobreConta(comando, &i);                    // Guarda o número da conta.
        cmd->valor = 0.0;                                                   // Valor inicial = 0.
        cmd->numeroContaPara = CONTA_VAZIA;                                 // Valor nulo para conta.
    }
    else if(operacao == 4)   {                                              // Transferência.
        cmd->numeroContaDe = descobreConta(comando, &i);                    // Guarda o número da conta remetente.
        cmd->numeroContaPara = descobreConta(comando, &i);                  // Guarda o número da conta destinatária.
        cmd->valor = descobreValor(comando, &i);                            // Guarda o valor da transferência.
        strcpy(cmd->usuario, "\0");                                         // Guarda nome nulo.
    }
    else if(operacao == 5)   {                                              // Listagem.
        cmd->numeroContaPara = descobreTipo(comando, &i);                   // Define o tipo de listagem. (-1=valor, -2=data)
        cmd->numeroContaDe = descobreConta(comando, &i);                    // Guarda o número da conta.
        cmd->valor = 0.0;                                                   // Valor nulo.
        strcpy(cmd->usuario, "\0");                                         // Guarda nome nulo.
    }
    else    {                                                               // Saque ou Depósito.
        cmd->numeroContaDe = descobreConta(comando, &i);                    // Guarda o número da conta remetente.
        cmd->numeroContaPara = CONTA_VAZIA;                                 // Valor nulo para conta.
        cmd->valor = descobreValor(comando, &i);                            // Guarda o valor da transação.
        strcpy(cmd->usuario, "\0");                                         // Guarda nome nulo.
    }

    return cmd;
}    

unsigned int
descobreComando(const char *comando, int *i)
{
    *i = 0;
    for(*i = 0; (*i <= OPE_MAX) && (comando[*i] != ' '); (*i)++);           // Encontra comando até SPACE caracter.
    
    //  Compara com comandos existentes //
    int operacao = 0;
    if(!strncmp(comando, "criarconta", *i))
        operacao = 1;                                                       // 1 = criaconta.
    else if(!strncmp(comando, "deposito", *i))
        operacao = 2;                                                       // 2 = deposito.
    else if(!strncmp(comando, "saque", *i))
        operacao = 3;                                                       // 3 = saque.
    else if(!strncmp(comando, "transfere", *i))
        operacao = 4;                                                       // 4 = transferencia.
    else if(!strncmp(comando, "liste", *i))
        operacao = 5;                                                       // 5 = liste.
    else
        operacao = 0;                                                       // 0 = não existe.

    while((*i < CMD_TAM) && (comando[*i] == ' '))                           // Encontra o próximo caracter (não SPACE).
        (*i)++;

    return operacao;
}       

char*
descobreNome(const char *comando, int *i)
{
    char *usuario = (char *) malloc(USU_MAX * sizeof(char));                // Cria espaço para guarda nome do usuário.

    int j;
    for(j = 0; (j < USU_MAX) && (comando[*i] != ' '); j++)
        usuario[j] = comando[(*i)++];
    usuario[j + 1] = '\0';

    while((*i < CMD_TAM) && (comando[*i] == ' '))                           // Encontra o próximo caracter (não SPACE).
        (*i)++;
    
    return usuario;
}

int
descobreConta(const char *comando, int *i)
{
    char numero[CON_MAX];                                                   // Guarda a conta em formato de texto.

    int j;
    for(j = 0; (j < CON_MAX) && (comando[*i] != ' '); j++)
        numero[j] = comando[(*i)++];
    numero[j + 1] = '\0';

    while((*i < CMD_TAM) && (comando[*i] == ' '))                           // Encontra o próximo caracter (não SPACE).
        (*i)++;
    
    return atoi(numero);
}

double
descobreValor(const char *comando, int *i)
{
    char valor[VAL_MAX];                                                    // Cria espaço para guardar o valor.

    int j;
    for(j = 0; (j < VAL_MAX) && (comando[*i] != ' '); j++)
        valor[j] = comando[(*i)++];
    valor[j + 1] = '\0';

    return atof(valor);
}

int
descobreTipo(const char *comando, int *i)
{
    char tipo[TIP_MAX];                                                     // Cria espaço para guardar o tipo.

    int j;
    for(j = 0; (j < TIP_MAX) && (comando[*i] != ' '); j++)
        tipo[j] = comando[(*i)++];
    tipo[j] = '\0';

    while((*i < CMD_TAM) && (comando[*i] == ' '))                           // Encontra o próximo caracter (não SPACE).
        (*i)++;

    if(!strcmp(tipo, "valor"))
        j = -1;                                                             // Tipo = valor = -1.
    else if(!strcmp(tipo, "data"))
        j = -2;                                                             // Tipo = data = -2.
    else    {
        printf("Utilização: liste \"data ou valor\"\n");
        j = 0;
    }

    while((*i < CMD_TAM) && (comando[*i] == ' '))                           // Encontra o próximo caracter (não SPACE).
        (*i)++;
    
    return j;
}

void
geraComandos(FILE *file, unsigned int n)
{
    //  Cria n comandos criarconta  //
    for(int i = 0; i < n; i++)
        fprintf(file, "criarconta %s %d\n", "teste", (i + 1));

    //  Cria n comandos deposito  //
    for(int i = 0; i < n; i++)
        fprintf(file, "deposito %d %lf\n", (i + 1), (double) (i % 1000));

    //  Cria n comandos saque  //
    for(int i = 0; i < n; i++)
        //fprintf(file, "saque %d %lf\n", (i + 1), (double) (i % 1000));
        fprintf(file, "saque %d %lf\n", (i + 1), (double) (1000 % (i + 1)));

    //  Cria n comandos transfere  //
    for(int i = 0; i < n; i++)
        fprintf(file, "transfere %d %d %lf\n", (i + 1), (n - 1 - i), 
            (double) (i % 1000));

    //  Cria n comandos liste data  //
    for(int i = 0; i < n; i++)
        fprintf(file, "liste data %d\n", (i + 1));

    //  Cria n comandos liste valor  //
    for(int i = 0; i < n; i++)
        fprintf(file, "liste valor %d\n", (i + 1));

    fprintf(file, "sair\n");
}

void
criarconta(Lista *contas, const char *usuario, const int numero)
{
    //  Verifica se o numero de conta já existe //
    Lista *posicao = NULL;
    if(existeConta(contas, numero, &posicao)) {
        printf("Número de conta já existente.");
        return;
    }

    ContaBancaria *nova = NovaConta(numero, 0.0);                                       // Cria a nova conta.
    nova->extrato = criaExtrato();                                                      // Cria o extrato da nova conta.
    insereLista(contas, nova);
}

void
depositoOuSaque(Lista *contas, const int numero, const double valor, const int option)
{
    //  Verifica se o numero de conta já existe //
    Lista *posicao = NULL;
    if(!(existeConta(contas, numero, &posicao))) {
        printf("Conta inexistente.");
        return;
    }

    Transacao *transacao = NULL;
    if(!option)                                                                         // Depósito.
        transacao = Deposito(&(posicao->conta), valor);
    else if(option)                                                                     // Saque.
        transacao = Saque(&(posicao->conta), valor);
    else
        return;

    insereNodeData(transacao, posicao->conta.extrato);
}    

void 
transferencia(Lista *contas, const int daConta, const int paraConta, const double valor)
{
    //  Verifica se o numero de daConta já existe //
    Lista *posicaoDe = NULL;
    if(!(existeConta(contas, daConta, &posicaoDe))) {
        printf("Conta inexistente.");
        return;
    }
    //  Verifica se o numero de paraConta já existe //
    Lista *posicaoPara = NULL;
    if(!(existeConta(contas, paraConta, &posicaoPara))) {
        printf("Conta inexistente.");
        return;
    }
    Transacao *transacao = Transferencia(&(posicaoDe->conta), &(posicaoPara->conta), valor);
    insereNodeData(transacao, posicaoDe->conta.extrato);

    transacao = Inverte(transacao);
    insereNodeData(transacao, posicaoPara->conta.extrato);
}

void
imprimeExtrato(Lista *contas, const int numero, const int tipo)
{
    //  Verifica se o numero de daConta já existe //
    Lista *posicao = NULL;
    if(!(existeConta(contas, numero, &posicao))) {
        printf("Conta inexistente.");
        return;
    }
    if(tipo == -2)                                                                      // Listar por data.
        imprimeLista(posicao->conta.extrato);
    else
        insereNodeValor(posicao->conta.extrato);
}


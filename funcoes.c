#include "funcoes.h"
#include "conta_bancaria.h" 
#include "transacao.h" 

void
interpretaComando(const char *buffer)
{
    char comando[MAX_CMD];                                                          // Vetor que guarda o comando digitado.
    int i = 0;                                                                      // Aponta posiçao do caracter no buffer.

    /*  Define o comando    */
    for(i = 0; buffer[i] != ' '; i++)
        comando[i] = buffer[i];                                                     
    comando[i] = '\0';                                                              // Encerra o comando.

    switch(comando) {
        case "criarconta":
            //
            break;
        case "deposito":
            //
            break;
        case "saque":
            //
            break;
        case "transfere":
            //
            break;
        default:
            //
            break;
    }

    return;
}

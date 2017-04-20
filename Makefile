CC = gcc
CFLAGS = -Wall -pedantic

all: comandos transacao conta_bancaria main clean

comandos: comandos.c conta_bancaria.o 
	$(CC) $(CFLAGS) -c comandos.c

conta_bancaria: conta_bancaria.c transacao.o
	$(CC) $(CFLAGS) -c conta_bancaria.c

transacao: transacao.c conta_bancaria.o
	$(CC) $(CFLAGS) -c transacao.c

main: transacao.o conta_bancaria.o comandos.o
	$(CC) main.c $(CFLAGS) transacao.o conta_bancaria.o comandos.o -o banco 

clean:
	-rm -f *.o

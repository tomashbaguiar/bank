CC = gcc
CFLAGS = -Wall
LDFLAGS =

all: lista conta_bancaria transacao main clean

lista: lista.c
	$(CC) $(FLAGS) -c lista.c

conta_bancaria: conta_bancaria.c transacao.o lista.o
	$(CC) $(FLAGS) -c conta_bancaria.c

transacao: transacao.c conta_bancaria.o
	$(CC) $(FLAGS) -c transacao.c

main: transacao.o conta_bancaria.o
	$(CC) main.c $(CFLAGS) lista.o transacao.o conta_bancaria.o -o main 

clean:
	-rm -f *.o

CC = gcc
CFLAGS = -Wall
LDFLAGS =

all: conta_bancaria transacao main clean

conta_bancaria: conta_bancaria.c transacao.o
	$(CC) $(FLAGS) -c conta_bancaria.c

transacao: transacao.c conta_bancaria.o
	$(CC) $(FLAGS) -c transacao.c

main: transacao.o conta_bancaria.o
	$(CC) main.c $(CFLAGS) transacao.o conta_bancaria.o -o main 

clean:
	-rm -f *.o

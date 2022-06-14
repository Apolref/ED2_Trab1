all : exec

run:
	./exec

clean:
	rm -f *.o
	rm -f exec

main.o : main.c
	gcc -o main.o -c main.c

contagem_intersecoes.o : contagem_intersecoes.c
	gcc -o contagem_intersecoes.o -c contagem_intersecoes.c

CtrlF.o : CtrlF.c
	gcc -o CtrlF.o -c CtrlF.c

matriz.o : matriz.c
	gcc -o matriz.o -c matriz.c

Ordena.o : Ordena.c
	gcc -o Ordena.O -c Ordena.c

exec : main.o contagem_intersecoes.o CtrlF.o matriz.o Ordena.o
	gcc -o exec main.o contagem_intersecoes.o CtrlF.o matriz.o Ordena.o
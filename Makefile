all: tp.o hash.o indiceInvertido.o
	@gcc tp.o hash.o indiceInvertido.o -o exe -Wall
	@rm -r *.o
tp.o: tp.c
	@gcc tp.c -c -Wall
indiceInvertido.o: indiceInvertido.c
	@gcc indiceInvertido.c -c -Wall
hash.o: hash.c
	@gcc hash.c -c -Wall
run:
	@./exe

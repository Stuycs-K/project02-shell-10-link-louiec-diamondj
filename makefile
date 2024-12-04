compile: main.o parse.o redirection.o
	@gcc -o shell main.o parse.o redirection.o
main.o: main.c
	@gcc -c main.c
parse.o: parse.c parse.h
	@gcc -c parse.c parse.h
redirection.o: redirection.c redirection.h
	@gcc -c redirection.c
clean:
	rm -f *.o
	rm -f *.gch
	rm -f shell

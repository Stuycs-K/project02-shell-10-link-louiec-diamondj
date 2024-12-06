<<<<<<< HEAD
compile: main.o parse.o pipe.o directory.o redirection.o
	@gcc -o shell main.o parse.o directory.o redirection.o pipe.o
main.o: main.c parse.h directory.h redirection.h pipe.h
	@gcc -c main.c
parse.o: parse.c
	@gcc -c parse.c
directory.o: directory.c
	@gcc -c directory.c
redirection.o: redirection.c
	@gcc -c redirection.c
pipe.o: pipe.c
	@gcc -c pipe.c
=======
compile: main.o parse.o redirection.o
	@gcc -o shell main.o parse.o redirection.o
main.o: main.c
	@gcc -c main.c
parse.o: parse.c parse.h
	@gcc -c parse.c parse.h
redirection.o: redirection.c redirection.h
	@gcc -c redirection.c
>>>>>>> cc2bca5598c5c5dbfe4c61cfb4da35219dafb246
clean:
	rm -f *.o
	rm -f *.gch
	rm -f shell

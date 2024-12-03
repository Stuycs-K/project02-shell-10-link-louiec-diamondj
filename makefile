compile: main.o parse.o
	@gcc -o shell main.o parse.o
main.o: main.c
	@gcc -c main.c
parse.o: parse.c parse.h
	@gcc -c parse.c parse.h
clean:
	rm *.o
	rm *.gch
	rm shell

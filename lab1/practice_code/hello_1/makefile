all: main hello
	gcc main.o hello.o -o main

main: main.c hello.h
	gcc -c main.c

hello: hello.c hello.h
	gcc -c hello.c

clean:
	rm -f *.o main
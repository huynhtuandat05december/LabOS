all: shell command
	gcc my_shell.o parse_command.o -o myShell

shell: my_shell.c parse_command.h
	gcc -c my_shell.c

command:parse_command.c parse_command.h
	gcc -c parse_command.c

clean:
	rm -f *.o main

all: fork_shell parse_comm
	gcc fork_shell.o parse_comm.o -o forkShell

parse_comm: parse_command.c parse_command.h
	gcc -c -o parse_comm.o parse_command.c

fork_shell: fork_shell.c parse_command.h
	gcc -c fork_shell.c

clean:
	rm -f *.o forkShell
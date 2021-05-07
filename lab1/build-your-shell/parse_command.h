#ifndef PARSE_COMMAND_H
#define PARSE_COMMAND_H

#define MAX_ARG_LENGTH 1024
#define MAX_NUM_ARG 32
#define MAX_INPUT_SIZE 64


/*
 * parse_command(char*) return a pointer to an array including a command and agurments in string
 * e.g. parse_command("echo Hello_World") will return a pointer to ["echo", "Hello_World"] 
 */ 
char **parse_command(char *line);

#endif
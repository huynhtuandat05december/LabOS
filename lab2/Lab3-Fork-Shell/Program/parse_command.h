#ifndef PARSE_COMMAND_H
#define PARSE_COMMAND_H

#define MAX_ARG_LENGTH 1024
#define MAX_NUM_ARG 32
#define MAX_NUM_COMM 32
#define MAX_INPUT_SIZE MAX_ARG_LENGTH*MAX_NUM_ARG*MAX_NUM_COMM

#define SEQUENTIAL_COMM ';'
#define BACKGROUND_COMM '&'
#define SEQUENTIAL_BACKGROUND_COMM '*'
#include <stdbool.h>

/*
 * parse_command(char*) return a pointer to an array including a command and agurments in string
 * e.g. parse_command("echo Hello_World") will return a pointer to ["echo", "Hello_World"] 
 */ 

char ***parse_command(char* line, char* type);
bool execute_command(char** tokens);

#endif
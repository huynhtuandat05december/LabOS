#include "parse_command.h"
#include <stdlib.h>
#include <string.h>

/*
 * parse_command(char*) return a pointer to an array including a command and agurments in string
 * e.g. parse_command("echo Hello_World") will return a pointer to ["echo", "Hello_World"] 
 */ 
char **parse_command(char *line)
{
    char **tokens = (char **)malloc(MAX_NUM_ARG * sizeof(char *));
    char *tmp = (char *)malloc(MAX_ARG_LENGTH * sizeof(char));
    int count = 0;

    tmp = strtok(line, " ");
    while(tmp != NULL){
        tokens[count] = (char*)malloc(MAX_ARG_LENGTH*sizeof(char));
        strcpy(tokens[count], tmp);
        tmp = strtok(NULL, " \n\t\r");
        count += 1;
    }
    tokens[count] = NULL;

    // handle error of strtok when calling just once
    if (count == 1){
        tokens[0][strlen(tokens[0]) - 1] = '\0';
    }

    free(tmp);
    return tokens;
}

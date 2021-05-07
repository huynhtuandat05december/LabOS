#include "parse_command.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

/*
 * parse_command(char*) return a pointer to an array including a command and agurments in string
 * e.g. parse_command("echo Hello_World") will return a pointer to ["echo", "Hello_World"] 
 */ 
char ***parse_command(char* line, char* type)
{  
    if (strcmp(line, "\n") == 0){
        return NULL;
    }
    // get type of the combination of commands
    char tmp_str[MAX_NUM_COMM * MAX_ARG_LENGTH * MAX_NUM_ARG] = "";
    strcpy(tmp_str, line);
    if (strchr(tmp_str, SEQUENTIAL_COMM) != NULL){
        *type = SEQUENTIAL_COMM;
    }
    else if (strchr(tmp_str, BACKGROUND_COMM) != NULL){
        *type = BACKGROUND_COMM;
    }
    else if (strchr(tmp_str, SEQUENTIAL_BACKGROUND_COMM) != NULL){
        *type = SEQUENTIAL_BACKGROUND_COMM;
    }
    else{
        *type = '\0';
    }
    char str_type[2]; str_type[0] = *type; str_type[1] = '\0';

    // split to list of string based on the type of combination
    char list_string[MAX_NUM_COMM][MAX_NUM_ARG * MAX_ARG_LENGTH];
    char* tmp_ = NULL;
    tmp_ = strtok(line, str_type);
    int counter_ = 0;
    while(tmp_ != NULL){
        strcpy(list_string[counter_], tmp_);
        counter_ += 1;
        tmp_ = strtok(NULL, str_type);
    }
    strcpy(list_string[counter_], "\0");
        
    // split to list of tokens of commands
    char ***commands = (char ***)malloc(MAX_NUM_COMM * sizeof(char **));
    for (counter_ = 0, tmp_ = NULL; strcmp(list_string[counter_], "\0") != 0;  counter_++){
        strcpy(tmp_str, list_string[counter_]);
        commands[counter_] = (char **)malloc(MAX_NUM_ARG * sizeof(char *));
        // handle a command
        char *tmp_c_;
        int count_c_ = 0;
        tmp_c_ = strtok(tmp_str, " \n\t\r");
        while(tmp_c_ != NULL){
            commands[counter_][count_c_]= (char*)malloc(MAX_ARG_LENGTH*sizeof(char));
            strcpy(commands[counter_][count_c_], tmp_c_);
            tmp_c_ = strtok(NULL, " \n\t\r");
            count_c_ += 1;
        }
        commands[counter_][count_c_] = NULL;
    }

    commands[counter_] = NULL;

    return commands;
}

bool execute_command(char** tokens){
    if (strcmp(tokens[0], "echo") == 0){
        for (int i = 1; tokens[i] != NULL; i++){
            printf("%s ", tokens[i]);
        }
        printf("\n");
        return true;
    }
    else if (strcmp(tokens[0], "sleep") == 0){
        int length = 0;
        length = atoi(tokens[1]);
        sleep(length);
        printf("waked after sleepping for %d seconds\n", length);
        return true;
    }
    return false;
}
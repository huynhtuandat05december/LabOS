#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include "parse_command.h"
#define MY_PROMPT "My Shell>$ "
static int a = 0;
int main(void)
{
    char line[MAX_INPUT_SIZE];
    char **tokens;
    int i;

    while (1)
    {
        printf(MY_PROMPT);
        bzero(line, MAX_INPUT_SIZE);
        if (fgets(line, sizeof(line), stdin) == NULL)
        {
            printf("\n");
            break;
        }

        tokens = parse_command(line);

        /*
        * ========================================================================+
        * Write your code here
        * 
        * ========================================================================+
        */

        // !! Comment two below lines after you successfully write Makefile
        // !! Comment two below lines after you successfully write Makefile
        // for (i = 0; tokens[i] != NULL; i++)
        //     printf("found token: %s\n", tokens[i]);
        if (strcmp(tokens[0], "whoami") == 0)
        {
            printf("My Id is %d\n", 1913026);
        }
        if (strcmp(tokens[0], "counter") == 0)
        {
            printf("Counter has been called %d times\n", ++a);
        }
        if (strcmp(tokens[0], "echo") == 0)
        {
            printf("%s %s\n", tokens[1], tokens[2]);
        }
        if (strcmp(tokens[0], "cat") == 0)
        {
            FILE *fp;
            char *line = NULL;
            size_t len = 0;
            ssize_t read;

            fp = fopen(tokens[1], "r");
            if (fp == NULL)
                exit(EXIT_FAILURE);

            while ((read = getline(&line, &len, fp)) != -1)
            {
                printf("%s", line);
            }
            printf("\n");

            fclose(fp);
        }
        if (strcmp(tokens[0], "ls") == 0)
        {
            DIR *folder;
            struct dirent *entry;

            folder = opendir(".");
            if (folder == NULL)
            {
                perror("Unable to read directory");
                return (1);
            }
            while ((entry = readdir(folder)))
            {
                if (entry->d_name[0] != '.' && entry->d_name[strlen(entry->d_name) - 1] != '~')
                {
                    printf("%s", entry->d_name);
                    break;
                }
            }
            while ((entry = readdir(folder)))
            {
                if (entry->d_name[0] != '.' && entry->d_name[strlen(entry->d_name) - 1] != '~')
                {
                    printf(" %s", entry->d_name);
                }
            }
            printf("\n");

            closedir(folder);
        }
        if (strcmp(tokens[0], "quit") == 0)
        {
            exit(0);
        }
        if (strcmp(tokens[0], "sleep") == 0)
        {
            int time = atoi(tokens[1]);
            sleep(time);
        }

        /* Free the allocated memory */
        for (i = 0; tokens[i] != NULL; i++)
            free(tokens[i]);

        free(tokens);
    }

    return 0;
}

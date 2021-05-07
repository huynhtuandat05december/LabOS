#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include "parse_command.h"
#include <unistd.h>
#include <sys/wait.h>

#define MY_PROMPT "Fork Shell>$ "

int main(void)
{
    char line[MAX_INPUT_SIZE];
    char ***commands = NULL;
    char type;
    int i, counter = 0;

    while (1)
    {
        printf(MY_PROMPT);
        bzero(line, MAX_INPUT_SIZE);
        if (fgets(line, sizeof(line), stdin) == NULL)
        {
            printf("\n");
            break;
        }

        /* similarly to lab 2:
            For example the input is: "ls; sleep 4; echo abc xyz"
            with parse_command function you will get {
                type: ';'
                commands -> [
                                ["ls", NULL],
                                ["sleep", "4", NULL],
                                ["echo", "abc", "xyz", NULL],
                                NULL
                            ]
            }
        */
        commands = parse_command(line, &type);
        if (commands == NULL)
        {
            continue;
        }
        // type == '\0' => only one command == lab 2
        if (type == '\0')
        {
            char **tokens = commands[0];
            if (!execute_command(commands[0]))
            {
                if (strcmp(commands[0][0], "tree") == 0)
                {
                    printf("My PID is %d \n", getpid());
                    pid_t pidB, pidE, pidD, pidF, pidC, pidG, pidI;
                    pidB = fork();
                    if (pidB == 0)
                    {
                        printf("My PID is %d, My parent's PID is %d \n", getpid(), getppid());
                        pidE = fork();
                        if (pidE == 0)
                        {
                            printf("My PID is %d, My parent's PID is %d \n", getpid(), getppid());
                            exit(1);
                        }
                        else if (pidE > 0)
                        {
                            wait(NULL);
                            pidF = fork();
                            if (pidF == 0)
                            {
                                printf("My PID is %d, My parent's PID is %d \n", getpid(), getppid());
                                exit(1);
                            }
                            else if (pidF > 0)
                            {
                                wait(NULL);
                                exit(1);
                            }
                        }
                    }
                    else if (pidB > 0)
                    {
                        wait(NULL);
                        pidC = fork();
                        if (pidC == 0)
                        {
                            printf("My PID is %d, My parent's PID is %d \n", getpid(), getppid());
                            pidG = fork();
                            if (pidG == 0)
                            {
                                printf("My PID is %d, My parent's PID is %d \n", getpid(), getppid());
                                pidI = fork();
                                if (pidI == 0)
                                {
                                    printf("My PID is %d, My parent's PID is %d \n", getpid(), getppid());
                                    exit(1);
                                }
                                else if (pidI > 0)
                                {
                                    wait(NULL);
                                    exit(1);
                                }
                            }
                            else if (pidG > 0)
                            {
                                wait(NULL);
                                exit(1);
                            }
                        }
                        else if (pidC > 0)
                        {
                            wait(NULL);
                            pidD = fork();
                            if (pidD == 0)
                            {
                                printf("My PID is %d, My parent's PID is %d \n", getpid(), getppid());
                            }
                            else if (pidD > 0)
                            {
                                wait(NULL);
                                exit(1);
                            }
                        }
                    }
                    // wait(NULL);
                }
            }
        }
        else if (type == SEQUENTIAL_COMM)
        {
            int i = 0;
            char **tokens = commands[i];
            while (tokens != NULL)
            {
                execute_command(tokens);
                i++;
                tokens = commands[i];
            }
        }

        else if (type == BACKGROUND_COMM)
        {
            int i = 0;
            char **tokens = commands[i];
            while (tokens != NULL)
            {
                switch (fork())
                {
                case 0:
                {
                    execute_command(tokens);
                    exit(0);
                    break;
                }
                case -1:
                {
                    perror("fork");
                    exit(1);
                    break;
                }
                default:
                {
                    break;
                }
                }
                i++;
                tokens = commands[i];
            }
        }

        else if (type == SEQUENTIAL_BACKGROUND_COMM)
        {
            pid_t child_pid, wpid;
            int status = 0;

            //Father code (before child processes start)
            int i = 0;
            char **tokens = commands[i];
            while (tokens != NULL)
            {
                if ((child_pid = fork()) == 0)
                {
                    execute_command(tokens);
                    exit(0);
                }
                i++;
                tokens = commands[i];
            }

            while ((wpid = wait(&status)) > 0)
                ;
        }

        /* Free the allocated memory */
        for (int i = 0; commands[i] != NULL; i++)
            for (int j = 0; commands[i][j] != NULL; j++)
                free(commands[i][j]);
        free(commands[i]);
        free(commands);
    }

    printf("Free memory... Quit.. (This line should be printed only one time!)\n");
    return 0;
}

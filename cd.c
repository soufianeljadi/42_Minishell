#include "minishell.h"

void execute_cd(char *path)
{
    if (chdir(path) != 0)
        perror("cd");
}

void execute_command(char *command)
{
    if (strncmp(command, "cd ", 3) == 0)
        execute_cd(command + 3);
    else if (strcmp(command, "exit") == 0)
        exit(0);
}

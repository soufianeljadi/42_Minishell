#include "minishell.h"


int exit_stat(int stat)
{
    static int var;

    if (stat != -1)
        var = stat;
    return (var);
}


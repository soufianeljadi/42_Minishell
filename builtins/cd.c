/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:00:00 by sdiouane          #+#    #+#             */
/*   Updated: 2024/03/25 17:00:07 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 23:52:10 by sdiouane          #+#    #+#             */
/*   Updated: 2024/03/13 01:05:23 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main()
{
    t_sep *cmd = NULL;
    t_sep *tmp= NULL;
    char *command;
    char **str;
    int i = 0;
    
    while (1)
    {

        command = readline("minishell :$ ");
        if (!command) {
            // Error or EOF while reading input
            break;
        }
        str = ft_split(command, ';');
        tmp = cmd;
        while (str[i])
        {
		    ft_lstadd_back(&cmd, ft_lstnew(str[i]));
            i++;
        }
        cmd->next=NULL;
        // printf("hgere\n");
        while (tmp)
        {
            printf("%s\n", tmp->cmd_sep);
            tmp = tmp->next;
        }
        // print_list(tmp);
        // Check for exit command
        if (strcmp(command, "exit") == 0) {
            free(command);
            break;
        }

        // Execute the command
        // pid_t pid = fork();
        // if (pid == -1) {
        //     perror("fork");
        // } else if (pid == 0) {  // Child process
        //     execlp(command, command, NULL);
        //     perror("exec");
        //     exit(EXIT_FAILURE);
        // } else {  // Parent process
        //     waitpid(pid, NULL, 0);
        // }

        free(command);
    }
    return 0;
}

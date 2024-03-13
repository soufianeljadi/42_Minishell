/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 23:52:10 by sdiouane          #+#    #+#             */
/*   Updated: 2024/03/13 20:24:24 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char **env)
{
    ((void)ac, (void)av);
    (void)env;
    // t_sep *cmd = NULL;
    // t_sep *tmp= NULL;
    // char **str;
    // int i = 0;
    char *line;
    
    while (1)
    {
        /***********************************Read line*/
        if((readline("minishell :$ ")) != NULL)
        {
            line = readline("minishell :$ ");
            if (!line)
                break;
        }
        // str = ft_split(line, ';');
        // tmp = cmd;
        // while (str[i])
        // {
		//     ft_lstadd_back(&cmd, ft_lstnew(str[i]));
        //     i++;
        // }
        // cmd->next=NULL;
        // // printf("hgere\n");
        // while (tmp)
        // {
        //     printf("%s\n", tmp->cmd_sep);
        //     tmp = tmp->next;
        // }
        // print_list(tmp);
        /***********************************History*/
        add_history(line);
        /***********************************Check for exit cmd*/
        if (strcmp(line, "exit") == 0) {
            free(line);
            break;
        }
        /***********************************Execute the cmd*/
        // pid_t pid = fork();
        // if (pid == -1) {
        //     perror("fork");
        // } else if (pid == 0) {  // Child process
        //     execlp(line, line, NULL);
        //     perror("exec");
        //     exit(EXIT_FAILURE);
        // } else {  // Parent process
        //     waitpid(pid, NULL, 0);
        // }
        free(line);
    }
    return 0;
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 23:52:10 by sdiouane          #+#    #+#             */
/*   Updated: 2024/03/20 23:43:46 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void init_env(char **env)
{
	s_env *lst = NULL;
	lst->env = env;
}

int only_spaces(char *str)
{
	int i = 0;
	while(str[i])
	{
		if(str[i] == ' ' || str[i] == '\t')
			i++;
		else
			return (0);	
	}
	return(1);
}


int main(int ac, char **av, char **env)
{
	((void)ac, (void)av);
	(void)env;	
	char *line = NULL;
	Token **token;
	while (1)
	{  
		if((line = readline("Minishell :$ "))!= NULL  && only_spaces(line) == 0)
		{
			if (!line)
			    break;
			add_history(line);
			if(parsing(line) == 1)		
				syntax_error();
			else
			{
				token = parse_command(line);
				print_tokens(token);
			}
			if (strncmp(line, "exit", 4) == 0)
			{
				printf("exit\n");
				free(line);
				break;
			}
	// Execute the cmd :
			// pid_t pid = fork();
			// if (pid == -1) {
			// 	perror("fork"); 
			// } else if (pid == 0) {  // Child process
			// 	execlp(line, line, NULL);
			// 	perror("exec");
			// 	exit(EXIT_FAILURE);
			// }
			// else // Parent process
			// 	waitpid(pi
		}
		free(line);
	}
	return 0;
}

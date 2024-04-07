/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jadi <sel-jadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 22:14:48 by sdiouane          #+#    #+#             */
/*   Updated: 2024/04/07 23:27:38 by sel-jadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	execute(char *s, char **env)
{
	char	*chemin;
	char	**cmd;
	if (*env)
	{
	cmd = ft_split(s, ' '); // ls -la 
	chemin = get_path(cmd[0], env); // /bin/kkk/ls
	if (execve(chemin, cmd, env) == -1)
	{
		ft_putstr_fd("Command not found!!", 2);
		ft_putendl_fd(cmd[0], 2);
		ft_free_tab(cmd);
		exit(EXIT_FAILURE);
	}
	}
}

void ft_execution(noued_cmd *lst, char **args, s_env *env_, char **env, s_env *env_i)
{
	(void)env_;
	(void)args;
	int pipefd[2];
	int fd_in = 0;
	pid_t pid;

	if (!strcmp(args[0], "export") || !strcmp(args[0], "unset") || !strcmp(args[0], "env") || !strcmp(args[0], "echo") || !strcmp(args[0], "cd") || !strcmp(args[0], "exit") || !strcmp(args[0], "pwd"))
		builtins(args, env_, env_i, env);
	else
	{
		while (lst)
		{
			// $variables :
			if (check_variables(args, env_) == 1)
			{
				if (pipe(pipefd) == -1 || (pid = fork()) == -1)
					exit(EXIT_FAILURE);
				else if (pid == 0)
				{
					if (lst->next != NULL)
					{
						dup2(pipefd[1], STDOUT_FILENO);
						close(pipefd[1]);
					}
					close(pipefd[0]);
					if (lst->redirection != NULL)
						execute_with_redirection(lst->cmd, env, lst->redirection);
					else
						execute(lst->cmd, env);
				}
				else
				{
					close(pipefd[1]);
					fd_in = pipefd[0];
					close(pipefd[0]);
				}
			}
			else
				printf("\n");
			lst = lst->next;
		}
	}
	while (0 < wait(NULL))
		;
}

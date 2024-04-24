/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 22:14:48 by sdiouane          #+#    #+#             */
/*   Updated: 2024/04/24 11:09:11 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *here_doc_fct(char *s)
{
	int fd1;
	int fd2;
	char *line;
	char *cmp;
	char **args;
	char *res;

	args = line_to_args(s);
	if (args[1][0] == '<' && args[1][1] == '<')
	{
			printf("CMD   : %s\n", args[0]);
		fd1 = open("file.txt",O_CREAT | O_RDWR | O_TRUNC, 0666);
		fd2 = open("file.txt",O_CREAT | O_RDWR | O_TRUNC, 0666);
		
		if (fd1 < 0 && fd2 < 0)
			return (NULL);
		cmp = ft_strjoin(args[2], "\n");
		while ((line = get_next_line(0)))
		{
			if (!strcmp(line, cmp))
			{
				free(line);
				break;
			}
			write(fd1, line, strlen(line));		
			free(line);
		}
		if (args[3][0] != '\0')
		{
			printf("%s: %s: No such file or directory\n", args[0], args[3]);
			exit(EXIT_FAILURE);
		}
		else
		{
			dup2(fd2, 0);
			return (args[0]);
		}
	}
	else if (args[0][0] == '<' && args[0][1] == '<')
	{
		fd1 = open("file.txt",O_CREAT | O_RDWR | O_TRUNC, 0666);
		fd2 = open("file.txt",O_CREAT | O_RDWR | O_TRUNC, 0666);
		
		if (fd1 < 0 && fd2 < 0)
			return (NULL);
		cmp = ft_strjoin(args[1], "\n");
		while ((line = get_next_line(0)))
		{
			if (!strcmp(line, cmp))
			{
				free(line);
				break;
			}
			write(fd1, line, strlen(line));		
			free(line);
		}
		if (args[2][0] != '\0')
		{
			printf("%s: %s: No such file or directory\n", args[0], args[2]);
			exit(EXIT_FAILURE);
		}
		else
		{
			dup2(fd2, 0);
			return (args[0]);
		}
	}
	free(args[1]);
	res = ft_strjoin(args[0], " ");
	res = ft_strjoin(res, args[2]);
	printf("RES   : %s\n", res);
	return (res);
}

static void	execute(char *s, char **env)
{
	char	*chemin;
	char	**cmd = NULL;
	char	*res = NULL;
	if (*env)
	{
		if (strstr(s, "<<"))
			res = here_doc_fct(s);
		cmd = ft_split(s, ' '); // ls -la 
		chemin = get_path(cmd[0], env); // /bin/kkk/ls
		if (execve(chemin, cmd, env) == -1)
		{
			fprintf(stderr,"Command not found !\n");
			ft_free_tab(cmd);
			exit(EXIT_FAILURE);
		}
	}
}

void ft_execution(noued_cmd *lst, char **args, s_env *env_, char **env, s_env *env_i, s_env *export_i)
{
	(void)env_;
	(void)args;
	int pipefd[2];
	int fd_in = 0;
	pid_t pid;

	if (!strcmp(args[0], "export") || !strcmp(args[0], "unset") || !strcmp(args[0], "env") || !strcmp(args[0], "echo") || !strcmp(args[0], "cd") || !strcmp(args[0], "exit") || !strcmp(args[0], "pwd"))
		builtins(args, env_, env_i, export_i, env);
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
					{
						execute_with_redirection(lst->cmd, env, lst->redirection);
					}
					else
					{
						//ft_pipex();
						execute(lst->cmd, env);
					}
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
			//wait(NULL);
		}
	}
	while (wait(NULL) >= 0)
		;
}



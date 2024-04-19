/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 22:14:48 by sdiouane          #+#    #+#             */
/*   Updated: 2024/04/19 19:39:11 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*here_doc_fct(char *s)
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
		printf("delemt : |%s|\n", args[2]);
		printf("cmd : %s\n", args[0]);
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
		if (args[3])
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
	free(args[1]);
	res = ft_strjoin(args[0], " ");
	res = ft_strjoin(res, args[2]);
	return (res);
}


// char	*double_red_out(char *s)
// {
// 	int i = 0;
// 	int start = 0;
// 	int fd1;
// 	int fd2;
// 	char *cmd;
// 	char *file;
// 	char *line;

// 	while (s[i] != '<' && s[i + 1] != '<')
// 		i++;
// 	cmd = ft_substr(s, 0, i);
// 	while (s[i] == ' ')
// 		i++;
// 	while (s[i] == '<')
// 		i++;
// 	while (s[i] == ' ')
// 		i++;
// 	start = i;
// 	while (s[i] != ' ' && s[i] != '\0')
// 		i++;
// 	file = ft_substr(s, start, i);
// 	printf("file : |%s|\n", file);
// 	printf("cmd : %s\n", cmd);
// 	fd1 = open(file, O_CREAT | O_RDWR | O_APPEND, 0666);
// 	fd2 = open("file.txt",O_CREAT | O_RDWR | O_TRUNC, 0666);
	
// 	if (fd1 < 0 && fd2 < 0)
// 		return (NULL);
// 	while ((line = get_next_line(0)))
// 	{
// 		if (!line)
// 		{
// 			free(line);
// 			break;
// 		}
// 		write(fd1, line, strlen(line));		
// 		free(line);
// 	}
// 	dup2(fd1, 0);
// 	return (cmd);	
// }

static void	execute(char *s, char **env)
{
	char	*chemin;
	char	**cmd;
	if (*env)
	{
		if (strstr(s, "<<"))
		{
			
			s = here_doc_fct(s);
		}
		// else if ((strstr(s, ">>")))
		// {
		// 	s = double_red_out(s);
		// }
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
					// else if (strstr(lst->cmd, "<<"))
					// 	here_doc_fct(lst->cmd);
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


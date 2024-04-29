/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jadi <sel-jadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 22:14:48 by sdiouane          #+#    #+#             */
/*   Updated: 2024/04/28 20:42:44 by sel-jadi         ###   ########.fr       */
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
	if (args[1][0] == '<' && args[1][1] == '<' && args)
	{
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
		// if (args[3])
		// {
		// 	printf("%s: %s: No such file or directory\n", args[0], args[3]);
		// 	exit(EXIT_FAILURE);
		// }
		// else
		// {
			dup2(fd2, 0);
			return (args[0]);
		// }
	}
	else if (args[0][0] == '<' && args[0][1] == '<' && args)
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
		// if (args[2])
		// {
		// 	printf("%s: %s: No such file or directory\n", args[0], args[2]);
		// 	exit(EXIT_FAILURE);
		// }
		// else
		// {
			dup2(fd2, 0);
			return (args[0]);
		// }
	}
	free(args[1]);
	res = ft_strjoin(args[0], " ");
	res = ft_strjoin(res, args[2]);
	return (res);
}

static void	execute(char *s, char **env, s_env **export_i)
{
	char	*chemin;
	char	**cmd = NULL;
	(void)export_i;
	if (*env)
	{
		if (strstr(s, "<<"))
			s = here_doc_fct(s);
		cmd = ft_split(s, ' '); // ls -la 
		supprimerGuillemets(cmd[0]);
		chemin = get_path(cmd[0], env); // /bin/kkk/ls
		if (execve(chemin, cmd, g_flags.envire) == -1)
		{
			// fprintf(stderr,"Command not found !\n");
			fprintf(stderr, "minishell : %s: command not found\n", cmd[0]);
			ft_free_tab(cmd);
			exit(EXIT_FAILURE);
		}
	}
}

void supprimerGuillemets(char *chaine)
{
    int i = 0;
	int j = 0;

    while (chaine[i])
	{
        if (chaine[i] != '"' && chaine[i] != '\'')
            chaine[j++] = chaine[i];
        i++;
    }
    chaine[j] = '\0';
}

void add_last_cmd(s_env **lst, char **args)
{
	int i;
	s_env *tmp;
	
	i = 0;
	tmp = *lst;
	while (args[i])
		i++;
	while (tmp)
	{
		if (!strcmp(tmp->key, "_"))
		{
			// printf("BEFORE -----> KEY : %s\tVALUE : %s\n",tmp->key, tmp->value);
			// if ()
			tmp->value = strdup(args[i - 1]);
			// printf("AFTER  -----> KEY : %s\tVALUE : %s\n",tmp->key, tmp->value);
		}
		tmp = tmp->next;
	}
}
static int	ft_lstsize(s_env *lst)
{
	int		c;
	s_env	*p;

	c = 0;
	p = lst;
	while (p)
	{
		p = p -> next;
		c++;
	}
	return (c);
}
static char	**ft_merge_envr(s_env *export_i)
{
	char	**str;
	int		len;
	int		i;

	i = 0;
	len = ft_lstsize(export_i);
	str = NULL;
	str = malloc(sizeof(char *) * len + 1);
	if (!str)
		return (NULL);
	while (export_i)
	{
		str[i] = ft_strdup("");
		str[i] = ft_strjoin(str[i], export_i->key);
		if (export_i->value)
		{
			str[i] = ft_strjoin(str[i], "=");
			str[i] = ft_strjoin(str[i], export_i->value);
		}
		export_i = export_i->next;
		i++;
	}
	str[i] = NULL;
	return (str);
}
void ft_execution(noued_cmd *lst, char **args, char **env, s_env *export_i, char **null_env)
{
	(void)args;
	int pipefd[2];
	int fd_in = 0;
	pid_t pid;

	g_flags.envire = NULL;
	add_last_cmd(&export_i, args);
	if (!strcmp(args[0], "export") || !strcmp(args[0], "unset") || !strcmp(args[0], "env") || !strcmp(args[0], "echo") || !strcmp(args[0], "cd") || !strcmp(args[0], "exit") || !strcmp(args[0], "pwd"))
		builtins(args, export_i, env);
	else
	{
		while (lst)
		{
			// $variables :
			if (check_variables(args, export_i) == 1)
			{
				g_flags.envire = ft_merge_envr(export_i);
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
					//supprimerGuillemets(lst->cmd);
					if (lst->redirection != NULL)
					{
						if (!env[0])
							execute_with_redirection(lst->cmd, null_env, lst->redirection);
						else
							execute_with_redirection(lst->cmd, env, lst->redirection);
					}
					else
					{
						// if (env[0])
						// 	pipeline(&lst->cmd);
						// else if (!env[0])
						// 	pipeline(lst->cmd);
						//ft_pipex();
						if (env[0])
							execute(lst->cmd, env, &export_i);
						else if (!env[0])
							execute(lst->cmd, null_env, &export_i);
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



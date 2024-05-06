/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 22:14:48 by sdiouane          #+#    #+#             */
/*   Updated: 2024/05/06 13:02:30 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// char *here_doc_fct(char *s)
// {
// 	int fd1;
// 	int fd2;
// 	char *line;
// 	char *cmp;
// 	char **args;
// 	char *res;

// 	args = line_to_args(s);
// 	if (args[1][0] == '<' && args[1][1] == '<' && args)
// 	{
// 		fd1 = open("file.txt",O_CREAT | O_RDWR | O_TRUNC, 0666);
// 		fd2 = open("file.txt",O_CREAT | O_RDWR | O_TRUNC, 0666);
		
// 		if (fd1 < 0 && fd2 < 0)
// 			return (NULL);
// 		cmp = ft_strdup(args[2]);
// 		if (!cmp)
// 			return (NULL);
// 		while ((line = readline("heredoc ->")))
// 		{
// 			if (!strcmp(line, cmp))
// 			{
// 				free(line);
// 				break;
// 			}
// 			write(fd1, line, strlen(line));		
// 			free(line);
// 		}
// 		dup2(fd2, 0);
// 		return (args[0]);
// 	}
// 	else if (args[0][0] == '<' && args[0][1] == '<' && args)
// 	{
// 		fd1 = open("file.txt",O_CREAT | O_RDWR | O_TRUNC, 0666);
// 		fd2 = open("file.txt",O_CREAT | O_RDWR | O_TRUNC, 0666);
		
// 		if (fd1 < 0 && fd2 < 0)
// 			return (NULL);
// 		cmp = ft_strdup(args[1]);
// 		if (!cmp)
// 			return (NULL);
// 		while ((line = readline("heredoc ->")))
// 		{
// 			if (!strcmp(line, cmp))
// 			{
// 				free(line);
// 				break;
// 			}
// 			write(fd1, line, strlen(line));
// 			free(line);
// 		}

// 		dup2(fd2, 0);
// 		return (args[0]);
// 	}
// 	free(args[1]);
// 	res = ft_strjoin(args[0], " ");
// 	res = ft_strjoin(res, args[2]);
// 	return (res);
// }


void execute(char *s, char **env)
{
	char	*chemin;
	char	**cmd = NULL;
	int i = 0;
	if (*env)
	{
		// if (strstr(s, "<<"))
		// 	s = here_doc_fct(s);
		cmd = ft_split(s, ' '); // ls -la 
		while (cmd[i])
			supprimerGuillemets(cmd[i++]);
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
        if (chaine[i] != '"')
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
			tmp->value = strdup(args[i - 1]);
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
	str = malloc(sizeof(char *) * (len + 1));
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

static void handle_child_process(noued_cmd *cmd_node, char **env, char **null_env, int pipefd[], char *redirection)
{
    if (cmd_node->next != NULL)
        dup2(pipefd[1], STDOUT_FILENO);
    close(pipefd[1]);
    close(pipefd[0]);

	(void)redirection;
    if (cmd_node->redirection != NULL)
	{
        char **environment = env[0] ? env : null_env;
        execute_with_redirection(cmd_node->cmd, environment, cmd_node->redirection);
    }
	else
	{
        char **environment = env[0] ? env : null_env;
		// builtins(data->args, data->export_i, data->env);
        execute(cmd_node->cmd, environment);
    }
}

static void handle_parent_process(int pipefd[])
{
    dup2(pipefd[0], STDIN_FILENO);
    close(pipefd[1]);
    close(pipefd[0]);
}

static void execute_child_process(noued_cmd *cmd_node, char **env, char **null_env, char *redirection)
{
    int pipefd[2];
    pid_t pid;

    if (pipe(pipefd) == -1 || (pid = fork()) == -1)
        exit(EXIT_FAILURE);
    else if (pid == 0)
        handle_child_process(cmd_node, env, null_env, pipefd, redirection);
    else
        handle_parent_process(pipefd);
}

static void execute_command(noued_cmd *cmd_node, char **env, char **null_env, char *redirection)
{
    if (!strstr(cmd_node->cmd, "$"))
        execute_child_process(cmd_node, env, null_env, redirection);
	else
        printf("\n");
}

void ft_execution(ExecutionData *data)
{
    add_last_cmd(&data->export_i, data->args);
    if (strcmp(data->args[0], "export") == 0 || strcmp(data->args[0], "unset") == 0 || strcmp(data->args[0], "echo") == 0 || strcmp(data->args[0], "cd") == 0 || strcmp(data->args[0], "env") == 0  || strcmp(data->args[0], "exit") == 0)
		builtins(data->args, data->export_i, data->env);
	else
	{
        while (data->lst)
		{
        	// builtins(data->args, data->export_i, data->env);
			g_flags.envire = ft_merge_envr(data->export_i);
            execute_command(data->lst, data->env, data->null_env, data->lst->redirection);
            data->lst = data->lst->next;
        }
    }
    while (0 < wait(NULL));
}

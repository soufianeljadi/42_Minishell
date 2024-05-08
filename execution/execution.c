/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 22:14:48 by sdiouane          #+#    #+#             */
/*   Updated: 2024/05/08 22:40:31 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void sup(char *chaine)
{
    int i = 0;
	int j = 0;

    while (chaine[i])
	{
        if (chaine[i] != '\'')
            chaine[j++] = chaine[i];
        i++;
    }
    chaine[j] = '\0';
}

void execute(char *s, char **env)
{
	char	*chemin;
	char	**cmd = NULL;
	int i = 0; 

	if (*env)
	{
		if ((((s[0] == '"' || s[0] == '\'') && (strstr(s, " ") || strstr(s, "\t")))))
			cmd = ft_split(s, ' ');
		else
		{
			if (!strcmp(s , ""))
				cmd[0] = strdup(s);
			else
				cmd = split_space_tab(s, ' ');
			if (cmd[0][0] == '\0')
				exit(EXIT_FAILURE);
			if (strstr(cmd[0], "\""))
			{
				while (cmd[i])
					supprimerGuillemets(cmd[i++]);
			}
			else if (strstr(cmd[0], "\'"))
			{
				i = 0;
				while (cmd[i])
					sup(cmd[i++]);
			}
		}
		chemin = get_path(cmd[0], env);
		if (execve(chemin, cmd, g_flags.envire) == -1 && !strstr(cmd[0], "$"))
		{
			// perror(errno);
			fprintf(stderr, "minishell : %s %s\n", cmd[0], strerror(errno));
			ft_free_tab(cmd);
			exit(EXIT_FAILURE);
		}
	}
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

static void handle_child_process(noued_cmd *cmd_node, char **env, char **null_env, int pipefd[])
{
    if (cmd_node->next != NULL)
        dup2(pipefd[1], STDOUT_FILENO);
    close(pipefd[1]);
    close(pipefd[0]);

    if (cmd_node->redirection != NULL)
	{
        char **environment = env[0] ? env : null_env;
        execute_with_redirection(cmd_node->cmd, environment, cmd_node->redirection);
    }
	else
	{
        char **environment = env[0] ? env : null_env;
        execute(cmd_node->cmd, environment);
    }
}


static void execute_command(noued_cmd *cmd_node, char **env, char **null_env)
{
	int pipefd[2];
    pid_t pid;
	
    // if (!strstr(cmd_node->cmd, "$"))
	// {
        // execute_child_process(cmd_node, env, null_env, redirection);
		if (pipe(pipefd) == -1 || (pid = fork()) == -1)
			exit(EXIT_FAILURE);
		else if (pid == 0)
			handle_child_process(cmd_node, env, null_env, pipefd);
		else
		{
			    dup2(pipefd[0], STDIN_FILENO);
				close(pipefd[1]);
				close(pipefd[0]);
		}
	// }
	// else
    //     printf("\n");
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
			g_flags.envire = ft_merge_envr(data->export_i);
        	// builtins(data->args, data->export_i, data->env);
            execute_command(data->lst, data->env, data->null_env);
            data->lst = data->lst->next;
        }
    }
    while (0 < wait(NULL))
		;
}

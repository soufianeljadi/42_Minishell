/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 09:55:09 by sdiouane          #+#    #+#             */
/*   Updated: 2024/05/27 20:47:26 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

char **struct_to_char(s_env **lst)
{
	char **env;
	int i;
	s_env *tmp;

	i = 0;
	tmp = *lst;
	env = malloc(sizeof(char *) * (ft_lstsize(tmp) + 1));
	while (tmp)
	{
		env[i] = ft_strjoin(tmp->key, "=");
		if (tmp->value)
			env[i] = ft_strjoin(env[i], tmp->value);
		else
				env[i] = ft_strjoin(env[i], "");
		tmp = tmp->next;
		i++;
	}
	env[i] = NULL;
	return (env);
}

char	**splt_args(char *line)
{
	char	**cmds;
	
	cmds = split_args(line);
	return (cmds);       
}

char **check_quotes_before_execution(char *s)
{
    char	**cmd;
    int		i;
	
	cmd = NULL;
	i = 0;
	cmd = splt_args(s);
	if (!cmd)
		exit(EXIT_FAILURE);
	while (cmd[i])
	{	
		if (count_quotes(cmd[i], '\"') % 2 == 0)
			del_dbl_quotes(cmd[i]);
		if (count_quotes(cmd[i], '\'') % 2 == 0)
			del_sngl_quotes(cmd[i]);
		i++;
	}
    return (cmd);     
}

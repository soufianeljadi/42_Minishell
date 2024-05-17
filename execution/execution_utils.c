/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 09:55:09 by sdiouane          #+#    #+#             */
/*   Updated: 2024/05/17 09:55:23 by sdiouane         ###   ########.fr       */
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

char **struct_to_char(s_env *lst)
{
	char **env;
	int i;
	s_env *tmp;

	i = 0;
	tmp = lst;
	env = malloc(sizeof(char *) * (ft_lstsize(lst) + 1));
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

char **check_quotes_before_execution(char *s)
{
	char **cmd = NULL;

	if ((s[0] == '\"' || s[0] == '\'') && (strstr(s, " ") || strstr(s, "\t")))
		cmd = ft_split(s, ' ');
	else
	{
		if (!strcmp(s , ""))
		{
			cmd = malloc(sizeof(char *) * 2);
			cmd[0] = strdup("");
			cmd[1] = NULL;
			return (cmd);
		}
		else
		{
			cmd = split_space_tab(s, ' ');
			if (cmd[0][0] == '\0')
				exit(EXIT_FAILURE);
		}
	}
	return (cmd);
}
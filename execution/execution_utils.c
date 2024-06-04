/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jadi <sel-jadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 09:55:09 by sdiouane          #+#    #+#             */
/*   Updated: 2024/06/04 22:26:34 by sel-jadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_last_cmd(s_env **lst, char **args)
{
	int		i;
	s_env	*tmp;

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

char	**struct_to_char(s_env **lst)
{
	char	**env;
	s_env	*tmp;
	int		i;

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

void	supprimer_protection(char *chaine)
{
	char	*source;
	char	*destination;

	source = chaine;
	destination = chaine;
	while (*source != '\0')
	{
		if (*source != '\\')
		{
			*destination = *source;
			destination++;
		}
		source++;
	}
	*destination = '\0';
}

int	is_blank(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			i++;
		else
			return (0);
	}
	return (1);
}

char	**check_quotes_before_execution(char *s)
{
	char	**cmd;
	int		i;

	cmd = NULL;
	i = 0;
	if (!s)
		exit(EXIT_FAILURE);
	if (s[0] == '\\')
	{
		supprimer_protection(s);
		del_sngl_quotes(s);
		cmd = malloc(sizeof(char *) * 2);
		cmd[0] = strdup(s);
		cmd[1] = NULL;
		return (cmd);
	}
	if ((strstr(s, " ") || strstr(s, "\t")) && is_blank(s))
		supprimerGuillemets(s);
	cmd = splt_args(s);
	if (!cmd)
		exit(EXIT_FAILURE);
	while (cmd[i])
	{
		if (count_quotes(cmd[i], '\"') % 2 == 0 && strstr(cmd[i], "\"") != NULL)
			del_dbl_quotes(cmd[i]);
		else if (count_quotes(cmd[i], '\'') % 2 == 0
			&& strstr(cmd[i], "'") != NULL)
			del_sngl_quotes(cmd[i]);
		i++;
	}
	return (cmd);
}

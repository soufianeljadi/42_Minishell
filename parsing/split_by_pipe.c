/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_by_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 22:07:07 by sel-jadi          #+#    #+#             */
/*   Updated: 2024/07/11 14:12:19 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*fct(char **args, char *s, int i)
{
	char	*temp;

	temp = NULL;
	if (!s)
		s = ft_strdup(args[i]);
	else
	{
		temp = ft_strjoin(s, " ");
		free(s);
		s = ft_strjoin(temp, args[i]);
		free(temp);
	}
	return (s);
}

static char	*handle_redirection(char *redirection, char *arg1, char *arg2)
{
	char	*temp1;
	char	*temp2;
	char	*temp3;

	temp1 = ft_strjoin(arg1, arg2);
	temp2 = ft_strjoin(redirection, temp1);
	free(temp1);
	temp3 = ft_strjoin(temp2, " ");
	free(temp2);
	free(redirection);
	return (temp3);
}

static void	add_and_reset_cmd(t_noued_cmd **cmd, char *s, char *redirection)
{
	add_back_noued_cmd(cmd, s, redirection);
	free(s);
	free(redirection);
}

t_noued_cmd	*split_args_by_pipe(char **args)
{
	t_noued_cmd	*cmd;
	char		*s;
	char		*red;
	int			i;

	(1) && (i = 0, cmd = NULL, s = NULL, red = NULL);
	while (args[i] != NULL)
	{
		if (ft_strcmp(args[i], "|") == 0)
			(add_and_reset_cmd(&cmd, s, red), red = NULL, s = NULL);
		else if (ft_strcmp(args[i], "<") == 0 || ft_strcmp(args[i], ">") == 0
			|| ft_strcmp(args[i], ">>") == 0 || ft_strcmp(args[i], "<<") == 0)
		{
			if (args[i + 1] == NULL)
				return (cmd);
			red = handle_redirection(red, args[i], args[i + 1]);
			i++;
		}
		else
			s = fct(args, s, i);
		i++;
	}
	if (s || red)
		add_and_reset_cmd(&cmd, s, red);
	return (cmd);
}

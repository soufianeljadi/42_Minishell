/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jadi <sel-jadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 19:58:08 by sdiouane          #+#    #+#             */
/*   Updated: 2024/07/19 22:58:10 by sel-jadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	protect_value(char *value)
{
	if (value)
		free(value);
}

void	check_(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	if (len < 2)
		return ;
	if ((str[0] == '\'' && str[len - 1] == '\'')
		|| (str[0] == '"' && str[len - 1] == '"'))
	{
		memmove(str, str + 1, len - 2);
		str[len - 2] = '\0';
	}
}

char	*exp_fct(char *commande, t_env *export_i, int *flag)
{
	char	*exp_commande;
	t_p		p;

	init_t_p(&p);
	if (!commande)
		exit(exit_stat(1));
	exp_commande = ft_strdup(commande);
	(check_memory_allocation(exp_commande), free(commande));
	while (exp_commande && exp_commande[p.i] != '\0')
	{
		handle_quotes(exp_commande, &p);
		if (exp_commande[p.i] == '$' && exp_commande[p.i + 1] == '?')
			exp_commande = replace_exit_status(exp_commande);
		else if (exp_commande[p.i] == '$' && (!p.q_open
				|| (p.q_open && p.cur_quote == '"')))
		{
			exp_commande = prc_variable(exp_commande, &p, export_i);
			check_(exp_commande);
			(check_memory_allocation(exp_commande), *flag = 1);
		}
		if (exp_commande[p.i] == '\0')
			break ;
		p.i++;
	}
	return (exp_commande);
}

int	get_pos_doll(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] != ' ' && str[i + 1] != '\t')
			return (1);
		i++;
	}
	return (0);
}

t_noued_cmd	*ft_expanding(t_data **data, t_env *export_i)
{
	t_data		*tmp;
	t_noued_cmd	*current;
	int			f;
	int			flag;

	(1) && (flag = 0, tmp = *data, current = tmp->lst, f = 0);
	while (current)
	{
		if (current->cmd)
		{
			if (get_pos_doll(current->cmd))
				(1) && (current->cmd = exp_fct(current->cmd, export_i, &f),
					flag = 1);
			if (flag == 1)
				supprimerguillemets(current->cmd);
			check_memory_allocation(current->cmd);
		}
		if (current->redirection)
		{
			current->redirection = exp_fct(current->redirection, export_i, &f);
			check_memory_allocation(current->redirection);
		}
		current = current->next;
	}
	return (tmp->lst);
}

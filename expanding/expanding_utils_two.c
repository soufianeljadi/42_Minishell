/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils_two.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jadi <sel-jadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 15:32:36 by sdiouane          #+#    #+#             */
/*   Updated: 2024/07/15 00:30:15 by sel-jadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*format_value_if_needed(char *key, t_env *export_i)
{
	char	*value;
	char	*tmp;

	value = get_env_value(key, export_i);
	if (value && value[0] == '\"' && value[ft_strlen(value) - 1] == '\"')
	{
		tmp = value;
		value = ft_substr2(value, 1, ft_strlen(value) - 2);
		free(tmp);
	}
	return (value);
}

void	check_memory_allocation(void	*ptr)
{
	if (!ptr)
		exit(exit_stat(1));
}

char	*replace_exit_status(char	*exp_commande)
{
	char	*new_command;

	new_command = ft_str_replace(exp_commande, ft_strdup("$?"),
			ft_itoa(exit_stat(-1)));
	check_memory_allocation(new_command);
	free(exp_commande);
	return (new_command);
}

void	init_t_p(t_p	*p)
{
	p->i = 0;
	p->j = 0;
	p->q_open = 0;
	p->cur_quote = 0;
}

void	handle_quotes(char	*exp_commande, t_p	*p)
{
	if (exp_commande[p->i] == '"' || exp_commande[p->i] == '\'')
	{
		if (p->q_open && exp_commande[p->i] == p->cur_quote)
		{
			p->q_open = 0;
			p->cur_quote = '\0';
		}
		else if (!p->q_open)
		{
			p->q_open = 1;
			p->cur_quote = exp_commande[p->i];
		}
	}
}

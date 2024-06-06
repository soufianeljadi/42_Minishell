/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 19:58:08 by sdiouane          #+#    #+#             */
/*   Updated: 2024/06/06 18:58:17 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void check_memory_allocation(void *ptr)
{
	if (!ptr)
		exit(exit_stat(1));
}

void handle_quotes(char *exp_commande, t_p *p)
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


char *format_value_if_needed(char *key, s_env *export_i)
{
	char *value;
	value = get_env_value(key, export_i);
	if (value && value[0] == '\"' && value[ft_strlen(value) - 1] == '\"')
		value = ft_substr2(value, 1, ft_strlen(value) - 2);
	else if (value && value[0] == '\'' && strcmp(value, "\""))
	{
		value = ft_strjoin("\\", value);
		check_memory_allocation(value);
		value = ft_strjoin(value, "\\");
		check_memory_allocation(value);
	}
	return (value);
}

char *variable_with_value(char *full_key, char *key, char *value, char *exp_commande)
{
	char *exp_cmd;

	full_key = ft_strjoin("$", key);
	check_memory_allocation(full_key);
	exp_cmd = ft_str_replace(exp_commande, full_key, value);
	(check_memory_allocation(exp_cmd), free(exp_commande));
	exp_commande = strdup(exp_cmd);
	check_memory_allocation(exp_commande);
	(free(full_key), free(exp_cmd), free(key), free(value));
	return (exp_commande);
}

char *process_variable(char *exp_commande, t_p *p, s_env *export_i)
{
	char *key;
	char *value;
	char *full_key;

	full_key = NULL;
	key = get_env_key(exp_commande, p->i);
	check_memory_allocation(key);
	value = format_value_if_needed(key, export_i);
	if (!value || !strcmp(value, "") || !strcmp(value, " "))
	{
		if (strcmp(key, ""))
		{
			full_key = ft_strjoin("$", key);
			exp_commande = ft_str_replace(exp_commande, full_key, strdup(" "));
		}
		(free(key), free(value));
	}
	else
	{
		exp_commande = variable_with_value(full_key, key, value, exp_commande);
		check_memory_allocation(exp_commande);
	}
	return (exp_commande);
}

char *exp_fct(char *commande, s_env *export_i, int *flag)
{
	char	*exp_commande;
	t_p		p;

	p.i= 0;
	p.j = 0;
	p.q_open = 0;
	p.cur_quote = 0;
	if (!commande)
		exit(exit_stat(1));
	(exp_commande = ft_strdup(commande), check_memory_allocation(exp_commande));
	while (exp_commande && exp_commande[p.i] != '\0')
	{
		handle_quotes(exp_commande, &p);
		if (exp_commande[p.i] == '$' && exp_commande[p.i + 1] == '?')
			(exp_commande = ft_str_replace(exp_commande, ft_strdup("$?"),
				ft_itoa(exit_stat(-1))), check_memory_allocation(exp_commande));
		if (exp_commande[p.i] == '$' && (!p.q_open
			|| (p.q_open && p.cur_quote == '"')))
		{
			exp_commande = process_variable(exp_commande, &p, export_i);
				(check_memory_allocation(exp_commande), *flag = 1);
		}
		p.i++;
	}
	return (exp_commande);
}

noued_cmd	*ft_expanding(t_data **data, s_env *export_i)
{
	t_data *tmp;
	noued_cmd *current;
	int f;

	tmp = *data;
	current = tmp->lst;
	f = 0;
	while (current)
	{
		if (current->cmd)
		{
			current->cmd = exp_fct(current->cmd, export_i, &f);
			check_memory_allocation(current->cmd);
		}
		if (current->redirection)
		{
			current->redirection = exp_fct(current->redirection, export_i, &f);
			check_memory_allocation(current->redirection);
		}
		current = current->next;
	}
	current = tmp->lst;
	while (current)
		current = current->next;
	return (tmp->lst);
}

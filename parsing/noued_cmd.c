/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noued_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 22:25:13 by sel-jadi          #+#    #+#             */
/*   Updated: 2024/07/16 16:54:25 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_noued_cmd	*new_noued_cmd(char *commande, char *redirection)
{
	t_noued_cmd	*nouveau_noeud;

	nouveau_noeud = (t_noued_cmd *)ft_malloc(sizeof(t_noued_cmd));
	if (!nouveau_noeud)
		return (exit(exit_stat(1)), NULL);
	if (commande)
		nouveau_noeud->cmd = ft_strdup(commande);
	else
		nouveau_noeud->cmd = NULL;
	if (redirection)
		nouveau_noeud->redirection = ft_strdup(redirection);
	else
		nouveau_noeud->redirection = NULL;
	nouveau_noeud->next = NULL;
	return (nouveau_noeud);
}

void	add_back_noued_cmd(t_noued_cmd **tete, char *c, char *r)
{
	t_noued_cmd	*courant;

	if (!*tete)
		*tete = new_noued_cmd(c, r);
	else
	{
		courant = *tete;
		while (courant->next)
			courant = courant->next;
		courant->next = new_noued_cmd(c, r);
	}
}

void	free_noued_cmd(t_noued_cmd *head)
{
	t_noued_cmd	*current;
	t_noued_cmd	*next;

	current = head;
	while (current != NULL)
	{
		next = current->next;
		if (current->redirection != NULL)
			free(current->redirection);
		if (current->cmd != NULL)
			free(current->cmd);
		if (current)
			free(current);////////////
		current = next;
	}
}

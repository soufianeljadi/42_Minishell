/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_by_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 23:28:30 by sdiouane          #+#    #+#             */
/*   Updated: 2024/06/05 16:03:35 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *ft_strjoin( char *s1,  char *s2)
{
	size_t len_s1 = 0;
	size_t len_s2 = 0;
	size_t i = 0;
	size_t j = 0;
	char *result;

	if (s1)
		while (s1[len_s1])
			len_s1++;
	if (s2)
		while (s2[len_s2])
			len_s2++;
	result = (char *)malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (!result)
		return (exit(exit_stat(1)), NULL);
	while (i < len_s1)
	{
		result[i] = s1[i];
		i++;
	}
	while (j < len_s2)
	{
		result[i + j] = s2[j];
		j++;
	}
	result[i + j] = '\0';
	return result;
}

noued_cmd *new_noued_cmd(char *commande, char *redirection)
{
	noued_cmd *nouveau_noeud = (noued_cmd *)malloc(sizeof(noued_cmd));
	if (!nouveau_noeud)
		return (exit(exit_stat(1)), NULL);
	if (!commande)
		nouveau_noeud->cmd = NULL;
	else
		nouveau_noeud->cmd = strdup(commande);
	nouveau_noeud->redirection = (redirection) ? strdup(redirection) : NULL;
	nouveau_noeud->next = NULL;
	return nouveau_noeud;
}

void add_back_noued_cmd(noued_cmd **tete, char *commande, char *redirection)
{
	if (!*tete)
		*tete = new_noued_cmd(commande, redirection);
	else
	{
		noued_cmd *courant = *tete;
		while (courant->next)
			courant = courant->next;
		courant->next = new_noued_cmd(commande, redirection);
	}
}

void free_noued_cmd(noued_cmd *node)
{
	if (node == NULL)
		exit(exit_stat(1));
	free_noued_cmd(node->next);
	free(node->cmd);
	free(node->redirection);
	free(node);
}

char	*fct(char **args, char *temp, char *s, int i)
{
	if (!s)
		s = strdup(args[i]);
	else
	{
		temp = ft_strjoin(s, " ");
		free(s);
		s = ft_strjoin(temp, args[i]);
		free(temp);
	}
	return (s);
}

noued_cmd *split_args_by_pipe(char **args)
{
	noued_cmd	*cmd;
	char		*s;
	char		*redirection;
	int			i;
	char 		*temp;

	(1) && (i = 0, cmd = NULL, s = NULL, redirection = NULL, temp = NULL);
	
	i = 0;
	while (args[i] != NULL)
	{
		if (strcmp(args[i], "|") == 0) 
			(add_back_noued_cmd(&cmd, s, redirection), free(s), free (redirection), redirection = NULL, s = NULL);
		else if (strcmp(args[i], "<") == 0 || strcmp(args[i], ">") == 0 || strcmp(args[i], ">>") == 0 || strcmp(args[i], "<<") == 0)
		{
			if (args[i + 1] == NULL)
				return (cmd);
			(!s) && (s = strdup(""));
			(1) && (redirection = ft_strjoin(redirection, strdup(ft_strjoin(args[i], args[i + 1]))), redirection = ft_strjoin(redirection, " "),	i++);
		}
		else
			s = fct(args, temp, s, i);
		i++;
	}
	if (s || redirection)	
		(add_back_noued_cmd(&cmd, s, redirection),	free(s));
	return (cmd);
}

void print_command_list(noued_cmd *head)
{
	noued_cmd *current = head;
	int i = 0;

	(void)head;
	
	while (current != NULL)
	{
		printf("Noeud : %d\n", i);
		printf("->cmd : %s\n->rederection : %s \n", current->cmd, current->redirection);
		current = current->next;
		i++;
	}
}


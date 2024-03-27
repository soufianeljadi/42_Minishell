/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_by_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 23:28:30 by sdiouane          #+#    #+#             */
/*   Updated: 2024/03/27 23:31:10 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *ft_strjoin(const char *s1, const char *s2)
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
		return NULL;

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

noued_cmd *new_noued_cmd(char *commande)
{
    noued_cmd *nouveau_noeud = (noued_cmd *)malloc(sizeof(noued_cmd));
    if (nouveau_noeud == NULL)
	{
        printf("Erreur d'allocation de mémoire\n");
        exit(EXIT_FAILURE);
    }
    nouveau_noeud->cmd = strdup(commande);
    nouveau_noeud->next = NULL;
    return nouveau_noeud;
}


void add_back_noued_cmd(noued_cmd **tete, char *commande)
{
    if (*tete == NULL)
        *tete = new_noued_cmd(commande);
    else
	{
        noued_cmd *courant = *tete;
        while (courant->next != NULL)
            courant = courant->next;
        courant->next = new_noued_cmd(commande);
    }
}


noued_cmd *split_args_by_pipe(char **args)
{
	noued_cmd *cmd = NULL;
    char *s = NULL;
    int i = 0;

    while (args[i])
	{
        if (strcmp(args[i], "|") == 0)
		{
			add_back_noued_cmd(&cmd, s);
            free(s);
            s = NULL;
        }
		else
            s = ft_strjoin(s, args[i]);
        i++;
    }
    if (s != NULL)
	{
		add_back_noued_cmd(&cmd, s);
        free(s);
    }
	return (cmd);
}


void print_command_list(noued_cmd *head)
{
	noued_cmd *current = head;
	
	while (current != NULL)
	{
		printf("noeud : %s\n", current->cmd);
		current = current->next;
	}
}
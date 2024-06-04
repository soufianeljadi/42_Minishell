/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jadi <sel-jadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 15:04:54 by sdiouane          #+#    #+#             */
/*   Updated: 2024/06/04 22:22:13 by sel-jadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cc(char *chaine)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (chaine[i])
	{
		if (chaine[i] != '"')
			chaine[j++] = chaine[i];
		i++;
	}
	chaine[j] = '\0';
}

void	cc2(char *chaine)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (chaine[i])
	{
		if (chaine[i] != '\'')
			chaine[j++] = chaine[i];
		i++;
	}
	chaine[j] = '\0';
}
s_env	*unset_fct(char **args, s_env *env)
{
	int		i;
	int		j;
	char	*key;

	i = 1;
	if (!strcmp(args[0], "unset"))
	{
		while (args[i])
		{
			if (args[i][0] == '"')
				cc(args[i]);
			if (args[i][0] == '\'')
				cc2(args[i]);
			j = 0;
			while (args[i][j])
			{
				while (args[i] && args[i][j] != ' ' && args[i][j] != '\t' && args[i][j] != '\0')
					j++;
				key = ft_substr2(args[i], 0, j);
				s_env *prev = NULL;
				s_env *current = env;
				if (verif_export(key) == 1)
				{
					fprintf(stderr, "minishell: unset: %s: not a valid identifier\n", key);
					exit_stat(1);
				}
				else
				{
					while (current != NULL)
					{
						if (strcmp(current->key, key) == 0)
						{
							if (prev != NULL)
								prev->next = current->next;
							else
								env = current->next;
							free(current->key);
							free(current->value);
							free(current);
							break;
						}
						prev = current;
						current = current->next;
					}
					free(key);
					while (args[i][j] == ' ' || args[i][j] == '\t')
						j++;
				}
			}
			i++;
		}
	}
	exit_stat(0);
	return env;
}

// s_env *unset_fct(char **args, s_env *env) {
//     int i = 1;
//     int j;
//     char *key;

//     if (!strcmp(args[0], "unset")) {
//         while (args[i]) {
//             if (args[i][0] == '"')
//                 cc(args[i]);
//             if (args[i][0] == '\'')
//                 cc2(args[i]);

//             j = 0;
//             while (args[i][j]) {
//                 while (args[i] && args[i][j] != ' ' && args[i][j] != '\t' && args[i][j] != '\0')
//                     j++;

//                 key = ft_substr2(args[i], 0, j);

//                 if (verif_export(key) == 1) {
//                     fprintf(stderr, "minishell: unset: %s: not a valid identifier\n", key);
//                 } else {
//                     s_env *prev = NULL;
//                     s_env *current = env;

//                     while (current != NULL) {
//                         if (strcmp(current->key, key) == 0) {
//                             if (prev != NULL) {
//                                 prev->next = current->next;
//                             } else {
//                                 env = current->next;  // Met à jour la tête de la liste
//                             }
//                             free(current->key);
//                             free(current->value);
//                             free(current);
//                             break;
//                         }
//                         prev = current;
//                         current = current->next;
//                     }
//                 }
//                 free(key);
//                 while (args[i][j] == ' ' || args[i][j] == '\t')
//                     j++;
//             }
//             i++;
//         }
//     }
//     return env;
// }

// =>  minishell => unset 'hh"h'
// Noeud : 0
// ->cmd : unset 'hh"h'
// ->rederection : (null)
// args[1] = 'hh"h'
// key = hhh

// bash-3.2$ unset "hhh"
// bash-3.2$ unset "hh'h"
// bash: unset: `hh'h': not a valid identifier
// bash-3.2$ unset  'hhh"hhh'
// bash: unset: `hhh"hhh': not a valid identifier
// bash-3.2$

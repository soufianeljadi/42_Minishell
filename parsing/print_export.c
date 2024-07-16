/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 22:02:27 by sel-jadi          #+#    #+#             */
/*   Updated: 2024/07/16 15:36:27 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void ft_rm_quotes(char *str)
// {
//     int len = strlen(str);
//     if (len < 2)
//         return; // Pas de quotes à enlever si la chaîne a moins de 2 caractères

//     char quote_type = '\0';
//     int start = -1, end = -1;

//     // Trouver la première quote ouvrante
//     for (int i = 0; i < len; i++)
//     {
//         if (str[i] == '"' || str[i] == '\'')
//         {
//             quote_type = str[i];
//             start = i;
//             break;
//         }
//     }

//     // Si aucune quote ouvrante trouvée, retourner
//     if (start == -1)
//         return;

//     // Si la première quote est au début et il y a un espace après
//     if (start == 0 && len > 2 && (str[start + 1] == ' ' || str[start + 1] == '\t'))
//         return;

//     // Trouver la première quote fermante correspondante
//     for (int i = start + 1; i < len; i++)
//     {
//         if (str[i] == quote_type)
//         {
//             end = i;
//             break;
//         }
//     }

//     // Si aucune quote fermante correspondante trouvée, retourner
//     if (end == -1)
//         return;

//     // Supprimer les premières quotes fermées
//     memmove(&str[start], &str[start + 1], end - start - 1);
//     memmove(&str[end - 1], &str[end + 1], len - end);
//     len -= 2; // Ajuster la longueur de la chaîne après suppression des quotes

//     // Vérifie si les nouvelles premières et dernières quotes sont appariées
//     if ((str[0] == '"' && str[len - 1] == '"') || (str[0] == '\'' && str[len - 1] == '\''))
//     {
//         // Supprime la première quote
//         memmove(str, str + 1, len - 1);
//         // Supprime la dernière quote
//         str[len - 2] = '\0'; // Ajuste la longueur de la chaîne
//     }
// }


void	print_export(t_env *list)
{
	while (list)
	{
		if (ft_strcmp(list->key, "_") != 0 && ft_strcmp(list->key, "?") != 0)
		{
			if (list->value == NULL)
				printf("declare -x %s\n", list->key);
			else
			{
				if (!ft_strcmp(list->value, ""))
				{
					printf("declare -x %s=", list->key);
					printf("\"%s\"\n", list->value);
				}
				else if (ft_strcmp(list->value, ""))
				{
					printf("declare -x %s=", list->key);
					ft_rm_quotes(list->value);
					printf("\"%s\"\n", list->value);
				}
			}
		}
		list = list->next;
	}
}

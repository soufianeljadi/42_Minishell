/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 16:50:26 by sdiouane          #+#    #+#             */
/*   Updated: 2024/03/23 21:03:24 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void echo_fct(char *line)
{
	int i = 0;
	int newline = 1;
	int in_quotes = 0;

	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (strncmp(&line[i], "echo", 4) == 0)
	{
		i = i + 4;
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (line[i] == '"' || line[i] == '\'')
		{
			in_quotes = 1;
			i++;
		}
		if (strncmp(&line[i], "-n", 2) == 0)
		{
			i += 2;
			if (line[i] == ' ' || line[i] == '\t')
				newline = 0;
			while (line[i] == ' ' || line[i] == '\t')
				i++;
		}
		if (in_quotes)
		{
			while (line[i] != '"' && line[i] != '\'' && line[i] != '\0')
			{
				printf("%c", line[i]);
				i++;
			}
			if (line[i] == '"' || line[i] != '\'')
				i++;
		}
		else
			printf("%s", &line[i]);
		}
		if (newline)
			printf("\n");
}


// void echo_fct(char *line) {
//     int i = 0;
//     int in_quotes = 0;
//     int num_n_flags = 0; // Compteur pour les occurrences de l'option -n

//     while (line[i] == ' ' || line[i] == '\t')
//         i++;
//     if (strncmp(&line[i], "echo", 4) == 0) {
//         i = i + 4;
//         while (line[i] == ' ' || line[i] == '\t')
//             i++;
//         if (line[i] == '"' || line[i] == '\'') {
//             in_quotes = 1;
//             i++;
//         }
//         while (strncmp(&line[i], "-n", 2) == 0) {
//             num_n_flags++; // Incrémente le compteur d'occurrences de -n
//             i += 2;
//             // Ignorer les espaces supplémentaires entre les options -n
//             while (line[i] == ' ' || line[i] == '\t')
//                 i++;
//         }
//         if (in_quotes) {
//             while (line[i] != '"' && line[i] != '\'' && line[i] != '\0') {
//                 printf("%c", line[i]);
//                 i++;
//             }
//             if (line[i] == '"' || line[i] != '\'')
//                 i++;
//         } else {
//             // Imprime les caractères après la dernière occurrence de -n
//             while (line[i] != '\0') {
//                 printf("%c", line[i]);
//                 i++;
//             }
//         }

//         // Print newline seulement si aucune occurrence de -n n'a été trouvée
//         if (num_n_flags == 0)
//             printf("\n");
//     }
// }
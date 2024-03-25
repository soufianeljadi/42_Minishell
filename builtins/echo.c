/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 16:50:26 by sdiouane          #+#    #+#             */
/*   Updated: 2024/03/25 17:00:11 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void echo_fct(char *line)
{
	int i = 0;
	int in_quotes = 0;
	int num_n_flags = 0;

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
			char quote = line[i];
			i++;
			while (line[i] != quote && line[i] != '\0')
				printf("%c", line[i++]);
			if (line[i] == quote)
				i++;
		}
		while (line[i] != '\0')
		{
			if (line[i] == '"' || line[i] == '\'')
			{
				char quote = line[i];
				i++;
				while (line[i] != quote && line[i] != '\0')
					printf("%c", line[i++]);
				if (line[i] == quote)
					i++;
			}
			else if (strncmp(&line[i], "-n", 2) == 0)
			{
				num_n_flags++;
				i += 2;
				while (line[i] == ' ' || line[i] == '\t')
					i++;
			}
			else
				printf("%c", line[i++]);
		}
		if (num_n_flags == 0)
			printf("\n");
	}
}

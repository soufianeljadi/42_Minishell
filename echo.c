/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 16:50:26 by sdiouane          #+#    #+#             */
/*   Updated: 2024/03/23 17:04:38 by sdiouane         ###   ########.fr       */
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
            newline = 0;
            i += 2;
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jadi <sel-jadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 15:55:13 by sdiouane          #+#    #+#             */
/*   Updated: 2024/03/27 00:15:49 by sel-jadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void syntax_error()
{	
	printf("syntax error \n");
}

Token** parse_command(char *command)
{
    Token **tokens = malloc(sizeof(Token*) * strlen(command));
    if (tokens == NULL)
    {
        fprintf(stderr, "Erreur lors de l'allocation de mémoire pour les jetons\n");
        exit(EXIT_FAILURE);
    }

    char *token_str = ft_strtok(command, " ");
    int token_count = 0;

    while (token_str != NULL)
    {
        tokens[token_count++] = create_token(token_str);
        token_str = ft_strtok(NULL, " ");
    }
    tokens[token_count] = NULL;

    return tokens;
}

void nbr_quotes(char *str)
{
	int i = 0;
	int cmp1 = 0;
	int cmp2 = 0;

	while (str[i] != '\0')
	{
		if (str[i] == '"' && str[i - 1] != '\\')
			cmp1++;
		i++;
	}
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' && str[i - 1] != '\\')
			cmp2++;
		i++;
	}
	
	if (cmp1 % 2 != 0 || cmp2 % 2 != 0)
		syntax_error();
}



int parsing(char *line)
{
    if (parse_single_input(line, '|'))
		return (1);
	// nbr_quotes(line);
	if(parse_redirection(line))
		return (1);
	return(0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 22:01:48 by sdiouane          #+#    #+#             */
/*   Updated: 2024/03/25 16:59:51 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

Token* create_token(char *value)
{
    Token *token = malloc(sizeof(Token));
    if (token == NULL)
    {
        fprintf(stderr, "Erreur lors de l'allocation de mémoire pour le jeton\n");
        exit(EXIT_FAILURE);
    }
    token->value = strdup(value);
    return token;
}

void free_token(Token *token)
{
    free(token->value);
    free(token);
}

void print_tokens(Token **tokens)
{
    for (int i = 0; tokens[i] != NULL; i++)
    {
        printf("%s\n", tokens[i]->value);
    }
}

void free_tokens(Token **tokens)
{
    for (int i = 0; tokens[i] != NULL; i++)
    {
        free_token(tokens[i]);
    }
    free(tokens);
}
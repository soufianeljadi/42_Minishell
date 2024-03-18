/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtock.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 22:28:09 by sdiouane          #+#    #+#             */
/*   Updated: 2024/03/17 22:38:42 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_strtok(char *str, const char *delim)
{
    static char *last_str = NULL;  
    char *token_start;
    // const char *delim_ptr;

    if (str == NULL)
        str = last_str;

    while (*str && strchr(delim, *str))
        str++;

    if (*str == '\0')
        return NULL;

    token_start = str;

    while (*str && !strchr(delim, *str))
        str++;

    if (*str != '\0')
        *str++ = '\0';

    last_str = str;

    return token_start;
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 10:16:07 by sdiouane          #+#    #+#             */
/*   Updated: 2024/07/17 14:24:52 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"



static int find_first_quote(const char *str)
{
    int i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == '"' || str[i] == '\'')
            return i;
        i++;
    }
    return -1;
}

static int find_matching_quote(const char *str, char quote_type, int start)
{
    int i = start + 1;
    while (str[i] != '\0')
    {
        if (str[i] == quote_type)
            return i;
        i++;
    }
    return -1;
}

static void remove_quotes(char *str)
{
    int len = strlen(str);
    int start = find_first_quote(str);
    int end = find_matching_quote(str, str[start], start);

    if (start != -1 && end != -1)
    {
        memmove(&str[start], &str[start + 1], end - start);
        memmove(&str[end - 1], &str[end + 1], len - end);
    }
}

void ft_rm_quotes(char *str)
{
    int len = strlen(str);
    if (len < 2)
        return; // Pas de quotes à enlever si la chaîne a moins de 2 caractères

    int start = find_first_quote(str);
    if (start == -1)
        return; // Si aucune quote ouvrante trouvée, retourner

    char quote_type = str[start];
    int end = find_matching_quote(str, quote_type, start);
    if (end == -1)
        return; // Si aucune quote fermante correspondante trouvée, retourner

    remove_quotes(str);
}


// static int find_first_quote(const char *str)
// {
//     int i = 0;
//     while (str[i] != '\0')
//     {
//         if (str[i] == '"' || str[i] == '\'')
//             return i;
//         i++;
//     }
//     return -1;
// }

// static int find_matching_quote(const char *str, char quote_type, int start)
// {
//     int i = start + 1;
//     while (str[i] != '\0')
//     {
//         if (str[i] == quote_type)
//             return i;
//         i++;
//     }
//     return -1;
// }

// static void remove_quotes(char *str)
// {
//     int len = strlen(str);
//     int start = find_first_quote(str);
//     int end = find_matching_quote(str, str[start], start);

//     if (start != -1 && end != -1)
//     {
//         memmove(&str[start], &str[start + 1], end - start);
//         memmove(&str[end - 1], &str[end + 1], len - end);
//     }
// }

// void ft_rm_quotes(char *str)
// {
//     int len = strlen(str);
//     if (len < 2)
//         return; // Pas de quotes à enlever si la chaîne a moins de 2 caractères

//     int start = find_first_quote(str);
//     if (start == -1)
//         return; // Si aucune quote ouvrante trouvée, retourner

//     char quote_type = str[start];
//     int end = find_matching_quote(str, quote_type, start);
//     if (end == -1)
//         return; // Si aucune quote fermante correspondante trouvée, retourner
//     len = strlen(str);
//     remove_quotes(str);
//     int i = 0;
//     while (str[i])
//     {
//         if ((str[i] == '"' || str[i] == '\'') && (str[i + 1] == '\'' || str[i + 1] == '\''))
//         {
//             remove_quotes(str);
//         }
//         else
//             i++;
//     }
//     if (str[end] != '\'' && str[end - 1] != '"')
//         ft_rm_quotes(str);
// }

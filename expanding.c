/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 19:58:08 by sdiouane          #+#    #+#             */
/*   Updated: 2024/05/01 21:19:10 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_env_value(char *key, s_env *export_i)
{
    s_env *tmp;
    char *value;
    // int i = 0;

    tmp = export_i;
    while (tmp)
    {
        if (!strcmp(tmp->key, key))
        {
            value = strdup(tmp->value);
            return (value);
        }
        tmp = tmp->next;
    }
    return (NULL);
}

char *ft_str_replace(char *source, char *pattern, char *replacement)
{
    size_t pattern_len = strlen(pattern);
    size_t replacement_len = strlen(replacement);

    const char *occurrence = strstr(source, pattern); // Recherche de la première occurrence du motif dans la source

    if (!occurrence)
        return strdup(source);
    // Calcule la taille de la nouvelle chaîne
    size_t new_size = strlen(source) - pattern_len + replacement_len + 1;
    char *new_str = (char *)malloc(new_size);
    if (!new_str)
        return NULL;
    // Copie la partie de la source avant l'occurrence du motif dans la nouvelle chaîne
    memcpy(new_str, source, occurrence - source);
    new_str[occurrence - source] = '\0';
    // Concatène la chaîne de remplacement à la nouvelle chaîne
    strcat(new_str, replacement);
    // Concatène la partie de la source après l'occurrence du motif à la nouvelle chaîne
    strcat(new_str, occurrence + pattern_len);
    return new_str;
}

void supprimerDoll(char *chaine)
{
    int i = 0;
	int j = 0;

    while (chaine[i])
	{
        if (chaine[i] != '$')
            chaine[j++] = chaine[i];
        i++;
    }
    chaine[j] = '\0';
}

// void supprimerquotes(char *chaine)
// {
//     int i = 0;
// 	int j = 0;

//     while (chaine[i])
// 	{
//         if (chaine[i] != '\'')
//             chaine[j++] = chaine[i];
//         i++;
//     }
//     chaine[j] = '\0';
// }

char *get_env_key(char *str, int i)
{
    char *key = NULL;
    while (str[i] && str[i] != '$')
        i++;
    if (str[i] == '$')
    {
        i++;
        int key_start = i;
        while (str[i] && ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= '0' && str[i] <= '9') || str[i] == '_'))
            i++;
        key = (char *)malloc((i - key_start + 1) * sizeof(char)); // Exclude the last '$' from the key length
        if (!key)
            exit(EXIT_FAILURE);
        strncpy(key, &str[key_start], i - key_start);
        key[i - key_start] = '\0';
    }
    return (key);
}

void ft_expanding(char **args, s_env *export_i)
{
	int i = 0;
	int j;
    char *expanded_cmd;
    char *key;
    char *value;
    i = j = 0;

    
    while (args[i])
    {
        if (is_single(args[i]) == 1)
            return ;
        j = 0;
        while (args[i] && args[i][j])
        {
                if (args[i][j] == '$')
                {
                    // j++;
                    key = get_env_key(args[i], j);
                    if (!key)
                        exit(EXIT_FAILURE);
                    printf("KEY : %s\n", key);
                    value = get_env_value(key, export_i);
                    if (value)
                    {
                        // key = ft_strjoin("$", key);
                        expanded_cmd = ft_str_replace(args[i], key, value);
                        // expanded_cmd = ft_substr(expanded_cmd, 0, strlen(expanded_cmd));
                        free(args[i]);
                        args[i] = expanded_cmd;
                        args[i] = ft_substr(args[i], 0, strlen(args[i]));
                        free(key);
                        free(value);
                    }
                    else
                    {
                        // key = ft_strjoin("$", key);
                        printf("---> %s\n", key);
                        expanded_cmd = ft_str_replace(args[i], key, strdup(""));
                        expanded_cmd = ft_substr(expanded_cmd, 0, strlen(expanded_cmd) - 1);
                        args[i] = ft_str_replace(args[i], key, strdup(""));
                        args[i] = ft_substr(args[i], 0, strlen(args[i]));
                    }
                }
            j++;
        }
        i++;
    }
    i = 0;
    // printf("%s", expanded_cmd);
}


// static char *remove_$(char *tab, int check)
// {
//     int i = 0;
//     int k = 0;

//     while (tab && tab[i])
//     {
//         if (tab && tab[i] == '\'' && check == 0)
//         {
//             i++;
//             while (tab && tab[i] && tab[i] != '\'')
//                 i++;
//             k = i;
//         }
//         if (tab && tab[i] == '$')
//             i++;
//         tab[k] = tab[i];
//         if (tab[i])
//         {
//             i++;
//             k++;
//         }
//         else
//             break;
//     }
//     if (tab[i])
//         tab[k] = '\0';
//     return tab;
// }


// void ft_expanding(char **args, s_env *export_i)
// {
//     // (void)env_list;
//     int i = 0;
//     int j = 0;
    
//     char *key = NULL;
//     char *value = NULL;
//     while (args && args[i])
//     {
//         j = 0;
//         while (args && args[i][j])
//         {
//             if (args && args[i] && args[i][j] == '\"')
//             {
//                 j++;
//                 while (args && args[i] && args[i][j] && args[i][j] != '\"')
//                 {
//                     if (args && args[i] && args[i][j] == '$')
//                     {
//                         key = get_env_key(args[i], j);
//                         // printf("%s\n", key);
//                         // printf("%s\n", value);
//                         value = get_env_value(key, export_i);
//                         if (key && value)
//                         {
//                             args[i] = ft_str_replace(args[i], key, value);
//                             args[i] = remove_$(args[i], 1);
//                         }
//                         else
//                         {
//                             args[i] = ft_str_replace(args[i], key, "");
//                             args[i] = remove_$(args[i], 1);
//                         }
//                     }
//                     j++;
//                 }
//             }
//             if (args && args[i] && args[i][j] == '\'')
//             {
//                 j++;
//                 while (args && args[i] && args[i][j] && args[i][j] != '\'')
//                     j++;
//             }
//             if (args && args[i] && args[i][j] == '$')
//             {
//                 if (args[i][j + 1] == '\"' || args[i][j + 1] == '\'' )
//                 {
//                     // args[i] = remove_$(args[i], 1);
//                     break;
//                 }
//                 // while ()
//                 key = get_env_key(args[i], j);
//                 value = get_env_value(key, export_i);
//                 if (key && value)
//                 {
//                     args[i] = ft_str_replace(args[i], key, value);
//                     args[i] = remove_$(args[i], 1);
//                 }
//                 else
//                 {
//                     args[i] = ft_str_replace(args[i], key, "");
//                     args[i] = remove_$(args[i], 1);
//                 }
//             }
//             if (args && args[i] && args[i][j])
//                 j++;
//         }
//         i++;   
//     }
    
// }

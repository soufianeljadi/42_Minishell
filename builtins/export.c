/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jadi <sel-jadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 22:11:52 by sdiouane          #+#    #+#             */
/*   Updated: 2024/03/27 01:09:10 by sel-jadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int len_of_env(char **env)
// {
// 	int i = 0;
// 	while (env[i])
// 		i++;
// 	return (i);
// }

// int	verif_export(char *str)
// {
// 	int	i;

// 	i = 0;
// 	if(str[0] >= '0' && str[0] <= '9')
// 		return (1);
// 	while (str[i])
// 	{
// 		if (!((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= '0' && str[i] <= '9'))) 
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

// s_env *export_fct(char *line, s_env *env)
// {
// 	int i = 0;
// 	int start1, start2;
// 	char *key, *value;

// 	while (line[i] == ' ' || line[i] == '\t')
// 		i++;
// 	if (strncmp(&line[i], "export", 6) == 0)
// 	{
// 		i += 6;
// 		while (line[i] == ' ' || line[i] == '\t')
// 			i++;
// 		while (line[i] != '\0')
// 		{
// 			start1 = i;
// 			while (line[i] != '=' && line[i] != '\0')
// 				i++;
// 			if (line[i] != '=')
// 			{
// 				syntax_error();
// 				exit(EXIT_FAILURE);
// 			}
// 			start2 = ++i;
// 			while (line[i] != ' ' && line[i] != '\t' && line[i] != '\0')
// 				i++;
// 			value = ft_substr(&line[start2], 0, i - start2);
// 			key = ft_substr(&line[start1], 0, start2 - start1 - 1);
// 			if (verif_export(key) == 0)
// 			{
// 				s_env *current = env;
// 				while (current != NULL)
// 				{
// 					if (strcmp(current->key, key) == 0)
// 					{
// 						// free(current->value);
// 						current->value = value;
// 						break;
// 					}
// 					current = current->next;
// 				}
// 				if (current == NULL && key[0])
// 					ft_lstadd_back(&env, ft_lstnew_data(value, key));
// 				while (line[i] == ' ' || line[i] == '\t')
// 					i++;
// 			}
// 			else
// 				syntax_error();
// 		}
// 	}
// 	return env;
// }

char *ft_strjoin(const char *s1, const char *s2)
{
    size_t len_s1 = 0;
    size_t len_s2 = 0;
    size_t i = 0;
    size_t j = 0;
    char *result;

    if (s1)
        while (s1[len_s1])
            len_s1++;
    if (s2)
        while (s2[len_s2])
            len_s2++;

    result = (char *)malloc(sizeof(char) * (len_s1 + len_s2 + 1));
    if (!result)
        return NULL;

    while (i < len_s1)
    {
        result[i] = s1[i];
        i++;
    }
    while (j < len_s2)
    {
        result[i + j] = s2[j];
        j++;
    }
    result[i + j] = '\0';

    return result;
}
 

s_env	*export_fct(char **args, s_env   *env)
{
	int i = 1;
	int j;
	int start;
	char *key;
	char *value;
	s_env *current;
	if (!strcmp(args[0], "export") && !args[1])
	    print_export(env);
	else
	{
		while(args[i])
		{
			j = 0;
			while (args[i][j] != '=' || args[i][j] == '\0')
				j++;
			key = ft_substr(args[i], 0, j);
			if(args[i][j] == '\0')
				ft_lstadd_back(&env, ft_lstnew_data(strdup(""), key));
			else
			{
					j++;
					start = j;
					while (args[i][j])
						j++;
				value = ft_substr(args[i], start, j - start);
				if (args[i][j - 1] == '+')
				{
					current = env;
					char *old_value = value;
					printf("\n----------old : %s --------\n\n", old_value);
					while (current != NULL)
					{
						if (strcmp(current->key, key) == 0)
						{
							old_value = current->value;
							current->value = ft_strjoin(old_value, value);
							break;
						}
						current = current->next;
					}
				}
				else
				{
					// j++;
					// start = j;
					// while (args[i][j])
					// 	j++;
					// value = ft_substr(args[i], start, j - start);
					current = env;
					while (current != NULL)
					{
						if (strcmp(current->key, key) == 0)
						{
							free(current->value);
							current->value = value;
							break;
						}
						current = current->next;
					}
					if (current == NULL && key[0])
						ft_lstadd_back(&env, ft_lstnew_data(value, key));	
				}									
			}
			i++;
		}
	}
	return env;
}




/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_null.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 21:24:00 by sdiouane          #+#    #+#             */
/*   Updated: 2024/05/20 15:14:38 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void del_qotes1(char *chaine)
{
    int i = 0, j = 0;
    while (chaine[i])
	{
        if (chaine[i] != '"')
            chaine[j++] = chaine[i];
        i++;
    }
    chaine[j] = '\0';
}

void is_equal(char **args, s_env *env, char *key)
{
    int start = ++env->j;
    while (args[env->i][env->j] && args[env->i][env->j] != '\0')
        env->j++;
    char *value = ft_substr(args[env->i], start, env->j - start);
    if (value[0] == '"')
        del_qotes1(value);
    s_env *current = env;
    while (current != NULL)
	{
        if (strcmp(current->key, key) == 0)
		{
            free(current->value);
            current->value = value;
            return;
        }
        current = current->next;
    }
    ft_lstadd_back(&env, ft_lstnew_data(value, key));
}

void concatenation(char **args, s_env *env, char *key)
{
    env->j += 2;
    int start = (args[env->i][env->j] == '"') ? ++env->j : env->j;
    while (args[env->i][env->j] && args[env->i][env->j] != '"')
        env->j++;
    char *value = ft_substr(args[env->i], start, env->j - start);
    s_env *current = env;
    while (current != NULL)
	{
        if (strcmp(current->key, key) == 0)
		{
            current->value = ft_strjoin(current->value, value);
            return;
        }
        current = current->next;
    }
}

void check(char *key, int i, int j, char **args, s_env *env)
{
	if (args[i][j] == '+')
	{
		if (args[i][j + 1] != '=')
			printf("export : %c, not a valid identifier", args[i][j]);
		else
			concatenation(args, env, key);
	}
	else if (args[i][j] == '=')
		is_equal(args, env, key);
	else if (args[i][j] == '\0')
	{
		if (!existe_deja(key, env))
			ft_lstadd_back(&env, ft_lstnew_data(strdup(""), key));
	}
}

void is_null(char **args, s_env *env)
{
	char *key;
	
	key = NULL;
    if (!strcmp(args[0], "export"))
	{
        if (!args[1])
            print_export(env);
		else
		{
            int i = 1;
            while (args[i])
			{
                int j = 0;
                while (args[i][j] && args[i][j] != '=' && args[i][j] != '+')
                    j++;
                key = ft_substr(args[i], 0, j);
				check(key, i, j, args, env);
                i++;
            }
        }
    }
}

// void is_null(char **args, s_env *env)
// {
// 	char *key;
	
// 	key = NULL;
//     if (!strcmp(args[0], "export"))
// 	{
//         if (!args[1])
//             print_export(env);
// 		else
// 		{
//             int i = 1;
//             while (args[i])
// 			{
//                 int j = 0;
//                 while (args[i][j] && args[i][j] != '=' && args[i][j] != '+')
//                     j++;
//                 key = ft_substr(args[i], 0, j);
//                 if (args[i][j] == '+' && args[i][j + 1] != '=')
//                     printf("export : %c, not a valid identifier", args[i][j]);
// 				else if (verif_export(key) == 0)
// 				{
//                     if (args[i][j] == '\0')
// 					{
//                         if (!existe_deja(key, env))
//                             ft_lstadd_back(&env, ft_lstnew_data(strdup(""), key));
//                     }
// 					else if (args[i][j] == '=') 
//                         (env->i = i, env->j = j, is_equal(args, env, key));
// 					else if (args[i][j] == '+' && args[i][j + 1] == '=')
//                         (env->i = i, env->j = j, concatenation(args, env, key));
//                 }
// 				else
//                     fprintf(stderr, "minishell: export: `%s': not a valid identifier\n", args[i]);
//                 i++;
//             }
//         }
//     }
// }

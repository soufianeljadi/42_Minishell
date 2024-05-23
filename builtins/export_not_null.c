/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_not_null.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 21:25:42 by sdiouane          #+#    #+#             */
/*   Updated: 2024/05/23 11:57:18 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void remove_q(char *chaine)
{
    int i = 0, j = 0;
    while (chaine[i])
	{
        if (chaine[i] != '\'')
            chaine[j++] = chaine[i];
        i++;
    }
    chaine[j] = '\0';
}

s_env *process_export_args(char **args, s_env *env)
{
    int		i;
	char	*key;

	(1) && (i = 1, key = NULL);
    while (args[i])
	{
        int j = 0;
			while (args[i][j] && args[i][j] != '=' && args[i][j] != '+')
				j++;
			key = ft_substr(args[i], 0, j);
			if (args[i][j] == '+' && args[i][j + 1] != '=')
				printf("export : %c, not a valid identifier", args[i][j]);
			else if (verif_export(key) == 0)
			{
				if (args[i][j] == '=')
					(env->i = i, env->j = j), fct_equal(args, env, key);
				else if (args[i][j] == '+' && args[i][j + 1] == '=')
					(env->i = i, env->j = j), ftc_concatination(args, env, key);
				else if (existe_deja(key, env) == 0)
					ft_lstadd_back(&env, ft_lstnew_data(NULL, key));
			}
			else
				fprintf(stderr, "minishell: export: `%s': not a valid identifier\n", key);
        i++;
    }
    return env;
}
          
s_env *not_null(char **args, s_env *env)
{
    if (!strcmp(args[0], "export"))
	{
        if (!args[1])
            print_export(env);
        else
            env = process_export_args(args, env);
    }
    return env;
}

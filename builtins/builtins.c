/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jadi <sel-jadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 01:07:33 by sel-jadi          #+#    #+#             */
/*   Updated: 2024/03/27 00:23:19 by sel-jadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int get_len_env(char **env)
{
	int i = 0;
	while (env[i])
		i++;
	return (i);	
}

void check_var_qu(char *line)
{
	int i = 0;
	
	while (line[i])
	{
		if (line[i] == '"')
		{
			while (line[i] != '$')
			{
				printf("%c", line[i]);
				i++;
			}
			if (line[i] == '$')
			{
				while (line[i] != '$')
				{
					printf("%c", line[i]);
					i++;
				}
			}
		}
		i++;
	}
}

void check_variables(char *line, s_env	*lst)
{
	int i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	while (line[i])
	{
			if (line[i] == '$' && line[i + 1] != ' ' && line[i + 1] != '\t')
			{
				i++;
				while (lst)
				{
					if (strcmp(line + i, lst->key) == 0)
					{
						printf("%s\n", lst->value);
					}
					lst = lst->next;
				}
			}
			
		i++;
		}
}

int check_env(char *line)
{
    int i = 0;
    while (line[i] == ' ' || line[i] == '\t')
        i++;
    if (strncmp(&line[i], "env", 3) == 0)
	{
		i += 3;
    	while ((line[i] == ' ' || line[i] == '\t'))
        	i++;
        if (line[i] == '\0')
            return 0;
	}
    return 1;
}

int check_export(char *line)
{
    int i = 0;
    while (line[i] == ' ' || line[i] == '\t')
        i++;
    if (strncmp(&line[i], "export", 5) == 0)
	{
		i += 6;
    	while ((line[i] == ' ' || line[i] == '\t'))
        	i++;
        if (line[i] == '\0')
            return 0;
    }
    return 1;
}
void builtins(char *line,char ** args, s_env *s_env)
{
    //ECHO
    echo_fct(args);
	// pwd :
	pwd_without_options(line);
	// unset :
	s_env = unset_fct(line, s_env);
	// export :
	export_fct(args ,s_env);

	//env
	if (!strcmp(args[0], "env") && !args[1])
        	print_list(s_env);
	// $variables :
	check_variables(line, s_env);
}
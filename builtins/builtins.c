/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jadi <sel-jadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 01:07:33 by sel-jadi          #+#    #+#             */
/*   Updated: 2024/03/26 01:13:46 by sel-jadi         ###   ########.fr       */
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
void builtins(char *line, s_env *s_env)
{
    //ECHO
    echo_fct(line);
	// pwd :
	pwd_without_options(line);
	// unset :
	s_env = unset_fct(line, s_env);
	// export :
	if (check_export(line) == 0)
	    print_export(s_env);
	else
	{
		s_env = export_fct(line, s_env);
		// env :
		if (check_env(line) == 0)
        	print_list(s_env);
    }
	// $variables :
	check_variables(line, s_env);
}
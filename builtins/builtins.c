/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 01:07:33 by sel-jadi          #+#    #+#             */
/*   Updated: 2024/04/26 14:57:25 by sdiouane         ###   ########.fr       */
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

int   check_variables(char **args, s_env *lst)
{
	char *key;
	s_env *current;
	int i = 0;
	int j;
	int flag = 1;
	int flag2 = 1;
	while (args[i] && strstr(*args, "$"))
	{
		j = 0;
		// printf("++++++++++args[%d] = %s++++++++++\n", i, args[i]);
		while (args[i][j])
		{
			while (args[i][j])
			{
				if (strstr(args[i], "$") || strstr(args[i], "\""))
				{
					if (args[i][j] == '$' || args[i][j] == '"')
					{
						flag2 = 0;
						break;
					}
					else
					{
						printf("%c", args[i][j]);
						j++;
					}
				}
				else
					break;
			}
			if (args[i][j] == '"' && strstr(args[i], "$"))
			{
				j++;
				while (args[i][j] && args[i][j] != '"')
				{
					if (args[i][j] == '$')
					{
						j++;
						int key_start = j;
   				        while ((args[i][j] >= 'a' && args[i][j] <= 'z') || (args[i][j] >= 'A' && args[i][j] <= 'Z') || (args[i][j] >= '0' && args[i][j] <= '9') || args[i][j] == '_')
							j++;
						key = (char *)malloc((j - key_start + 1) * sizeof(char));
						if (!key)
							exit(EXIT_FAILURE);
						strncpy(key, &args[i][key_start], j - key_start);
						key[j - key_start] = '\0';
						current = lst;
						while (current)
						{
							if (strcmp(current->key, key) == 0)
							{
								printf("%s", current->value);
								flag = 0;
								break;
							}
							current = current->next;
						}
						free(key);
					}
					else if (args[i][j] != '"')
						printf("%c", args[i][j++]);
				}
			}
			else if (args[i][j] == '$' && flag2 == 0)
			{
					j++;
					int key_start = j;
   				    while ((args[i][j] >= 'a' && args[i][j] <= 'z') || (args[i][j] >= 'A' && args[i][j] <= 'Z') || (args[i][j] >= '0' && args[i][j] <= '9') || args[i][j] == '_')
						j++;
					key = (char *)malloc((j - key_start + 1) * sizeof(char));
					if (!key)
						exit(EXIT_FAILURE);
					strncpy(key, &args[i][key_start], j - key_start);
					key[j - key_start] = '\0';
					current = lst;
					while (current)
					{
						if (strcmp(current->key, key) == 0)
						{
							printf("%s", current->value);
							flag = 0;
							break;
						}
						current = current->next;
					}
					free(key);
				while (args[i][j] != '\0')
					printf("%c", args[i][j++]);
			}
			else
				j++;
		}
		i++;
	}
	if (flag == 1)
		return (1);
	return (0);
}


void print_env_i(s_env *lst)
{
	while (lst)
	{
		if (!strcmp(lst->key, "PWD"))
			printf("%s=%s\n", lst->key, lst->value);
		else if (!strcmp(lst->key, "SHLVL"))
			printf("%s=%s\n", lst->key, lst->value);
		else if (!strcmp(lst->key, "_"))
			printf("%s=%s\n", lst->key, lst->value);
		lst = lst->next;
	}
}

void builtins(char **args, s_env *export_i, char **env)
{
	(void)env;    
	char *pwd;

	//exit
	if (!strncmp(args[0], "exit", 4))
	{
		printf("exit\n");
		exit(EXIT_SUCCESS);
	}
	// echo :
	echo_fct(args, export_i);

	pwd = getcwd(NULL, 0);
	// pwd :
	pwd_without_options(args, pwd);
	// export :
	export_i = export_fct(args, export_i, export_i, env);
	// unset :
	export_i = unset_fct(args, export_i);

	// env
	if (*env)
	{
		if (!strcmp(args[0], "env") && !args[1])
			print_list(export_i);
	}
	else if (!*env)
	{
		if (!strcmp(args[0], "env") && !args[1])
		{
			print_list(export_i);
		}
	}
	// cd :
	execute_cd(args, export_i);		
}

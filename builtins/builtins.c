/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 01:07:33 by sel-jadi          #+#    #+#             */
/*   Updated: 2024/04/20 07:53:00 by sdiouane         ###   ########.fr       */
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


int check_variables(char **args, s_env *lst)
{
	char *key;
	s_env *current;
	int i = 0;
	int j;
	int flag = 1;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
		
			if (args[i][j] == '"')
			{
				j++;
				while(args[i][j] == ' ')
					printf("%c", args[i][j++]);
				if (args[i][j] == '$')
				{
					int key_start = j + 1;
					while (args[i][j] && args[i][j] != ' ' && args[i][j] != '\t')
						j++;
					key = (char *)malloc(((j - key_start) + 1) * sizeof(char));
					if (!key)
						exit(EXIT_FAILURE);
					strncpy(key, &args[i][key_start], j - key_start);
					key[j - key_start] = '\0';
					printf("key : %s\n", key);
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
					while(args[i][j] != '"')
						printf("%c", args[i][j++]);
					printf("\n--->%s\n\n", key);
				}
				else
					j++;
			}
			else
			{
				if (args[i][j] == '$')
				{
					int key_start = j + 1;
					while (args[i][j] && args[i][j] != ' ' && args[i][j] != '\t')
						j++;
					key = (char *)malloc(((j - key_start) + 1) * sizeof(char));
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
				else
					j++;
			}
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

void builtins(char **args, s_env *lst, s_env *env_i, char **env)
{
	// (void)env_i;
	(void)env;    
	char *pwd;

	//exit
	if (!strncmp(args[0], "exit", 4))
	{
		printf("exit\n");
		exit(EXIT_SUCCESS);
	}
	
	// echo :
	echo_fct(args, lst);

	pwd = getcwd(NULL, 0);
	// pwd :
	pwd_without_options(args, pwd);
	// unset :
	lst = unset_fct(args, lst);
	
	// export :
	export_fct(args ,lst);
	// env
	if (*env)
	{
		if (!strcmp(args[0], "env") && !args[1])
			print_list(lst);
	}
	else if (!*env)
	{
		if (!strcmp(args[0], "env") && !args[1])
			print_list(env_i);	
	}
	// cd :
	execute_cd(args, lst);		
	// $variables :
	check_variables(args, lst);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 01:07:33 by sel-jadi          #+#    #+#             */
/*   Updated: 2024/05/07 15:07:55 by sdiouane         ###   ########.fr       */
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
	int i = 0;
	int j;
	int flag = 1;
	int flag2 = 1;
	int c = 0;

// print_list(lst);
	if (strstr(*args, "$"))
		fprintf(stderr, "minishel: ");
	while (args[i] && strstr(*args, "$"))
	{
		j = 0;
		while (args[i][j])
		{
			while (args[i][j])
			{
				if (strstr(args[i], "$") || strstr(args[i], "\""))
				{
					if (args[i][j] == '$' || args[i][j] == '\"')
					{
						flag2 = 0;
						break;
					}
					else
						fprintf(stderr, "%c", args[i][j++]);
				}
				else
					break;
			}
			if (args[i][j] == '"' && strstr(args[i], "$"))
			{
				j++;
				while (args[i][j] && args[i][j] != '"')
				{
					if (args[i][j] == '$' && args[i][j + 1] != '_')
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
						//lst = lst;
						while (lst)
						{
							if (strcmp(lst->key, key) == 0)
							{
								fprintf(stderr, "%s", lst->value);
								flag = 0;
								break;
							}
							lst = lst->next;
						}
						free(key);
					}
					else if (args[i][j] != '"')
					{
						c = 1;
						fprintf(stderr, "%c", args[i][j++]);
					}
				}
				if(c == 0)
				{
					fprintf(stderr, " : is a directory");
					return (0);
				}
				else
				{
					fprintf(stderr, ": No such file or directory");
					return (0);
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
					//lst = lst;
					while (lst)
					{
						if (strcmp(lst->key, key) == 0)
						{
							printf("\nKEY : %s\tVALUE : %s\n", key, lst->value);
							fprintf(stderr, "%s", lst->value);
							flag = 0;
							break;
						}
						lst = lst->next;
					}
					free(key);
				while (args[i][j] != '\0')
				{
					fprintf(stderr, "%c", args[i][j++]);
					c = 1;
				}
				if(c == 0)
				{
					fprintf(stderr, " : is a directory");
					return (0);
				}
				else
				{
					fprintf(stderr, ": No such file or directory");
					return (0);
				}
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

// void builtins(char **args, s_env *export_i, char **env)
// {   
// 	char *pwd;

// 	//exit
// 	if (!strcmp(args[0], "exit"))
// 	{
// 		printf("exit\n");
// 		exit(EXIT_SUCCESS);
// 	}
// 	// echo :
// 	echo_fct(args, export_i);
// 	pwd = getcwd(NULL, 0);
// 	// pwd :
// 	pwd_without_options(args, pwd);
// 	// export :
// 	export_i = export_fct(args, export_i, export_i, env);
// 	// unset :
// 	export_i = unset_fct(args, export_i);
// 	// cd :
// 	export_i = execute_cd(args, export_i);		
// 	// env
// 	if (*env)
// 		if (!strcmp(args[0], "env") && !args[1])
// 			print_list(export_i);
// 	else if (!*env)
// 		if (!strcmp(args[0], "env") && !args[1])
// 			print_list(export_i);
// }

void builtins(char **args, s_env *export_i, char **env)
{   
    char *pwd;
	// supprimerGuillemets(args);
    if (!strcmp(args[0], "exit"))
    {
        printf("exit\n");
        exit(EXIT_SUCCESS);
    }
    else if (!strcmp(args[0], "echo"))
    {
        echo_fct(args, export_i);
    }
    else if (!strcmp(args[0], "pwd"))
    {
        pwd = getcwd(NULL, 0);
        pwd_without_options(args, pwd);
        free(pwd); // N'oubliez pas de libérer la mémoire allouée par getcwd
    }
    else if (!strcmp(args[0], "export"))
    {
        export_i = export_fct(args, export_i, export_i, env);
    }
    else if (!strcmp(args[0], "unset"))
    {
        export_i = unset_fct(args, export_i);
    }
    else if (!strcmp(args[0], "cd"))
    {
        export_i = execute_cd(args, export_i);        
    }
    else if (!strcmp(args[0], "env") && !args[1])
    {
        if (*env || !*env)
        {
            print_list(export_i);
        }
    }
	// exit(EXIT_SUCCESS);
}
      
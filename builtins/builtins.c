/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 01:07:33 by sel-jadi          #+#    #+#             */
/*   Updated: 2024/04/17 16:09:52 by sdiouane         ###   ########.fr       */
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
		i++;
	}
	if (flag == 1)
		return (1);
	return (0);
}



// Renvoie la valeur d'une variable d'environnement donnée
// char *get_env_value(const char *key, s_env *lst) {
//     s_env *current = lst;
//     while (current) {
//         if (strcmp(current->key, key) == 0) {
//             return current->value;
//         }
//         current = current->next;
//     }
//     return NULL;
// }

// // Vérifie et remplace les variables d'environnement dans une chaîne d'arguments
// void check_variables(char **args, s_env *lst) {
//     int i = 0;
//     int f = 0;
//     while (args[i]) {
//         if (args[i][0] == '$') {
//             char *key = &args[i][1]; // Ignorer le '$' initial
//             char *value = get_env_value(key, lst);
//             if (value != NULL) {
//                 printf("%s", value);
//             } else {
//                 printf("$%s", key); // Si la variable n'est pas définie, imprimer tel quel
//             }
//         } else {
//             printf("%s", args[i]);
//         }
//         printf(" ");
//         i++;
//     }
// }


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
	// printf("***********%s***********\n", pwd);

	

	// unset :
	lst = unset_fct(args, lst);
	
	// export :
	export_fct(args ,lst); // += 

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

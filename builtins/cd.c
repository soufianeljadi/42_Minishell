/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:00:00 by sdiouane          #+#    #+#             */
/*   Updated: 2024/06/07 11:22:13 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// s_env	*execute_cd(char **args, s_env *lst)
// {
// 	int i = 0;
// 	char *new_pwd;
// 	char *old_pwd;
// 	while(args[i])
// 		i++;

// 	if (i != 1)
// 	{
// 		if (!strcmp(args[0], "cd")  && args[1])
// 		{
// 			if (chdir(getenv("HOME")) == -1)
// 			{
// 				printf("hahahahahhahahahahhah\n");
// 				return (lst);
// 			}
// 			if (chdir(args[1]) != 0)
// 				perror("cd");
// 			new_pwd = getcwd(NULL, 0);
// 			if (!new_pwd)
// 			{
// 				while (lst && lst->next != NULL)
// 				{
// 					if (!strcmp(lst->key, "PWD"))
// 						lst->value = ft_strjoin(lst->value, "/..");
// 					lst = lst->next;
// 				}
// 				ft_putstr_fd("minishell: cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n", 2);
// 				return (lst);
// 			}
// 			while (lst && lst->next != NULL)
// 			{
// 				if (!strcmp(lst->key, "PWD"))
// 					old_pwd = ft_strdup(lst->value);
// 				if (!strcmp(lst->key, "PWD"))
// 					lst->value = ft_strdup(new_pwd);
// 				else if (!strcmp(lst->key, "OLDPWD"))
// 					lst->value = ft_strdup(old_pwd);
// 				lst = lst->next;
// 			}
// 		}
// 	}
// 	else
// 	{
// 		if (!strcmp(args[0], "cd"))
// 		{
// 			if (chdir(getenv("HOME")) == -1)
// 			{
// 				printf("hahahahahhahahahahhah\n");
// 				return (lst);
// 			}
// 			new_pwd = getcwd(NULL, 0);
// 			while (lst && lst->next != NULL)
// 			{
// 				if (!strcmp(lst->key, "PWD"))
// 					lst->value = ft_strdup(new_pwd);
// 				lst = lst->next;
// 			}
// 		}
// 	}
// 	return (lst);
// }

// < Makefile cat | " "
// s_env *update_env_var(s_env *lst, char *key, char *new_value)
// {
// 	s_env *head = lst;
// 	while (lst != NULL)
// 	{
// 		if (!strcmp(lst->key, key))
// 		{
// 			free(lst->value);
// 			lst->value = ft_strdup(new_value);
// 		}
// 		lst = lst->next;
// 	}
// 	return head;
// }

// s_env *execute_cd(char **args, s_env *lst)
// {
// 	int i;
// 	char *new_pwd;
// 	char *old_pwd;
// 	char *home;

// 	(1) && (i = 0, new_pwd = NULL, old_pwd = NULL);
// 	while (args[i])
// 		i++;
// 	old_pwd = getcwd(NULL, 0);
// 	if (!old_pwd)
// 	{
// 		perror("getcwd");
// 		return (lst);
// 	}
// 	if (i == 1 || (i == 2 && strcmp(args[1], "~") == 0))
// 	{
// 		home = get_env_value("HOME", lst);
// 		if (!home)
// 		{
// 			exit_stat(1);
// 			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
// 			free(old_pwd);
// 			return lst;
// 		}
// 		if (chdir(home) != 0)
// 		{
// 			perror("cd");
// 			free(old_pwd);
// 			return lst;
// 		}
// 	}
// 	else
// 	{
// 		if (chdir(args[1]) != 0)
// 		{
// 			exit_stat(256);
// 			perror("cd");
// 			free(old_pwd);
// 			return lst;
// 		}
// 	}
// 	new_pwd = getcwd(NULL, 0);
// 	if (!new_pwd)
// 	{
// 		ft_putstr_fd("minishell: cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n", 2);
// 		new_pwd = ft_strjoin(old_pwd, "/..");
// 	}
// 	lst = update_env_var(lst, "OLDPWD", old_pwd);
// 	lst = update_env_var(lst, "PWD", new_pwd);
// 	free(old_pwd);
// 	free(new_pwd);
// 	return lst;
// }

// s_env	*execute_cd(char **args, s_env *lst)
// {
// 	int i = 0;
// 	char *new_pwd;
// 	char *old_pwd;
// 	while(args[i])
// 		i++;
// 	if (i != 1)
// 	{
// 		if (!strcmp(args[0], "cd")  && args[1])
// 		{
// 			if (chdir(args[1]) != 0)
// 				perror("cd");
// 			new_pwd = getcwd(NULL, 0);
// 			if (!new_pwd)
// 			{
// 				while (lst && lst->next != NULL)
// 				{
// 					if (!strcmp(lst->key, "PWD"))
// 						lst->value = ft_strjoin(lst->value, "/..");
// 					lst = lst->next;
// 				}
// 				return (lst);
// 			}
// 			while (lst && lst->next != NULL)
// 			{
// 				if (!strcmp(lst->key, "PWD"))
// 					old_pwd = ft_strdup(lst->value);
// 				if (!strcmp(lst->key, "PWD"))
// 					lst->value = ft_strdup(new_pwd);
// 				else if (!strcmp(lst->key, "OLDPWD"))
// 					lst->value = ft_strdup(old_pwd);
// 				lst = lst->next;
// 			}
// 		}
// 	}
// 	else
// 	{
// 		if (!strcmp(args[0], "cd"))
// 		{
// 			if (chdir(getenv("HOME")) == -1)
// 				perror("HOME");
// 			new_pwd = getcwd(NULL, 0);
// 			while (lst && lst->next != NULL)
// 			{
// 				if (!strcmp(lst->key, "PWD"))
// 					lst->value = ft_strdup(new_pwd);
// 				lst = lst->next;
// 			}
// 		}
// 	}
// 	return (lst);
// }

// s_env	*execute_cd(char **args, s_env *lst)
// {

// }

// static int	set_oldpwd(char ***env, char *pwd, char *old)
// {
// 	char	*tmp;

// 	tmp = ft_strjoin("PWD=", pwd);
// 	if (tmp == NULL)
// 		return (-1);
// 	if (ft_add_env(tmp, env) == -1)
// 		return (free(tmp), -1);
// 	(free(tmp), free(pwd));
// 	tmp = ft_strjoin("OLDPWD=", old);
// 	if (tmp == NULL)
// 		return (-1);
// 	if (ft_add_env(tmp, env) == -1)
// 		return (free(tmp), -1);
// 	(free(old), free(tmp));
// 	exit_stat(0);
// 	return (1);
// }

// // int	ft_cd(char **args, char ***env)
// s_env	*execute_cd(char **args, s_env *lst)
// {
// 	char	*pwd;
// 	char	*old;

// 	old = getcwd(NULL, 0);
// 	if (args[1] == NULL)
// 	{
// 		if (chdir(ft_getenv("HOME", *env)) != 0)
// 			return (ft_throw(strerror(errno), NULL, 0, 1), -1);
// 	}
// 	else
// 	{
// 		if (chdir(args[1]) != 0)
// 			return (ft_throw(strerror(errno), args[1], 0, 1), -1);
// 	}
// 	pwd = getcwd(NULL, 0);
// 	return (set_oldpwd(env, pwd, old));
// }

// Fonction pour créer une nouvelle variable d'environnement
// s_env *new_env_var(char *key, char *value)
// {
// 	s_env *new_var = malloc(sizeof(s_env));
// 	if (!new_var)
// 		return NULL;
// 	new_var->key = strdup(key);
// 	new_var->value = strdup(value);
// 	new_var->next = NULL;
// 	return new_var;
// }

// // Fonction pour ajouter ou mettre à jour une variable d'environnement
// int set_env_var(s_env **lst, char *key, char *value)
// {
// 	s_env *current = *lst;
// 	while (current)
// 	{
// 		if (strcmp(current->key, key) == 0)
// 		{
// 			free(current->value);
// 			current->value = strdup(value);
// 			return 0;
// 		}
// 		current = current->next;
// 	}
// 	// Si la variable n'existe pas, l'ajouter
// 	s_env *new_var = new_env_var(key, value);
// 	if (!new_var)
// 		return -1;
// 	new_var->next = *lst;
// 	*lst = new_var;
// 	return 0;
// }

// // Fonction pour obtenir la valeur d'une variable d'environnement
// char *get_env_var(s_env *lst, char *key)
// {
// 	(void)key;
// 	while (lst)
// 	{
// 		if (strcmp(lst->key, key) == 0)
// 			return lst->value;
// 		lst = lst->next;
// 	}
// 	return NULL;
// }

// // Fonction pour définir PWD et OLDPWD
// int set_oldpwd(s_env **lst, char *pwd, char *old)
// {
// 	if (set_env_var(lst, "PWD", pwd) == -1)
// 		return -1;
// 	if (set_env_var(lst, "OLDPWD", old) == -1)
// 		return -1;
// 	free(pwd);
// 	free(old);
// 	return 0;
// }

// // Fonction principale pour changer de répertoire
// s_env *execute_cd(char **args, s_env *lst)
// {
// 	char *pwd;
// 	char *old;

// 	old = getcwd(NULL, 0);
// 	if (args[1] == NULL)
// 	{
// 		char *home = get_env_var(lst, "HOME");
// 		if (home == NULL)
// 		{
// 			fprintf(stderr, "cd: HOME not set\n");
// 			return lst;
// 		}
// 		if (chdir(home) != 0)
// 		{
// 			perror("cd");
// 			return lst;
// 		}
// 	}
// 	else
// 	{
// 		if (chdir(args[1]) != 0)
// 		{
// 			perror("cd");
// 			return lst;
// 		}
// 	}
// 	pwd = getcwd(NULL, 0);
// 	if (set_oldpwd(&lst, pwd, old) == -1)
// 		perror("set_oldpwd");
// 	return lst;
// }

// export a="'t"

// Fonction pour créer une nouvelle variable d'environnement
// s_env *new_env_var(char *key, char *value)
// {
// 	s_env *new_var = malloc(sizeof(s_env));
// 	if (!new_var)
// 		return NULL;
// 	new_var->value = strdup(value);
// 	new_var->next = NULL;
// 	return new_var;
// }

// // Fonction pour ajouter ou mettre à jour une variable d'environnement
// int set_env_var(s_env **lst, char *key, char *value)
// {
// 	s_env *current = *lst;
// 	while (current)
// 	{
// 		if (strcmp(current->key, key) == 0)
// 		{
// 			free(current->value);
// 			current->value = strdup(value);
// 			return 0;
// 		}
// 		current = current->next;
// 	}
// 	// Si la variable n'existe pas, l'ajouter
// 	s_env *new_var = new_env_var(key, value);
// 	if (!new_var)
// 		return -1;
// 	new_var->next = *lst;
// 	*lst = new_var;
// 	return 0;
// }

// // Fonction pour obtenir la valeur d'une variable d'environnement
// char *get_env_var(s_env *lst, char *key)
// {
// 	while (lst)
// 	{
// 		if (strcmp(lst->key, key) == 0)
// 		{
// 			return lst->value;
// 		}
// 		lst = lst->next;
// 	}
// 	return NULL;
// }

// // Fonction pour définir PWD et OLDPWD
// int set_oldpwd(s_env **lst, char *pwd, char *old)
// {
// 	if (set_env_var(lst, "PWD", pwd) == -1)
// 		return -1;
// 	if (set_env_var(lst, "OLDPWD", old) == -1)
// 		return -1;
// 	free(pwd);
// 	free(old);
// 	return 0;
// }

// // // Fonction principale pour changer de répertoire
// s_env *execute_cd(char **args, s_env *lst)
// {
// 	char *pwd = NULL;
// 	char *old = NULL;
// 	char *home = NULL;

// 	old = getcwd(NULL, 0);
// 	if (old == NULL)
// 	{
// 		perror("getcwd");
// 		return lst;
// 	}

// 	if (args[1] == NULL)
// 	{
// 		home = get_env_var(lst, "HOME");
// 		if (home == NULL)
// 		{
// 			fprintf(stderr, "cd: HOME not set\n");
// 			free(old);
// 			return lst;
// 		}
// 		if (chdir(home) != 0)
// 		{
// 			perror("cd");
// 			free(old);
// 			return lst;
// 		}
// 	}
// 	else
// 	{
// 		if (chdir(args[1]) != 0)
// 		{
// 			perror("cd");
// 			free(old);
// 			return lst;
// 		}
// 	}

// 	pwd = getcwd(NULL, 0);
// 	if (pwd == NULL)
// 	{
// 		// perror("getcwd");
// 		// free(old);
// 		// return lst;
// 		pwd = get_env_var(lst, "OLDPWD");
// 	}

// 	if (set_oldpwd(&lst, pwd, old) == -1)
// 	{
// 		perror("set_oldpwd");
// 		return lst;
// 	}

// 	return lst;
// }
// -----------------------
// Fonction pour créer une nouvelle variable d'environnement
s_env *new_env_var(char *key, char *value)
{
	s_env *new_var = malloc(sizeof(s_env));
	if (!new_var)
		return NULL;
	new_var->key = strdup(key);
	new_var->value = strdup(value);
	new_var->next = NULL;
	return new_var;
}

// Fonction pour ajouter ou mettre à jour une variable d'environnement
int set_env_var(s_env **lst, char *key, char *value)
{
	s_env *current = *lst;
	while (current)
	{
		if (strcmp(current->key, key) == 0)
		{
			free(current->value);
			current->value = strdup(value);
			return 0;
		}
		current = current->next;
	}
	s_env *new_var = new_env_var(key, value);
	if (!new_var)
		return -1;
	new_var->next = *lst;
	*lst = new_var;
	return 0;
}

// Fonction pour obtenir la valeur d'une variable d'environnement
char *get_env_var(s_env *lst, char *key)
{
	while (lst)
	{
		if (strcmp(lst->key, key) == 0)
		{
			return lst->value;
		}
		lst = lst->next;
	}
	return NULL;
}

// Fonction pour définir PWD et OLDPWD
int set_oldpwd(s_env **lst, char *pwd, char *old)
{
	if (set_env_var(lst, "PWD", pwd) == -1)
		return -1;
	if (set_env_var(lst, "OLDPWD", old) == -1)
		return -1;
	free(pwd);
	free(old);
	return 0;
}

// Fonction auxiliaire pour obtenir la nouvelle destination
char *ft_getdes(s_env *lst, char *des)
{
	if (!des)
	{
		des = get_env_var(lst, "HOME");
		if (!des)
		{
			fprintf(stderr, "cd: HOME not set\n");
			return NULL;
		}
	}
	return strdup(des);
}

// Fonction principale pour changer de répertoire
s_env *execute_cd(char **args, s_env *lst)
{
	char *pwd = NULL;
	char *old = NULL;
	char *des = NULL;

	des = ft_getdes(lst, args[1]);
	if (!des)
		return lst;

	old = getcwd(NULL, 0);
	if (chdir(des) == -1)
	{
		if (!set_env_var(&lst, "OLDPWD", old))
		{
			pwd = getcwd(NULL, 0);
			printf("pwd : %s\n", pwd);
			if (!pwd)
			{
				pwd = get_env_var(lst, "OLDPWD");
			}
			if (pwd && !set_env_var(&lst, "PWD", pwd))
			{
				free(pwd);
				free(old);
				free(des);
				return lst;
			}
		}
	}
	free(pwd);
	free(old);
	free(des);
	return lst;
}

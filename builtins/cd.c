/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:00:00 by sdiouane          #+#    #+#             */
/*   Updated: 2024/07/16 23:01:10 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	set_oldpwd(t_env	**lst, char	*pwd, char	*old)
{
	if (set_env_var(lst, "PWD", pwd) == -1)
		return (-1);
	if (set_env_var(lst, "OLDPWD", old) == -1)
		return (-1);
	free(pwd);
	free(old);
	return (0);
}

char	*ft_getdes(t_env	*lst, char	*des)
{
	if (!des)
	{
		des = get_env_var(lst, "HOME");
		if (!des)
		{
			fprintf(stderr, "cd: HOME not set\n");
			return (NULL);
		}
	}
	return (ft_strdup(des));
}

int	set_old_pwd(char	*old, t_env	*lst, char	*des)
{
	old = getcwd(NULL, 0);
	if (!old)
	{
		old = get_env_var(lst, "PWD");
		if (!old)
			(perror("getcwd"), old = ft_strdup(""));
		else
			old = ft_strdup(old);
		if (!old)
			return (free(des), 1);
	}
	return (free(old), 0);
}

static void	ft_error(char *cmd)
{
	int	ref;
	DIR	*ptr;

	ref = errno;
	ft_putstr_fd("minishell: ", 2);
	if (just_quotes(cmd))
		supprimerguillemets(cmd);
	ft_putstr_fd(cmd, 2);
	if (ref == 2)
	{
		ft_putendl_fd(": No such file or directory", 2);
		exit_stat(127);
	}
	else if (ref == 13)
	{
		ptr = opendir(cmd);
		if (ptr && !closedir(ptr))
			ft_putendl_fd(": is directory", 2);
		else
			ft_putendl_fd(": Permission denied", 2);
		exit_stat(126);
	}
	exit_stat(0);
}

t_env	*execute_cd(char	**args, t_env	*lst, char	*curr)
{
	char	*pwd;
	char	*old;
	char	*des;

	if (args[1] && strcmp(args[1], "~") == 0)
		des = ft_getdes(lst, get_env_var(lst, "HOME"));
	else
		des = ft_getdes(lst, args[1]);
	old = NULL;
	if (!des)
		return (free(curr), lst);
	if (set_old_pwd(old, lst, des))
		return (free(des), free(curr), exit_stat(1), lst);
	if (chdir(des) == -1)
		return (ft_error(des), free(old), free(des), free(curr), exit_stat(1),
			lst);
	if (set_env_var(&lst, "OLDPWD", curr) == -1)
		return (free(old), free(des), free(curr), exit_stat(1), lst);
	(free(old), pwd = getcwd(NULL, 0));
	if (!pwd)
	{
		pwd = ft_strdup(curr);
		if (!pwd)
			return (free(des), free(curr), lst);
	}
	if (set_env_var(&lst, "PWD", pwd) == -1)
		return (free(pwd), free(des), free(curr), lst);
	return (free(pwd), free(des), free(curr), exit_stat(1), lst);
}

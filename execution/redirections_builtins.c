/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_builtins.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 23:00:01 by sdiouane          #+#    #+#             */
/*   Updated: 2024/07/16 11:56:50 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int	redirection_double_out_builtins(char *redirection, int *fd)
{
	int flag;

	flag = 1;
	del_dbl_quotes(redirection);
	if (redirection)
	{
		*fd = open(redirection, O_WRONLY | O_CREAT | O_APPEND, 0666);
		if (*fd < 0)
			(put_errno_builtins(redirection), flag= -1);
		redirection = NULL;
		(dup2(*fd, STDOUT_FILENO), close(*fd));
	}
	else
		(put_ambiguous_builtins(redirection), flag = -1);
	return (flag);
}

int	redirection_in_builtins(char *oper, char *redirection, int *fd)
{
	char	*file;
	int		flag;

	flag = 1;
	file = file_nc(redirection);
	if (redirection != NULL)
	{
		if (redirection[0] == '\\')
			supprimer_protection(redirection);
		if (just_quotes(redirection) == 1)
		{
			ft_putendl_fd("minishell: : No such file or directory", 2);
			flag = -1;
		}
		else
			*fd = open(file, O_RDONLY);
		if (*fd < 0)
			(put_errno_builtins(redirection), flag = -1);
		if (!ft_strcmp(oper, "<<") || !ft_strcmp(oper, "<"))
			dup2(*fd, STDIN_FILENO);
		else
			(close(*fd), exit(0));
		(close(*fd), redirection = NULL);
	}
	else
		(put_ambiguous_builtins(redirection), flag = -1);
	free (file);
	return (flag);
}

int	redirection_out_builtins(char *redirection, int *fd)
{
	int flag;

	flag = 1;
	if (redirection)
	{
		del_dbl_quotes(redirection);
		del_sngl_quotes(redirection);
	}
	if (redirection)
	{
		del_dbl_quotes(redirection);
		*fd = open(redirection, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (*fd < 0)
			(put_errno(redirection), flag = -1);
		redirection = NULL;
		(dup2(*fd, STDOUT_FILENO), close(*fd));
	}
	else
		(put_ambiguous_builtins(redirection), flag = -1);
	return (flag);
}

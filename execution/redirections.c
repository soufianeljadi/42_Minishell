/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 23:00:01 by sdiouane          #+#    #+#             */
/*   Updated: 2024/07/20 12:01:19 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	just_quotes(char *str)
{
	while (*str)
	{
		if (*str != '"' && *str != '\'' && *str != ' ' && *str != '\t')
			return (0);
		str++;
	}
	return (1);
}

void	redirection_double_out(char *redirection, int *fd)
{
	if (redirection)
	{
		if (just_quotes(redirection) == 1)
		{
			ft_putendl_fd("minishell: : No such file or directory", 2);
			exit(EXIT_FAILURE);
		}
		ft_rm_quotes(redirection);
		*fd = open(redirection, O_WRONLY | O_CREAT | O_APPEND, 0666);
		if (*fd < 0)
			put_errno(redirection);
		redirection = NULL;
		(dup2(*fd, STDOUT_FILENO), close(*fd));
	}
	else
		put_ambiguous(redirection);
}

void	redirection_in(char *oper, char *redirection, int *fd)
{
	if (redirection != NULL)
	{
		if (just_quotes(redirection) == 1)
		{
			ft_putendl_fd("minishell: : No such file or directory", 2);
			exit(EXIT_FAILURE);
		}
		else
		{
			ft_rm_quotes(redirection);
			*fd = open(redirection, O_RDONLY);
		}
		if (*fd < 0)
			put_errno(redirection);
		if (!ft_strcmp(oper, "<<") || !ft_strcmp(oper, "<"))
			dup2(*fd, STDIN_FILENO);
		else
			(close(*fd), exit(0));
		(close(*fd), redirection = NULL);
	}
	else
		put_ambiguous(redirection);
}

void	redirection_out(char *redirection, int *fd)
{
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
			put_errno(redirection);
		redirection = NULL;
		(dup2(*fd, STDOUT_FILENO), close(*fd));
	}
	else
		put_ambiguous(redirection);
}

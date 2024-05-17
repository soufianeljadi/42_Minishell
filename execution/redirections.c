/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 23:00:01 by sdiouane          #+#    #+#             */
/*   Updated: 2024/05/17 10:10:06 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *file_nc(char *s)
{
	int i;
	int x;
	char *f;
	
	i = 0;
	x = 0;
	if (!s)
		return (NULL);
	f = (char *)malloc(sizeof(char) * (strlen(s) + 1));
	if (f == NULL)
		exit(EXIT_FAILURE);
	while (s[i] != '\0')
	{
		if (s[i] == '"' || s[i] == '\'')
		{
			char quote = s[i];
			i++;
			while (s[i] != '\0' && s[i] != quote)
			{
				f[x] = s[i];
				i++;
				x++;
			}
			if (s[i] == '\0')
				exit(EXIT_FAILURE);
		}
		else
		{
			f[x] = s[i];
			x++;
		}
		i++;
	}
	f[x] = '\0';
	return f;
}


void redirection_double_out(char *redirection, int *fd)
{
	if (redirection)
	{
		if (redirection[0] == '$')
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(redirection, 2);
			ft_putstr_fd(": ambiguous redirect\n", 2);
			exit(EXIT_FAILURE);
		}
        *fd = open(file_nc(redirection), O_WRONLY | O_CREAT | O_APPEND, 0666);
		if (*fd < 0)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(redirection, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			exit(EXIT_FAILURE);
		}
		redirection = NULL;
        dup2(*fd, STDOUT_FILENO);
        close(*fd);
	}
}

void redirection_in(char *redirection, int *fd)
{
	if (redirection != NULL)
	{
		if (redirection[0] == '$')
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(redirection, 2);
			ft_putstr_fd(": ambiguous redirect\n", 2);
			exit(EXIT_FAILURE);
		}
		*fd = open(file_nc(redirection), O_RDONLY);
		if (*fd < 0)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(redirection, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			exit(EXIT_FAILURE);
		}
		redirection = NULL;
		dup2(*fd, STDIN_FILENO);
		close(*fd);
	}
}

void redirection_out(char *redirection, int *fd)
{
	if (redirection)
	{
		if (redirection[0] == '$')
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(redirection, 2);
			ft_putstr_fd(": ambiguous redirect\n", 2);
			exit(EXIT_FAILURE);
		}
        *fd = open(file_nc(redirection), O_WRONLY | O_CREAT | O_TRUNC, 0666);
        if (*fd < 0)
		{
            printf("minishell: %s: No such file or directory\n", redirection);
            exit(EXIT_FAILURE);
        }
		redirection = NULL;
        dup2(*fd, STDOUT_FILENO);
        close(*fd);
	}
}

void execute_with_redirection(ExecutionData *data)
{
    int fd_in;
    int fd_out;
	int i;
	char **red;

	(1) && (fd_in = -1, fd_out = -1, i = 0,
	red = line_to_args(data->lst->redirection));
	while (red[i])
	{
		if (!strcmp(red[i], "<"))
			redirection_in(red[i + 1], &fd_in);
		if (!strcmp(red[i], ">>"))
			redirection_double_out(red[i + 1], &fd_out);
		if (!strcmp(red[i], ">"))
			redirection_out(red[i + 1], &fd_out);
		if (!strcmp(red[i], "<<"))
			heredoc(red[i + 1], data);
		i++;
	}
	if (fd_in != -1)
		close(fd_in);
	if (fd_out != -1)
		close(fd_out);
	if (data->lst->cmd != NULL
		&& strspn(data->lst->cmd, " ") != strlen(data->lst->cmd))
			execute(data->lst->cmd, data->env);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 19:37:55 by sel-jadi          #+#    #+#             */
/*   Updated: 2024/05/17 10:57:03 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	go_heredoc( char *red, ExecutionData *data, int fd_doc)
{
	char	*line;

	while (1)
	{
		line = readline("<-heredoc-> ");
		if (!line)
			break ;
		if (ft_strncmp(line, red, ft_strlen(data->args[1]) + 1) == 0)
			break ;
		ft_putstr_fd(line, fd_doc);
		ft_putstr_fd("\n", fd_doc);
		free(line);
	}
	if (line != 0)
		free(line);
}

void	child_heredoc(char *red, ExecutionData *data, int *heredoc)
{
	signal(SIGINT, handle_sigint_heredoc);
	close(heredoc[0]);
	go_heredoc(red ,data, heredoc[1]);
	close(heredoc[1]);
	exit(0);
}

int	parent_heredoc(ExecutionData *data, int *heredoc)
{
	int	exit_status;

	signal(SIGINT, SIG_IGN);
	wait(&exit_status);
	close(heredoc[1]);
	if (WIFEXITED(exit_status))
	{
		exit_status = WEXITSTATUS(exit_status);
		if (exit_status == 1)
			return (-3);
		else
			data->lst->in = dup(heredoc[0]);
		close(heredoc[0]);
	}
	signals_init();
	return (0);
}

int	heredoc(char *red ,ExecutionData *data)
{
	int	pid;
	int	heredoc[2];
	int	i;

	i = pipe(heredoc);
	if (i == -1)
		exit(1);
	pid = fork();
	if (pid == 0)
		child_heredoc(red,data, heredoc);
	else
		return (parent_heredoc(data, heredoc));
	return (0);
}

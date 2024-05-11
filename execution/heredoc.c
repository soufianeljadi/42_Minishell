/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jadi <sel-jadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 19:37:55 by sel-jadi          #+#    #+#             */
/*   Updated: 2024/05/11 20:19:10 by sel-jadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	go_heredoc(ExecutionData *data, int fd_doc)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strncmp(line, data->args[1], ft_strlen(data->args[1]) + 1) == 0)
			break ;
		ft_putstr_fd(line, fd_doc);
		ft_putstr_fd("\n", fd_doc);
		free(line);
	}
	if (line != 0)
		free(line);
}

static void	child_heredoc(ExecutionData *data, int *heredoc)
{
    
	signal(SIGINT, handle_sigint_heredoc);
	close(heredoc[0]);
	go_heredoc(data, heredoc[1]);
	close(heredoc[1]);
	exit(0);
}
static int	parent_heredoc(ExecutionData *data, int *heredoc)
{
    (void)data;
	signal(SIGINT, SIG_IGN);
	close(heredoc[1]);
	signals_init();
	return (0);
}

int	heredoc(ExecutionData *data)
{
	int	pid;
	int	heredoc[2];
	int	i;

	i = pipe(heredoc);
	if (i == -1)
		exit(1);
	pid = fork();
	if (pid == 0)
		child_heredoc(data, heredoc);
	else
		return (parent_heredoc(data, heredoc));
	return (0);
}
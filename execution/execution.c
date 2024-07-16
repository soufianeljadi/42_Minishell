/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 22:14:48 by sdiouane          #+#    #+#             */
/*   Updated: 2024/07/15 01:28:36 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	protect_fork(int pid)
{
	if (pid == -1)
		(perror("fork"), exit(EXIT_FAILURE));
}

void	check_sign(t_data *data)
{
	if (g_signal == 1 && (data->lst->cmd || data->lst->redirection))
		exit (0);
}

static pid_t	execute_command(t_data *data)
{
	pid_t	pid;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		exit(EXIT_FAILURE);
	pid = fork();
	protect_fork(pid);
	if (pid == 0)
	{
		check_sign(data);
		signal(SIGINT, SIG_DFL);
		if (data->lst->next != NULL)
			if (dup2(pipefd[1], STDOUT_FILENO) == -1)
				(perror("dup2"), exit(EXIT_FAILURE));
		(close(pipefd[1]), close(pipefd[0]));
		(handle_child_process(data), exit(EXIT_SUCCESS));
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		if (dup2(pipefd[0], STDIN_FILENO) == -1)
			(perror("dup2"), exit(EXIT_FAILURE));
		(close(pipefd[1]), close(pipefd[0]));
	}
	return (pid);
}

int	multiple_cmds(t_data *data, int size)
{
	int			i;
	int			pid;
	t_noued_cmd	*tmp;
	t_noued_cmd	*next;
	t_noued_cmd	*begin;

	(1) && (i = 1, pid = -1);
	begin = NULL;
	begin = data->lst;
	while (data->lst)
	{
		tmp = data->lst;
		next = tmp->next;
		if (i == size)
			pid = execute_command(data);
		else
			execute_command(data);
		data->lst = next;
		i++;
	}
	free_noued_cmd(begin);
	return (pid);
}

void	ft_execution(t_data *data)
{
	int	st;
	int	size;
	int	pid;

	if (g_signal == 1 && data->lst->cmd && data->lst->redirection)
		return ;
	(1) && (pid = 0, size = ft_lstsize(data->lst));
	data->env = struct_to_char(&data->export_i);
	(add_last_cmd(&data->export_i, data->args), signal(SIGINT, SIG_IGN));
	if (size == 1 && check_bultin(data->args[0]) == 1)
		(execute_with_redirection(data), builtins(data));
	else
	{
		signal(SIGINT, SIG_IGN);
		(1) && (pid = multiple_cmds(data, size), waitpid(pid, &st, 0));
		while (0 < wait(NULL))
			;
		if (g_signal == 1)
			exit_stat(1);
		else if (WIFSIGNALED(st))
			exit_stat(128 + WTERMSIG(st));
		else
			exit_stat(WEXITSTATUS(st));
	}
	(signals_init(), ft_free_tab(data->env));
}

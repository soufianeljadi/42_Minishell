/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 22:14:48 by sdiouane          #+#    #+#             */
/*   Updated: 2024/06/10 06:10:21 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_execut_error(char *cmd)
{
	int ref;
	DIR *ptr;

	ref = errno;
	ft_putstr_fd("minishell: ", 2);
	if (just_quotes(cmd))
		supprimerGuillemets(cmd);
	ft_putstr_fd(cmd, 2);
	if (ref == 2)
	{
		ft_putendl_fd(": command not found", 2);
		exit(127);
	}
	else if (ref == 13)
	{
		ptr = opendir(cmd);
		if (ptr && !closedir(ptr))
			ft_putendl_fd(": is directory", 2);
		else
			ft_putendl_fd(": Permission denied", 2);
		exit(126);
	}
	exit(0);
}

void remove_outermost_quotes(char *str)
{
	int len;

	len = ft_strlen(str);
	if (len < 2)
		return;

	if (str[0] == '"' || str[0] == '\'')
	{
		memmove(str, str + 1, len - 1);
		str[len - 1] = '\0';
		len--;
	}
	if (str[len - 1] == '"' || str[len - 1] == '\'')
		str[len - 1] = '\0';
}

void check_error(char **cmd, char **env, char *chemin)
{
	if (cmd[0][0] == '.' || cmd[0][0] == '/')
		if (execve(cmd[0], cmd, env) == -1)
			(ft_execut_error(cmd[0]), ft_free_tab(cmd), exit(0));
	if (execve(chemin, cmd, env) == -1 && strcmp(cmd[0], "\0"))
	{
		if (strcmp(cmd[0], "\0"))
			(ft_execut_error(cmd[0]), ft_free_tab(cmd), exit(0));
	}
}

void execute(char *s, char **env, t_data *data)
{
	char    *chemin;
	char    **cmd;

	(1) && (cmd = NULL, chemin = NULL);
	if (*env)
	{
		cmd = check_quotes_before_execution(s);
		if (cmd[0] == NULL)
			exit(exit_stat(1));
		chemin = get_path(cmd[0], env);
		if (chemin == NULL)
			(ft_free_tab(cmd), exit(EXIT_FAILURE));
		if (check_bultin(data->lst->cmd) == 0)
		{
			if (cmd[0][0] == '.' || cmd[0][0] == '/')
				if (execve(cmd[0], cmd, env) == -1)
					(ft_execut_error(cmd[0]), ft_free_tab(cmd), exit(EXIT_FAILURE));
			if (execve(chemin, cmd, env) == -1 && strcmp(cmd[0], "\0"))
				if (strcmp(cmd[0], "\0"))
					(ft_execut_error(cmd[0]) ,ft_free_tab(cmd), exit(EXIT_FAILURE));
		}
		else
			(execute_with_redirection(data), builtins(data));
	}
}

static void handle_child_process(t_data *data)
{
	if (data->lst->redirection != NULL)
		execute_with_redirection(data);
	if (data->lst->cmd != NULL)
		execute(data->lst->cmd, data->env, data);
}

static pid_t execute_command(t_data *data)
{
	pid_t pid;
	int pipefd[2];

	if (pipe(pipefd) == -1 || (pid = fork()) == -1)
		exit(EXIT_FAILURE);
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		if (data->lst->next != NULL)
			dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		close(pipefd[0]);
		handle_child_process(data);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[1]);
		close(pipefd[0]);
	}
	return (pid);
}

int	check_bultin(char *cmd)
{
	if (!strcmp(cmd, "echo"))
		return (1);
	else if (!strcmp(cmd, "cd"))
		return (1);
	else if (!strcmp(cmd, "pwd"))
		return (1);
	else if (!strcmp(cmd, "export"))
		return (1);
	else if (!strcmp(cmd, "unset"))
		return (1);
	else if (!strcmp(cmd, "env"))
		return (1);
	else if (!strcmp(cmd, "exit"))
		return (1);
	return (0);
}

int multiple_cmds(t_data *data, int size)
{
	int i;
	int pid;
	
	i = 1;
	while (data->lst)
	{
		g_flags.envire = ft_merge_envr(data->export_i);
		if (i == size)
			pid = execute_command(data);
		else
		{
			execute_command(data);
		}
		data->lst = data->lst->next;
		i++;
	}
	return (pid);
}

void ft_execution(t_data *data)
{
	int st;
	int	size;
	int	pid = 0;

	size = ft_lstsize(data->lst);
	data->env = struct_to_char(&data->export_i);
	add_last_cmd(&data->export_i, data->args);
	signal(SIGINT, SIG_IGN);
	if (size == 1 && check_bultin(data->args[0]) == 1)
	{
		execute_with_redirection(data);
		builtins(data);
	}
	else 
	{
		signal(SIGINT, SIG_IGN);
		pid = multiple_cmds(data, size);
	}
	waitpid(pid, &st, 0);
	while (0 < wait(NULL))
		;
	exit_stat(WEXITSTATUS(st));
	// if (WIFEXITED(st))
	// 	exit_stat(WEXITSTATUS(st));
	// else if (WIFSIGNALED(st))
		exit_stat(st);
	signals_init();
}
// void ft_execution(t_data *data)
// {
// 	int st;
// 	int	size;
// 	int	pid = 0;

// 	size = ft_lstsize(data->lst);
// 	data->env = struct_to_char(&data->export_i);
// 	add_last_cmd(&data->export_i, data->args);
// 	signal(SIGINT, SIG_IGN);
	// if (size == 1 && check_bultin(data->args[0]) == 1)
	// {
	// 	execute_with_redirection(data);
	// 	builtins(data);
	// }
// 	else 
// 	{
// 		signal(SIGINT, SIG_IGN);
// 		pid = multiple_cmds(data, size);
// 	}
// 	waitpid(pid, &st, 0);
// 	while (0 < wait(NULL))
// 		;
// 	exit_stat(WEXITSTATUS(st));
// 	signals_init();
// }

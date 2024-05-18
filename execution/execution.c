/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 22:14:48 by sdiouane          #+#    #+#             */
/*   Updated: 2024/05/18 14:00:17 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int  ft_execut_error(char *cmd)
{
    int         ref;
    DIR         *ptr;

    ref = errno;
    ft_putstr_fd("minishell: ", 2);
    ft_putstr_fd(cmd, 2);
    if (ref == 2)
    {
        ft_putendl_fd(": command not found", 2);
        return (127);
    }
    else if (ref == 13)
    {
        ptr = opendir(cmd);
        if (ptr && !closedir(ptr))
            ft_putendl_fd(": is directory", 2);
        else
        {
            ft_putstr_fd(": ", 2);
            ft_putendl_fd(strerror(ref), 2);
        }
        return (126);
    }
    return (0);
}


void execute(char *s, char **env)
{
	char	*chemin;
	char	**cmd;

	(1) && (cmd = NULL, chemin = NULL);
	if (*env)
	{
		
		cmd = check_quotes_before_execution(s);
		if (cmd[0][0] == '\'')
			del_sngl_quotes(cmd[0]);
		else if (cmd[0][0] == '\"')
			del_dbl_quotes(cmd[0]);
		chemin = get_path(cmd[0], env);
		if (execve(chemin, cmd, env) == -1 /*&& strcmp(cmd[0], "\0")*/)
		{
			if (strcmp(cmd[0], "\0"))
				ft_execut_error(cmd[0]);
			(ft_free_tab(cmd), exit(EXIT_FAILURE));
		}
	}
}

static void handle_child_process(ExecutionData *data)
{
	if (data->lst->redirection != NULL)
	{
		execute_with_redirection(data);
	}
	else
	{
		if (data->lst->cmd != NULL)
		{
			if (builtins(data) == 1)
				execute(data->lst->cmd, data->env);
			exit(EXIT_SUCCESS);
		}
	}
}

static void execute_command(ExecutionData *data)
{
	int pipefd[2];
    pid_t pid;

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
}


void	ft_execution(ExecutionData *data)
{
    add_last_cmd(&data->export_i, data->args);
	if (!ft_strncmp(data->args[0], "<<", 2) && !data->args[1])
		(syntax_error(), exit(EXIT_FAILURE));
	if (data->lst->next == NULL)
	{
		if (builtins(data) == 1)
			execute_command(data);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		while (data->lst)
		{
			g_flags.envire = ft_merge_envr(data->export_i);
			if (builtins(data) == 1)
				execute_command(data);
			data->lst = data->lst->next;         
		}
	}
    while (0 < wait(NULL))
		;
}

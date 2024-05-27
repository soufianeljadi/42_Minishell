/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 22:14:48 by sdiouane          #+#    #+#             */
/*   Updated: 2024/05/27 23:24:28 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int  ft_execut_error(char *cmd)
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
            
        }
        return (126);
    }
    return (0);
}

void remove_outermost_quotes(char *str)
{
    int len = strlen(str);
    if (len < 2) return; // If the string is too short, do nothing

    // Remove leading quote
    if (str[0] == '"' || str[0] == '\'')
	{
        memmove(str, str + 1, len - 1);
        str[len - 1] = '\0';
        len--;
    }

    // Remove trailing quote
    if (str[len - 1] == '"' || str[len - 1] == '\'')
        str[len - 1] = '\0';
}


void execute(char *s, char **env, ExecutionData *data)
{
	char    *chemin;
	char    **cmd;

	(1) && (cmd = NULL, chemin = NULL);
	if (*env)
	{
		cmd = check_quotes_before_execution(s);
		if (cmd[0] == NULL)
			exit(EXIT_FAILURE);
		chemin = get_path(cmd[0], env);
		if (chemin == NULL)
			(ft_free_tab(cmd), exit(EXIT_FAILURE));
		if (builtins(data) == 1)
		{
			if (cmd[0][0] == '.' || cmd[0][0] == '/')
				if (execve(cmd[0], cmd, env) == -1)
					(ft_execut_error(cmd[0]), ft_free_tab(cmd), exit(EXIT_FAILURE));
			if (execve(chemin, cmd, env) == -1 && strcmp(cmd[0], "\0"))
			{
				if (strcmp(cmd[0], "\0"))
					(ft_execut_error(cmd[0]), ft_free_tab(cmd), exit(EXIT_FAILURE));
			}
		}
	}
}

static void handle_child_process(ExecutionData *data)
{
	if (data->lst->redirection != NULL)
		execute_with_redirection(data);
	else if (data->lst->cmd != NULL)
		execute(data->lst->cmd, data->env, data);
}

static void execute_command(ExecutionData *data)
{
    pid_t	pid;
	int		pipefd[2];

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
	data->env = struct_to_char(&data->export_i);
    add_last_cmd(&data->export_i, data->args);
	if (!ft_strncmp(data->args[0], "<<", 2) && !data->args[1])
		(syntax_error(), exit(EXIT_FAILURE));
	if (data->lst->next == NULL)
	{
		signal(SIGINT, SIG_IGN);
		if (builtins(data) == 1)
			execute_command(data);
		// handle_child_process(data);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		while (data->lst)
		{
			g_flags.envire = ft_merge_envr(data->export_i);
			execute_command(data);
			data->lst = data->lst->next;         
		}
	}
    while (0 < wait(NULL))
		;
}

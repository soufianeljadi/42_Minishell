/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 22:14:48 by sdiouane          #+#    #+#             */
/*   Updated: 2024/05/29 18:56:19 by sdiouane         ###   ########.fr       */
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

	(void)data;
	(1) && (cmd = NULL, chemin = NULL);
	if (*env)
	{
		printf("----->|%s|\n", s);
		cmd = check_quotes_before_execution(s);
		if (cmd[0] == NULL)
			exit(EXIT_FAILURE);
		chemin = get_path(cmd[0], env);
		if (chemin == NULL)
			(ft_free_tab(cmd), exit(EXIT_FAILURE));
		// if (builtins(data) == 1)
		// {
			printf("---->cmd[0] : |%s|\n", cmd[0]);
			if (cmd[0][0] == '.' || cmd[0][0] == '/')
				if (execve(cmd[0], cmd, env) == -1)
					(ft_execut_error(cmd[0]), ft_free_tab(cmd), exit(EXIT_FAILURE));
			if (execve(chemin, cmd, env) == -1 && strcmp(cmd[0], "\0"))
			{
				if (strcmp(cmd[0], "\0"))
					(ft_execut_error(cmd[0]), ft_free_tab(cmd), exit(EXIT_FAILURE));
			}
		// }
		// exit(EXIT_SUCCESS);
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
		if (builtins(data) == 0)
		{
			if (data->lst->redirection != NULL)
			{
				execute_with_redirection(data);
			}
		}
		else if (builtins(data) == 1)
		{		
			execute_command(data);
		}
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


// void	ft_execution(ExecutionData *data)
// {
// 	int pipe_fd[2];
// 	int saved_stdout;
// 	int status;

// 	// Convert environment variables to char **
// 	data->env = struct_to_char(&data->export_i);
// 	add_last_cmd(&data->export_i, data->args);
// 	// Check for syntax error with heredoc (<<)
// 	if (!ft_strncmp(data->args[0], "<<", 2) && !data->args[1])
// 	{
// 		syntax_error();
// 		exit(EXIT_FAILURE);
// 	}

// 	if (data->lst->next == NULL)
// 	{
// 		// Single command handling
// 		signal(SIGINT, SIG_IGN);

// 		if (builtins(data) == 0)
// 		{
// 			// Create a pipe
// 			if (pipe(pipe_fd) == -1)
// 			{
// 				perror("pipe");
// 				exit(EXIT_FAILURE);
// 			}

// 			// Save the current stdout
// 			saved_stdout = dup(STDOUT_FILENO);
// 			if (saved_stdout == -1)
// 			{
// 				perror("dup");
// 				exit(EXIT_FAILURE);
// 			}

// 			// Redirect stdout to pipe write end
// 			if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
// 			{
// 				perror("dup2");
// 				exit(EXIT_FAILURE);
// 			}

// 			// Close the write end of the pipe in the parent process
// 			close(pipe_fd[1]);

// 			// Execute the builtin command (this should write to the pipe)
// 			if (builtins(data) == 0)
// 			{
// 				// Close the saved stdout
// 				close(saved_stdout);
// 				// Close the read end of the pipe in the parent process
// 				close(pipe_fd[0]);
// 				return;
// 			}

// 			// Restore the original stdout
// 			if (dup2(saved_stdout, STDOUT_FILENO) == -1)
// 			{
// 				perror("dup2");
// 				exit(EXIT_FAILURE);
// 			}

// 			// Close the saved stdout
// 			close(saved_stdout);

// 			// Read from the pipe (this will be used as stdin for redirections)
// 			char buffer[1024];
// 			ssize_t count;

// 			while ((count = read(pipe_fd[0], buffer, sizeof(buffer) - 1)) > 0)
// 			{
// 				buffer[count] = '\0';
// 				// Here you would process the output from the builtin command
// 				// For now, we'll just print it
// 				write(STDOUT_FILENO, buffer, count);
// 			}

// 			// Close the read end of the pipe
// 			close(pipe_fd[0]);

// 			// Execute with redirection if necessary
// 			if (data->lst->redirection != NULL)
// 			{
// 				execute_with_redirection(data);
// 			}
// 		}
// 		else if (builtins(data) == 1)
// 		{
// 			execute_command(data);
// 		}
// 	}
// 	else
// 	{
// 		// Multiple command handling
// 		signal(SIGINT, SIG_IGN);
// 		while (data->lst)
// 		{
// 			g_flags.envire = ft_merge_envr(data->export_i);
// 			execute_command(data);
// 			data->lst = data->lst->next;
// 		}
// 	}

// 	// Wait for all child processes to finish
// 	while (wait(&status) > 0)
// 		;
// }

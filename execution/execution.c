/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 22:14:48 by sdiouane          #+#    #+#             */
/*   Updated: 2024/04/01 00:43:36 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	execute(char *s, char **env)
{
	char	*chemin;
	char	**cmd;

	cmd = ft_split(s, ' '); // ls -la 
	chemin = get_path(cmd[0], env); // /bin/kkk/ls
	if (execve(chemin, cmd, env) == -1)
	{
		ft_putstr_fd("Command not found!!", 2);
		ft_putendl_fd(cmd[0], 2);
		ft_free_tab(cmd);
		exit(EXIT_FAILURE);
	}
}

// static void execute_with_redirection(char *cmd, char **env, char *redirection)
// {
// 	char *chemin;
// 	char **args;

// 	args = ft_split(cmd, ' ');
// 	chemin = get_path(args[0], env);
	
// 	if (chemin != NULL)
// 	{
// 		int fd = -1;

// 		if (redirection != NULL) 
// 		{
// 			if (redirection[0] == '>')
// 			{
// 				fd = open(redirection + 1, O_WRONLY | O_CREAT | O_TRUNC, 0666);
// 				if (fd < 0)
// 				{
// 					perror("Cannot open file for writing");
// 					exit(EXIT_FAILURE);
// 				}
// 				dup2(fd, STDOUT_FILENO);
// 			}
// 			else if (redirection[0] == '<')
// 			{
// 				fd = open(redirection + 1, O_RDONLY);
// 				if (fd < 0)
// 				{
// 					perror("Cannot open file for reading");
// 					exit(EXIT_FAILURE);
// 				}
// 				dup2(fd, STDIN_FILENO);
// 			}
// 			close(fd);
// 		}
// 		execve(chemin, args, env);
// 		perror("Command execution failed");
// 		exit(EXIT_FAILURE);
// 	}
// 	else if (!chemin)
// 	{
// 		fprintf(stderr, "Command not found: [->%s<-]\n", args[0]);
// 		exit(EXIT_FAILURE);
// 	}
// }

static void execute_with_redirection(char *cmd, char **env, char *redirection)
{
    char *chemin;
    char **args;

    args = ft_split(cmd, ' ');
    chemin = get_path(args[0], env);
    
    if (chemin != NULL)
    {
        int fd = -1;

        if (redirection != NULL) 
        {
            // Parse the redirection string to handle multiple redirections
            char *token = strtok(redirection, ">");
            while (token != NULL)
            {
                // Skip leading spaces
                while (*token && *token == ' ')
                    token++;
                
                if (*token != '\0')
                {
                    // Open the file for writing
                    fd = open(token, O_WRONLY | O_CREAT | O_TRUNC, 0666);
                    if (fd < 0)
                    {
                        perror("Cannot open file for writing");
                        exit(EXIT_FAILURE);
                    }
                    // Redirect stdout to the file
                    dup2(fd, STDOUT_FILENO);
                    close(fd); // Close the file descriptor after redirection
                }
                token = strtok(NULL, ">");
            }
        }
        // Execute the command
        execve(chemin, args, env);
        perror("Command execution failed");
        exit(EXIT_FAILURE);
    }
    else if (!chemin)
    {
        fprintf(stderr, "Command not found: [->%s<-]\n", args[0]);
        exit(EXIT_FAILURE);
    }
}

void ft_execution(noued_cmd *lst, char **args, s_env *s_env, char **env)
{
	(void)s_env;
	(void)args;
	int pipefd[2];
	int fd_in = 0;
	pid_t pid;

	if (!strcmp(args[0], "export") || !strcmp(args[0], "unset") /*|| !strcmp(args[0], "echo") */|| !strcmp(args[0], "cd") || !strcmp(args[0], "env"))
		builtins(args, s_env);
	else
	{
		while (lst)
		{
			if (pipe(pipefd) == -1 || (pid = fork()) == -1)
				exit(EXIT_FAILURE);
			else if (pid == 0)
			{
				dup2(fd_in, STDIN_FILENO);
				if (lst->next != NULL)
					dup2(pipefd[1], STDOUT_FILENO);
				close(pipefd[0]);
				if (lst->redirection != NULL)
					execute_with_redirection(lst->cmd, env, lst->redirection);
				else
					execute(lst->cmd, env);
			}
			else
			{
				// waitpid(pid, NULL, 0);
				close(pipefd[1]);
				fd_in = pipefd[0];
			}
				lst = lst->next;
		}
	}
	while (0 < wait(NULL))
		;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 23:52:10 by sdiouane          #+#    #+#             */
/*   Updated: 2024/03/31 01:47:24 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int only_spaces(char *str)
{
	int i = 0;
	while(str[i])
	{
		if(str[i] == ' ' || str[i] == '\t')
			i++;
		else
			return (0);	
	}
	return(1);
}

s_env *split_env(char **env)
{
	int i = 0;
	int j = 0;
	s_env	*lst = NULL;
	while (env[i])
	{
		j = 0;
		while (env[i][j] != '=')
			j++;
		ft_lstadd_back(&lst, ft_lstnew_data(ft_substr(env[i] ,j + 1 ,ft_strlen(env[i])) ,ft_substr(env[i] ,0 , j)));
		i++;
	}
	return (lst);
}

void	execute(char *s, char **env)
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

void execute_with_redirection(char *cmd, char **env, char *redirection)
{
    char *chemin;
    char **args;

    args = ft_split(cmd, ' ');
    chemin = get_path(args[0], env);
	
	if (!chemin)
	{
        fprintf(stderr, "Command not found: %s\n", args[0]);
        exit(EXIT_FAILURE);
    }
    // else if (chemin != NULL)
	// {
        int fd = -1;

        if (redirection != NULL) 
		{
            if (redirection[0] == '>')
			{
                fd = open(redirection + 1, O_WRONLY | O_CREAT | O_TRUNC, 0666);
                if (fd < 0)
				{
                    perror("Cannot open file for writing");
                    exit(EXIT_FAILURE);
                }
                dup2(fd, STDOUT_FILENO);
            }
			else if (redirection[0] == '<')
			{
                fd = open(redirection + 1, O_RDONLY);
                if (fd < 0)
				{
                    perror("Cannot open file for reading");
                    exit(EXIT_FAILURE);
                }
                dup2(fd, STDIN_FILENO);
            }
            close(fd);
        }
        execve(chemin, args, env);
        perror("Command execution failed");
        exit(EXIT_FAILURE);
    // }
}

void ft_execution(noued_cmd *lst, char **args, s_env *s_env, char **env)
{
    (void)s_env;
    (void)args;
    int pipefd[2];
    int fd_in = 0;
    pid_t pid;

	if (!strcmp(lst->cmd, args[0]))
		builtins(args, s_env);
	while (lst)
	{
		if (pipe(pipefd) == -1)
		{
			perror("Pipe error");
			exit(EXIT_FAILURE);
		}
		if ((pid = fork()) == -1)
		{
			perror("Fork error");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{ // Child process
			dup2(fd_in, STDIN_FILENO); // Replace stdin with fd_in  -> 0
			if (lst->next != NULL)
				dup2(pipefd[1], STDOUT_FILENO); // Replace stdout with pipe write end -> 1
			close(pipefd[0]); // Close unused pipe read end
			if (lst->redirection != NULL)
				execute_with_redirection(lst->cmd, env, lst->redirection);
			else
			{
				execute(lst->cmd, env);
			}
		}
		else
		{ // Parent process
			// waitpid(pid, NULL, 0);
			close(pipefd[1]); // Close pipe write end
			fd_in = pipefd[0]; // Save the read end of the pipe for the next iteration
		}
			lst = lst->next;
	}
	while (0 < wait(NULL))
		;
}


void	main_loop(char *line, s_env *s_env, char **env)
{
	(void)s_env;
	char **args = NULL;
	noued_cmd *cmd = NULL;
	while (42)
	{ 
		//read_line
		line = readline("Minishell :$ ");
		if (!line)
			(printf("exit\n"),exit(0));
		if(line != NULL && only_spaces(line) == 0)
		{
			// history :
			add_history(line);
			if(parsing(line) == 1)		
				syntax_error();
			else
			{
				// split_line_into_arguments :
				args = line_to_args(line);
				// split_args_by_pipe :
				cmd = split_args_by_pipe(args);
				// print_command_list(cmd);
				ft_execution(cmd, args, s_env, env);
				free (args);
				free_noued_cmd(cmd);
			}
			//exit
			if (strncmp(line, "exit", 4) == 0)
			{
				printf("exit\n");
				free(line);
				free(args);
				free_noued_cmd(cmd);
				break;
			}
		}
	}
	free(line);
	// clear_history();
	free_noued_cmd(cmd);
	ft_free_tab(args);
}

void	f(void)
{
	// system("lsof minishell > file");
	system("leaks minishell");
}


int main(int ac, char **av, char **env)
{
	(void)av;
	atexit(f);
	char *line = NULL;
	s_env *splited_env = NULL;

	if (ac != 1)
		(printf("Args not allowed !\n"),exit(EXIT_FAILURE));
	splited_env = split_env(env);
	//signals
	rl_catch_signals = 0;
	signal(SIGQUIT, signal_ctrl_c_d);
	signal(SIGINT, signal_ctrl_c_d);
	main_loop(line, splited_env, env);
	// free(line);
	free_s_env(splited_env);
	return 0;
}



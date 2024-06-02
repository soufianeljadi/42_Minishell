void ft_execution(noued_cmd *lst, char **args, char **env, s_env *export_i, char **null_env)
{
	(void)args;
	int pipefd[2];
	int fd_in = 0;
	pid_t pid;

	g_flags.envire = NULL;
	add_last_cmd(&export_i, args);
	if (!strcmp(args[0], "export") || !strcmp(args[0], "unset") || !strcmp(args[0], "env") || !strcmp(args[0], "echo") || !strcmp(args[0], "cd") || !strcmp(args[0], "exit") || !strcmp(args[0], "pwd"))
		builtins(args, export_i, env);
	else
	{
		signal(SIGINT, SIG_IGN);
		while (lst)
		{
			// $variables :
			if (check_variables(args, export_i) == 1)
			{
				g_flags.envire = ft_merge_envr(export_i);
				if (pipe(pipefd) == -1 || (pid = fork()) == -1)
					exit(EXIT_FAILURE);
				else if (pid == 0)
				{
					signal(SIGINT, SIG_DFL);
					if (lst->next != NULL)
					{
						dup2(pipefd[1], STDOUT_FILENO);
						close(pipefd[1]);
					}
					close(pipefd[0]);
					//supprimerGuillemets(lst->cmd);
					if (lst->redirection != NULL)
					{
						if (!env[0])
							execute_with_redirection(lst->cmd, null_env, lst->redirection);
						else
							execute_with_redirection(lst->cmd, env, lst->redirection);
					}
					else
					{
						// if (env[0])
						// 	pipeline(&lst->cmd);
						// else if (!env[0])
						// 	pipeline(lst->cmd);
						//ft_pipex();
						if (env[0])
							execute(lst->cmd, env, &export_i);
						else if (!env[0])
							execute(lst->cmd, null_env, &export_i);
					}
				}
				else
				{
					signal(SIGINT, SIG_IGN);
					close(pipefd[1]);
					fd_in = pipefd[0];
					close(pipefd[0]);
				}
			}
			else
			{
				printf("\n  zokkkkk  \n");
			}
			lst = lst->next;
			//wait(NULL);
		}
	}
	while (wait(NULL) >= 0)
		;
	signal(SIGINT, signal_ctrl_c_d);
}
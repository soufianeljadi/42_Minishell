/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jadi <sel-jadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 21:54:40 by sdiouane          #+#    #+#             */
/*   Updated: 2024/04/28 20:39:52 by sel-jadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "../minishell.h"

void	execute(char *s, char **env)
{
	char	*chemin;
	char	**cmd;

	cmd = ft_split(s, ' '); // ls -la 
	chemin = get_path(cmd[0], env); // /bin/kkk/ls
	if (execve(chemin, cmd, g_flags.envire) == -1)
	{
		ft_putstr_fd("Command not found!!", 2);
		ft_putendl_fd(cmd[0], 2);
		ft_free_tab(cmd);
		exit(0);
	}
}

int	open_file(char *s, int id)
{
	int	r;

	if (id == 0)
		r = open(s, O_RDONLY, 0777);
	if (id == 1)
		r = open(s, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (r == -1)
	{
		printf("permission denied \n");
		exit(EXIT_FAILURE);
	}
	return (r);
}

void	fils1(char **arv, int p[], char **env)
{
	int	fd;

	fd = open_file(arv[1], 0);
	dup2(fd, 0);
	dup2(p[1], 1);
	close(p[0]);
	execute(arv[2], env);
}

void	fils2(char **arv, int p[], char **env)
{
	int	fd;

	fd = open_file(arv[4], 1);
	dup2(fd, 1);
	dup2(p[0], 0);
	close(p[1]);
	execute(arv[3], env);
}

int	main(int arc, char **arv, char **env)
{
	int		p[2];
	pid_t	pid1;
	pid_t	pid2;
	int		status;

	if (arc != 5)
		exit(EXIT_FAILURE);
	pipe(p);
	if (pipe(p) == -1)
		exit(EXIT_FAILURE);
	pid1 = fork();
	if (pid1 == -1)
		exit(EXIT_FAILURE);
	if (pid1 == 0)
		fils1(arv, p, env);
	pid2 = fork();
	if (pid2 == -1)
		exit(EXIT_FAILURE);
	if (pid2 == 0)
		fils2(arv, p, env);
	close(p[0]);
	close(p[1]);
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
	return (0);
}

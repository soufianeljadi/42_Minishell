/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 23:00:01 by sdiouane          #+#    #+#             */
/*   Updated: 2024/05/11 18:47:33 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *file_nc(char *s)
{
	int i;
	int x;
	char *f;
	
	i = 0;
	x = 0;
	if (!s)
		return (NULL);
	f = (char *)malloc(sizeof(char) * (strlen(s) + 1));
	if (f == NULL)
		exit(EXIT_FAILURE);
	while (s[i] != '\0')
	{
		if (s[i] == '"' || s[i] == '\'')
		{
			char quote = s[i];
			i++;
			while (s[i] != '\0' && s[i] != quote)
			{
				f[x] = s[i];
				i++;
				x++;
			}
			if (s[i] == '\0')
				exit(EXIT_FAILURE);
		}
		else
		{
			f[x] = s[i];
			x++;
		}
		i++;
	}
	f[x] = '\0';
	return f;
}

char *ft_strsep(char **stringp, const char *delim)
{
	char *start;
	char *end;

	if (delim == NULL || *stringp == NULL || **stringp == '\0')
		return NULL;
	start = *stringp;
	end = strstr(start, delim);
	if (end)
	{
		*end = '\0';
		*stringp = end + strlen(delim);
	}
	else
		*stringp = NULL;

	return start;
}

static void redirection_double_out(char *redirection, int *fd)
{
            *fd = open(file_nc(redirection), O_WRONLY | O_CREAT | O_APPEND, 0666);
			if (*fd < 0)
			{
				printf("minishell: %s: No such file or directory\n", redirection);
				exit(EXIT_FAILURE);
			}
            dup2(*fd, STDOUT_FILENO);
            close(*fd);
}

static void redirection_in(char *redirection, int *fd)
{
			*fd = open(file_nc(redirection), O_RDONLY);
			if (*fd < 0)
			{
				printf("minishell: %s: No such file or directory\n", redirection);
				exit(EXIT_FAILURE);
			}
			dup2(*fd, STDIN_FILENO);
			close(*fd);
}

static void redirection_out(char *redirection, int *fd)
{
            *fd = open(file_nc(redirection), O_WRONLY | O_CREAT | O_TRUNC, 0666);
            if (*fd < 0)
			{
                printf("minishell: %s: No such file or directory\n", redirection);
                exit(EXIT_FAILURE);
            }
			dup2(*fd, STDIN_FILENO);
			close(*fd);
}

// char *here_doc_fct(char **args)
// {
// }

void execute_with_redirection(ExecutionData *data)
{
    int fd_in;
    int fd_out;
	int i;
	char **red;
	(1) && (fd_in = -1, fd_out = -1, i = 0, red = line_to_args(data->lst->redirection));
	while (red[i] != NULL)
	{
		printf("red[%d] = %s\n", i, red[i]);
		if (!strcmp(red[i], ">"))
			redirection_out(red[i + 1], &fd_out);
		else if (!strcmp(red[i], "<"))
			redirection_in(red[i + 1], &fd_in);
		else if (!strcmp(red[i], ">>"))
			redirection_double_out(red[i + 1], &fd_out);
		i++;
	}
	free (red);
	if (fd_in != -1)
		close(fd_in);
	if (fd_out != -1)
		close(fd_out);
	if (data->lst->cmd != NULL && strspn(data->lst->cmd, " ") != strlen(data->lst->cmd))
       		execute(data->lst->cmd, data->env);
}

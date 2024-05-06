/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 23:00:01 by sdiouane          #+#    #+#             */
/*   Updated: 2024/05/06 17:05:11 by sdiouane         ###   ########.fr       */
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
    char *token_out;
    char *ptr;
	char *token_double_out;
	
	token_out = NULL;
	token_double_out = NULL;
	ptr = redirection;
    while ((token_double_out = ft_strsep(&ptr, ">>")) != NULL)
    {
        while (*token_double_out && *token_double_out == ' ')
            token_double_out++;
        if (*token_double_out != '\0')
        {
            *fd = open(file_nc(token_double_out), O_WRONLY | O_CREAT | O_APPEND, 0666);
			if (*fd < 0)
			{
				printf("minishell: %s: No such file or directory\n", token_double_out);
				exit(EXIT_FAILURE);
			}
            dup2(*fd, STDOUT_FILENO);
            close(*fd);
        }
    }
}

static void redirection_in(char *redirection, int *fd)
{
	char *token_in;
	
	token_in = strtok(redirection, "<");
	while (token_in != NULL)
	{
		while (*token_in && *token_in == ' ')
			token_in++;
		if (*token_in != '\0')
		{
			*fd = open(file_nc(token_in), O_RDONLY);
			if (*fd < 0)
			{
				printf("minishell: %s: No such file or directory\n", token_in);
				exit(EXIT_FAILURE);
			}
			dup2(*fd, STDIN_FILENO);
			close(*fd);
		}
		token_in = strtok(NULL, "<");
	}
	
}

static int redirection_out(char *redirection, int *fd)
{
    char *token_out;
    char *ptr;
	
	token_out = NULL;
	ptr = redirection;
    while ((token_out = ft_strsep(&ptr, ">")) != NULL)
	{
        while (*token_out && *token_out == ' ')
            token_out++;
        if (*token_out != '\0')
		{
            *fd = open(file_nc(token_out), O_WRONLY | O_CREAT | O_TRUNC, 0666);
            if (*fd < 0) {
                printf("minishell: %s: No such file or directory\n", token_out);
                exit(EXIT_FAILURE);
            }
            dup2(*fd, STDOUT_FILENO);
            close(*fd);
            return (1);
        }
    }
    return (0);
}

// char *here_doc_fct(char **args)
// {
	
// }

void execute_with_redirection(char *cmd, char **env, char *redirection)
{
    int fd_in;
    int fd_out;
	
	fd_in = -1;
	fd_out = -1;
	int i = 0;
	char **red = ft_split(redirection, ' ');

	i = 0;

	while (red[i] && *red != NULL)
	{
		if (red[i][0] == '<')
			redirection_in(red[i], &fd_in);
		else if (red[i][0] == '>')
		{
			if (!redirection_out(red[i], &fd_out))
				return ;
		}
		else if (red[i][0] == '>' && red[i][1] == '>')
			redirection_double_out(red[i], &fd_out);
		i++;
	}
	if (fd_in != -1)
		close(fd_in);
	if (fd_out != -1)
		close(fd_out);

	if (cmd != NULL && strspn(cmd, " ") != strlen(cmd))
		execute(cmd, env);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 23:00:01 by sdiouane          #+#    #+#             */
/*   Updated: 2024/04/05 23:44:41 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


char *file_nc(char *s)
{
	int i = 0;
	int x = 0;
	char *f;
	
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

// static void redirection_in(char *redirection, int *fd)
// {
// 	char *token_in = strtok(redirection, "<");
// 	while (token_in != NULL)
// 	{
// 		while (*token_in && *token_in == ' ')
// 			token_in++;
// 		if (*token_in != '\0')
// 		{
// 			*fd = open(file_nc(token_in), O_RDONLY);
// 			if (*fd < 0)
// 				exit(EXIT_FAILURE);
// 			dup2(*fd, STDIN_FILENO);
// 			close(*fd);
// 		}
// 		token_in = strtok(NULL, "<");
// 	}
// }

// static void redirection_out(char *redirection, int *fd)
// {
// 	char *token_out = strtok(redirection, ">");
// 	while (token_out != NULL)
// 	{
// 		while (*token_out && *token_out == ' ')
// 			token_out++;
// 		if (*token_out != '\0')
// 		{
// 			*fd = open(file_nc(token_out), O_WRONLY | O_CREAT | O_TRUNC, 0666);
// 			if (*fd < 0)
// 				exit(EXIT_FAILURE);
// 			dup2(*fd, STDOUT_FILENO);
// 			close(*fd);
// 		}
// 		token_out = strtok(NULL, ">");
// 	}
// }

// void execute_with_redirection(char *cmd, char **env, char *redirection)
// {
// 	char *chemin;
// 	char **args;

// 	args = ft_split(cmd, ' ');
// 	chemin = get_path(args[0], env);
// 	if (chemin != NULL)
// 	{
// 		int fd_in = -1;
// 		int fd_out = -1;
// 		if (redirection != NULL) 
// 		{
//             if (strstr(redirection, "<") != NULL)
//                 redirection_in(redirection, &fd_in);
//             if (strstr(redirection, ">") != NULL)
//                 redirection_out(redirection, &fd_out);
// 		}
// 		execve(chemin, args, env);
// 		exit(EXIT_FAILURE);
// 	}
// 	else if (!chemin)
// 		exit(EXIT_FAILURE);
// }

// void execute_with_redirection(char *cmd, char **env, char *redirection)
// {
//     char *chemin;
//     char **args;

//     args = ft_split(cmd, ' ');
//     chemin = get_path(args[0], env);
//     if (chemin != NULL)
//     {
//         int fd_in = -1;
//         int fd_out = -1;
//         if (redirection != NULL)
//         {
//             if (strstr(redirection, "<") != NULL)
//             {
//                 if (strstr(redirection, "<") == redirection)
//                 {
//                     redirection_in_first(redirection, &fd_in);
//                 }
//                 else
//                 {
//                     redirection_in(redirection, &fd_in);
//                 }
//             }
//             if (strstr(redirection, ">") != NULL)
//                 redirection_out(redirection, &fd_out);
//         }
//         execve(chemin, args, env);
//         exit(EXIT_FAILURE);
//     }
//     else if (!chemin)
//         exit(EXIT_FAILURE);
// }


void redirection_in(char *redirection, int *fd)
{
    char *token_in = strtok(redirection, "<");
    while (token_in != NULL)
    {
        while (*token_in && *token_in == ' ')
            token_in++;
        if (*token_in != '\0')
        {
            *fd = open(file_nc(token_in), O_RDONLY);
            if (*fd < 0)
                exit(EXIT_FAILURE);
            dup2(*fd, STDIN_FILENO);
            close(*fd);
        }
        token_in = strtok(NULL, "<");
    }
}
void redirection_out(char *redirection, int *fd)
{
    char *token_out = strtok(redirection, ">");
    while (token_out != NULL)
    {
        while (*token_out && *token_out == ' ')
            token_out++;
        if (*token_out != '\0')
        {
            *fd = open(file_nc(token_out), O_WRONLY | O_CREAT | O_TRUNC, 0666);
            if (*fd < 0)
                exit(EXIT_FAILURE);
            dup2(*fd, STDOUT_FILENO);
            close(*fd);
        }
        token_out = strtok(NULL, ">");
    }
}

void execute_with_redirection(char *cmd, char **env, char *redirection)
{
    char *chemin;
    char **args;

    args = ft_split(cmd, ' ');
    chemin = get_path(args[0], env);
    if (chemin != NULL)
    {
        int fd_in = -1;
        int fd_out = -1;
        if (redirection != NULL)
        {
            if (strstr(redirection, "<") != NULL)
                redirection_in(redirection, &fd_in);
            if (strstr(redirection, ">") != NULL) {
                if (strstr(redirection, ">") == redirection) // Check if '>' is first
                    redirection_out(redirection, &fd_out);
                else
                    redirection_out(redirection, &fd_out);
            }
        }
        execve(chemin, args, env);
        exit(EXIT_FAILURE);
    }
    else if (!chemin)
        exit(EXIT_FAILURE);
}

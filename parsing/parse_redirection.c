/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 23:09:54 by sdiouane          #+#    #+#             */
/*   Updated: 2024/06/04 15:40:53 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
static int only_spaces__(char *line, int i)
{
	while (line[i] != '\0' && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i] == '\0' || line[i] == '|')
		return 1;
	return 0;
}

static int check_line(char *line, int i, int *r)
{
	// char **lines = ft_split(cmd, ' ');
	while (line[i])
	{
		if (line[i + 1] != '\0' && ((line[i] == '>' && line[i + 1] == '>') || (line[i] == '<' && line[i + 1] == '<')))
		{
			if (line[i + 2] != '\0' && (line[i + 2] == '<' || line[i + 2] == '>'))
			{
			printf("here\n");
				*r = 1;
				break;
			}
			i += 2;
			*r = only_spaces__(line, i);
			if (*r)
				break;
		}
		else if (line[i] == '>' || line[i] == '<')
		{
			if (line[i + 1] == '\0')
			{
				*r = 1;
				break;
			}
			*r = only_spaces__(line, i + 1);
			if (*r)
				break;
		}
		i++;
	}
	return (i);
}

int is_alpha_numirique(char *line)
{
	int i = 0;
	
	while (line[i])
	{
		if ((line[i] >= '0' && line[i] <= '9') || (line[i] >= 'a' && line[i] <= 'z') || (line[i] >= 'A' && line[i] <= 'Z'))
			i++;
		else
			return (1);
	}
	return (0);
}

void first_check(char *cmd, int i, int *t)
{
	char **line = ft_split(cmd, ' ');
	while (line[i])
	{
		if (!strcmp(line[i], "<<") && is_alpha_numirique(line[i + 1]))
		{
			printf("%s\t%s \n", line[i + 1], line[i + 2]);
			*t = 1;
			break ;
		}
		i++;
	}
	
}

int parse_redirection(char *line)
{
	int i;
	int r;
	int t;
	
	i = 0;
	r = 0;
	t = 0;
	while (line[i] != '\0' && line[i] <= 32)
		i++;
	i = check_line(line, i, &r);
	if (r == 1)
		return 1;
	i = 0;
	// first_check(line, i, &t);
	// if (t == 1)
	// 	return (1);
	return 0;
}

// ----------------------------2
// static int only_spaces__(char *line, int i)
// {
// 	while (line[i] != '\0' && (line[i] == ' ' || line[i] == '\t'))
// 		i++;
// 	if (line[i] == '\0' || line[i] == '|')
// 		return 1;
// 	return 0;
// }

// // static int check_line(char *line, int i, int *r)
// // {
// // 	while (line[i] != '\0')
// // 	{
// // 		if (line[i + 1] != '\0' && ((line[i] == '>' && line[i + 1] == '>') || (line[i] == '<' && line[i + 1] == '<')))
// // 		{
// // 			if (line[i + 2] != '\0' && (line[i + 2] == '<' || line[i + 2] == '>'))
// // 			{
// // 				printf("here\n");
// // 				*r = 1;
// // 				break;
// // 			}
// // 			i += 2;
// // 			*r = only_spaces__(line, i);
// // 			if (*r)
// // 				break;
// // 		}
// // 		else if (line[i] == '>' || line[i] == '<')
// // 		{
// // 			if (line[i + 1] == '\0')
// // 			{
// // 				*r = 1;
// // 				break;
// // 			}
// // 			*r = only_spaces__(line, i + 1);
// // 			if (*r)
// // 				break;
// // 		}
// // 		i++;
// // 	}
// // 	return (i);
// // }

// static int check_line(char *line, int i, int *r)
// {
// 	while (line[i] != '\0')
// 	{
// 				printf("here\n");
// 		if (line[i + 1] != '\0' && ((line[i] == '>' && line[i + 1] == '>') || (line[i] == '<' && line[i + 1] == '<')))
// 		{
// 			if (line[i + 2] == '\0' || (line[i + 2] == '<' || line[i + 2] == '>'))
// 			{
// 				*r = 1;
// 				break;
// 			}
// 			i += 2;
// 			*r = only_spaces__(line, i);
// 			if (*r)
// 				break;
// 		}
// 		else if (line[i] == '>' || line[i] == '<')
// 		{
// 			if (line[i + 1] == '\0')
// 			{
// 				*r = 1;
// 				break;
// 			}
// 			if (line[i + 1] != '\0')
// 			{
// 				*r = only_spaces__(line, i + 1);
// 				if (*r)
// 					break;
// 			}
// 		}
// 		i++;
// 	}
// 	return (i);
// }


// int is_alpha_numirique(char *line)
// {
// 	int i = 0;
	
// 	while (line[i])
// 	{
// 		if ((line[i] >= '0' && line[i] <= '9') || (line[i] >= 'a' && line[i] <= 'z') || (line[i] >= 'A' && line[i] <= 'Z'))
// 			i++;
// 		else
// 			return (1);
// 	}
// 	return (0);
// }

// void first_check(char *cmd, int i, int *t)
// {
// 	char **line = ft_split(cmd, ' ');
// 	if (!line) {
// 		*t = 1;
// 		return;
// 	}
// 	printf("i : %d\n", i);
// 	while (line[i])
// 	{
// 		if (check_line(line[i], i, t) == 1)
// 		{
// 			if (!strcmp(line[i], "<<") && line[i + 1] && is_alpha_numirique(line[i + 1]))
// 			{
// 				if (line[i + 2])
// 					printf("%s\t%s \n", line[i + 1], line[i + 2]);
// 				*t = 1;
// 				break;
// 			}
// 		}
// 		i++;
// 	}
// 	int j = 0;
// 	while (line[j])
// 		free(line[j++]);
// 	free(line);
// }

// int parse_redirection(char *line)
// {
// 	int i;
// 	int r;
// 	int t;
	
// 	i = 0;
// 	r = 0;
// 	t = 0;
// 	while (line[i] != '\0' && line[i] <= 32)
// 		i++;
// 	first_check(line, i, &t);
// 	if (t == 1)
// 		return (1);
// 	return 0;
// }

// ----------------------------3

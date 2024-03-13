/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jadi <sel-jadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 23:51:44 by sdiouane          #+#    #+#             */
/*   Updated: 2024/03/13 14:09:40 by sel-jadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

#define MAX_COMMAND_LENGTH 100

typedef	struct			s_sep
{
	char				*cmd_sep;
	struct s_sep		*next;
}						t_sep;
/*********************************prompt*/
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
char 	*prompt();
/********************************' ; '*/
void	print_list(t_sep *list);
t_sep	*add_cell(t_sep *list, char *cmd_sep, int pos);
t_sep	*create_cell(char *cmd_sep);

/*******************************lst*/
void	ft_lstadd_back(t_sep **lst, t_sep *new);
t_sep	*ft_lstnew(char *data);

/*****************************split*/
void	ft_free_tab(char **tab);
char	**ft_split(char	*s, char c);


#endif
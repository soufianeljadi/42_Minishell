/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 23:51:44 by sdiouane          #+#    #+#             */
/*   Updated: 2024/03/13 00:48:10 by sdiouane         ###   ########.fr       */
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

void	print_list(t_sep *list);
t_sep	*add_cell(t_sep *list, char *cmd_sep, int pos);
t_sep	*create_cell(char *cmd_sep);

void	ft_lstadd_back(t_sep **lst, t_sep *new);
t_sep	*ft_lstnew(char *data);


void	ft_free_tab(char **tab);
char	**ft_split(char	*s, char c);


#endif
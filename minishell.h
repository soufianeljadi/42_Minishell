/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 23:51:44 by sdiouane          #+#    #+#             */
/*   Updated: 2024/03/16 23:28:44 by sdiouane         ###   ########.fr       */
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

typedef	struct			s_cmd
{
	char				*cmd_sep;
	struct s_cmd		*next;
}						s_cmd;

typedef struct s_env
{
	char **env;
} s_env;

// init env :

void init_env(char **env);


// lst :
s_cmd	*ft_lstnew();
void	ft_lstadd_back(s_cmd **lst, s_cmd *new);
void	print_list(s_cmd *list);
s_cmd	*ft_lstnew_data(char *data);


// split :
void	ft_free_tab(char **tab);
char	**ft_split(char	*s, char c);

// token : 
int handle_char();

// parsing :

void nbr_quotes(char *str);
void syntax_error();
int check_next(char *line);
int parse_single_input(char *line, char c);
int parsing(char *lineint );

#endif

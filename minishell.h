/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 23:51:44 by sdiouane          #+#    #+#             */
/*   Updated: 2024/03/22 00:02:07 by sdiouane         ###   ########.fr       */
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
	char				*key;
	char				*value;
	struct s_env		*next;
} s_env;

typedef struct {
    char *value;
} Token;
// init env :

char **init_env(char **env);


// lst :
s_env	*ft_lstnew();
void	ft_lstadd_back(s_env **lst, s_env *new);
void	print_list(s_env *list);
s_env	*ft_lstnew_data(char *value, char*key);


// split :
void	ft_free_tab(char **tab);
char	**ft_split(char	*s, char c);

// strtock :
char *ft_strtok(char *str, const char *delim);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strchr(const char *str, int c);

// token : 
Token* create_token(char *value);
void free_token(Token *token);
void print_tokens(Token **tokens);
void free_tokens(Token **tokens);

// parsing :
Token** parse_command(char *command);
void syntax_error();
int parsing(char *lineint );
	// pipe :
int check_next(char *line,int i);
int parse_single_input(char *line, char c);
	// redirection :
int parse_redirection(char *line);
	// quotes :
void nbr_quotes(char *str);

#endif

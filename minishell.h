/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 23:51:44 by sdiouane          #+#    #+#             */
/*   Updated: 2024/03/29 22:00:27 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
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

typedef struct noeud_cmd
{
	char				*redirection;
	char				*cmd;
	struct noeud_cmd	*next;
} noued_cmd;

typedef struct s_parse
{
	int		i;
	int		count;
	int		dq;
	int		sq;

}			t_parse;


typedef struct s_points
{
	int	i;
	int	j;
	int	start;
	int	end;
}	t_points;

/**********************MAIN***********************************/
	// init_env
char **init_env(char **env);
void	main_loop(char *line,s_env *s_env);
/**********************PARSING***********************************/
	// lst :
s_env	*ft_lstnew();
void	ft_lstadd_back(s_env **lst, s_env *new);
void	print_list(s_env *list);
void	print_export(s_env *list);
s_env	*ft_lstnew_data(char *value, char*key);
	// split :
void	ft_free_tab(char **tab);
char	**ft_split(char	*s, char c);
	// strtock :
char *ft_strtok(char *str, const char *delim);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_substr2(const char *inp, int start, int end);
char	*ft_strchr(const char *str, int c);
	// quotes :
int		ft_quots(char **line);
int		ft_next_quote(char *s, char c);
char		ft_first_quote(char *s);
int 		line_has_quotes(char **line);
	// token : 
Token*	create_token(char *value);
void 	free_token(Token *token);
void 	print_tokens(Token **tokens);
void 	free_tokens(Token **tokens);
	// parsing :
Token** parse_command(char *command);
void 	syntax_error();
int		parsing(char *lineint );
	// utils :
size_t	ft_strlen(char *s);
char	*ft_strjoin(const char *s1, const char *s2);
	// split_args : 
char 	**line_to_args(char *line);
char	**split_args(char *inp);
char	**ft_allocation(char *inp, t_points *p);
int		is_white_space(char c);
int		check_quots(char *inp);
int		get_end_quots(char *inp);
int		check_quots(char *inp);
int		get_end_space(char *inp);
void	ft_free(char **s);
int		ft_count_cmd(char *inp);
	// split_by_pipe :
noued_cmd	*new_noued_cmd(char *commande, char	*redirection);
void		add_back_noued_cmd(noued_cmd **tete, char *commande, char	*redirection);
void 		print_command_list(noued_cmd *head);
noued_cmd	*split_args_by_pipe(char **args);
	//add_sep :
char	*ft_add(char c, char *s, int index);
int		ft_sep_red(char **s, int *i);
void	ft_count_quotes(char *s, int i, t_parse *d);
char	*ft_add_sep(char *s, t_parse d);
	// pipe :
int check_next(char *line,int i);
int parse_single_input(char *line, char c);
	// redirection :
int parse_redirection(char *line);
	// quotes :
void nbr_quotes(char *str);


/**********************BUILTINS***********************************/
void builtins(char ** args, s_env *s_env);
// export :
s_env	*export_fct(char **args, s_env   *env);
//pwd :
void pwd_without_options(char **args);
// unset :
s_env   *unset_fct(char **args, s_env *env);
// cd :
void execute_command(char *command);
// echo :
void echo_fct(char **args);

/**********************signals***********************************/
void    signal_ctrl_c_d(int signal);

#endif

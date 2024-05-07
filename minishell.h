/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 23:51:44 by sdiouane          #+#    #+#             */
/*   Updated: 2024/05/07 16:16:14 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <errno.h>

#define ANSI_RESET_ALL          "\x1b[0m"
#define ANSI_COLOR_RED          "\x1b[31m"
#define ANSI_COLOR_GREEN        "\x1b[32m"
#define ANSI_COLOR_YELLOW       "\x1b[33m"
#define ANSI_BACKGROUND_RED     "\x1b[41m"
#define ANSI_COLOR_MAGENTA      "\x1b[35m"
#define ANSI_COLOR_CYAN         "\x1b[36m"
#define ANSI_COLOR_BLUE         "\x1b[34m"
#define ANSI_COLOR_WHITE        "\x1b[37m"
#define ANSI_COLOR_BLACK        "\x1b[30m"
#define ANSI_BOLD               "\x1b[1m"


#define MAX_COMMAND_LENGTH 100

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1042
# endif


typedef	struct			s_cmd
{
	char				*cmd_sep;
	struct s_cmd		*next;
}						s_cmd;

typedef struct s_env
{
	int					i;
	int					j;
	char				*key;
	char				*value;
	struct s_env		*next;
} s_env;

typedef struct {
    char *value;
} Token;

typedef struct noeud_cmd
{
	int 				in;
	int 				out;
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


typedef struct g_variables
{
	int			shlvl;
	char		**envire;
}					t_var;



typedef struct {
    noued_cmd *lst;      // Liste des commandes
    char **args;         // Arguments de la commande principale
    char **env;          // Environnement
    s_env *export_i;     // Variables d'environnement exportées
    char **null_env;     // Environnement vide
} ExecutionData;

/**********************MAIN***********************************/
	// init_env
void	main_loop(char *line, char **env, s_env *export_i, char **null_env);
/**********************PARSING***********************************/
	// lst :
s_env	*ft_lstnew();
void	ft_lstadd_back(s_env **lst, s_env *new);
void	print_list(s_env *list);
void	print_export(s_env *list);
void	print_env_i(s_env *lst);
s_env	*ft_lstnew_data(char *value, char*key);
void	free_noued_cmd(noued_cmd *node);
void	free_s_env(s_env *head);
	// split :
void	ft_free_tab(char **tab);
char	**ft_split(char	*s, char c);
	// strdup :
char	*ft_strdup(char *s1);
	// strtock :
char	*ft_strtok(char *str, const char *delim);
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
void builtins(char **args, s_env *export_i, char **env);
// export :
s_env *export_fct(char **args, s_env *env, s_env *split_export_i, char **eenv);
int existe_deja(char *key, s_env *env);
char *remove_quotes(char *input);
int	verif_export(char *str);
void is_null(char **args, s_env *env);
void concatenation(char **args, s_env *env, char *key);
void is_equal(char **args, s_env *export_i, char *key);
s_env *not_null(char **args, s_env *env);
void fct_equal(char **args, s_env *env, char *key, int f);
void ftc_concatination(char **args, s_env *env, char *key);

//pwd :
char *pwd_without_options(char **args, char *pwd);
// unset :
s_env   *unset_fct(char **args, s_env *env);
void	remove_key(s_env **begin_list, void *data_ref, int (*cmp)());
int cmp(void *data1, void *data2);
// cd :
s_env *execute_cd(char **args, s_env *lst);
// echo :
void echo_fct(char **args, s_env *s_env);
// $var :
int   check_variables(char **args, s_env *lst);

/**********************signals***********************************/
void    signal_ctrl_c_d(int signal);

/**********************get_next_line*****************************/
char	*get_next_line(int fd);
char	*ft_join(char *dest, char *s1, char *s2);
int		find(char *s, char c);
char	*ft_strjoin_gnl(char *start, char *buff);
int		ft_strlen_gnl(char *s);
char	*ft_strdup_gnl(char *s1);

/***********************execution********************************/
// void ft_execution(noued_cmd *lst, char **args, char **env, s_env *export_i, char **null_env);
void ft_execution(ExecutionData *data);
void execute(char *s, char **env);
void pipeline(char ***cmd);
void supprimerGuillemets(char *chaine);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*get_env(char *s, char **env);
char	*get_path(char *cmd, char **env);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
	// redirections :
char	*file_nc(char *s);
void execute_with_redirection(char *cmd, char **env, char *redirection);
int		only_spaces(char *str);
s_env	*split_env(char **env);
s_env	*split_export_i(s_env *lst);
s_env	*add_env_entry(s_env *head, char *key, char *value);


char	*ft_itoa(unsigned int n);
int	ft_atoi(const char *str);

// expanding :
void ft_expanding(char **args, s_env *export_i);
char *get_env_key(char *s, int j);
char *get_env_value(char *key, s_env *export_i);
char *ft_str_replace(char *s, char *key, char *value);

int is_single(char *str);
t_var	g_flags;
#endif

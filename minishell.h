/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jadi <sel-jadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 23:51:44 by sdiouane          #+#    #+#             */
/*   Updated: 2024/07/19 23:07:33 by sel-jadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <termios.h>
# include <unistd.h>
# include <fcntl.h> 
# include <stdbool.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>

# define ANSI_RESET_ALL "\x1b[0m"
# define ANSI_COLOR_RED "\x1b[31m"
# define ANSI_COLOR_YELLOW "\x1b[33m"
# define ANSI_BACKGROUND_RED "\x1b[41m"
# define ANSI_COLOR_GREEN "\x1b[32m"
# define ANSI_COLOR_MAGENTA "\x1b[35m"
# define ANSI_COLOR_CYAN "\x1b[36m"
# define ANSI_COLOR_BLUE "\x1b[34m"
# define ANSI_COLOR_WHITE "\x1b[37m"
# define ANSI_COLOR_BLACK "\x1b[30m"
# define ANSI_BOLD "\x1b[1m"

# define MAX_TOKEN_LENGTH 100
# define MAX_COMMAND_LENGTH 100

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1042
# endif

# define MAX_OUTPUT_SIZE 1024

extern int	g_signal;

typedef struct s_env
{
	int				i;
	int				j;
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_parse
{
	int	i;
	int	count;
	int	dq;
	int	sq;
}	t_parse;

typedef struct s_points
{
	int	i;
	int	j;
	int	start;
	int	end;
}	t_points;

typedef struct noeud_cmd
{
	int					in;
	int					out;
	char				*redirection;
	char				*cmd;
	struct noeud_cmd	*next;
}	t_noued_cmd;

typedef struct exec_data
{
	t_noued_cmd	*lst;
	char		**args;
	t_env		*export_i;
	char		**env;
	int			fd_in;
	int			fd_out;
}	t_data;
typedef struct t_p
{
	int	i;
	int	j;
	int	q_open;
	int	cur_quote;
}	t_p;

char		*ft_strncpy(char *dest, const char *src, size_t n);
char		*ft_strcat(char *dest, const char *src);
void		main_loop(char *line, t_env *export_i);
t_env		*ft_lstnew(void);
void		ft_lstadd_back(t_env **lst, t_env *new);
void		print_list(t_env *list);
void		print_export(t_env *list);
t_env		*ft_lstnew_data(char *value, char *key);
void		free_noued_cmd(t_noued_cmd *node);
char		*get_dest(char *args, t_env	*lst);
void		free_s_env(t_env *head);
char		*ft_getdes(t_env	*lst, char	*des);
void		protect_value(char *value);
void		ft_free_tab(char **tab);
char		**ft_split(char *s, char c);
char		**split_space_tab(char *s, char c);
char		*ft_strdup(char *s1);
char		*ft_strtok(char *str, const char *delim);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_substr2(const char *inp, int start, int end);
char		*ft_strchr(const char *str, int c);
int			ft_quots(char **line);
int			ft_next_quote(char *s, char c);
char		ft_first_quote(char *s);
int			line_has_quotes(char **line);
void		syntax_error(void);
int			parsing(char *line, t_data *data);
size_t		ft_strlen(const char *s);
char		**line_to_args(char *line);
char		**split_args(char *inp);
int			is_white_space(char c);
int			check_quots(char *inp);
int			get_end_quots(char *inp);
int			check_quots(char *inp);
int			get_end_space(char *inp);
void		ft_free(char **s);
int			ft_count_cmd(char *inp);
char		*get_env_value(char *key, t_env *export_i);
char		*get_env_key(char *s, int j);
char		*exp_fct(char *commande, t_env *export_i, int *f);
char		*prc_variable(char *exp_commande, t_p *p, t_env *export_i);
void		handle_quotes(char *exp_commande, t_p *p);
int			is_closed(char *exp_commande, int i);
void		check_memory_allocation(void *ptr);
t_env		*export_fct(char **args, t_env *env, char **eenv);
int			existe_deja(char *key, t_env *env);
int			verif_export(char *str);
void		is_null(char **args, t_env *env);
void		is_equal(char **args, t_env *export_i, char *key);
t_env		*not_null(char **args, t_env *env);
void		fct_equal(char **args, t_env *env, char *key);
void		ftc_concatination(char **args, t_env *env, char *key);
void		remove_q(char *chaine);
void		ft_execut_error(char *cmd);
int			count_quotes(char *str, char c);
int			exit_stat(int stat);
void		check_here_doc(t_data *data);
void		handle_heredocs(char **delem, t_data *data);
int			just_quotes(char *str);
int			check_bultin(char *cmd);
int			is_blank(char *str);
void		supprimer_protection(char *chaine);
void		free_noued_cmd(t_noued_cmd *head);
void		add_back_noued_cmd(t_noued_cmd **tete, char *c, char *r);
void		print_export(t_env *list);
char		*ft_strjoin(char const *s1, char const *s2);
int			check_quots(char *inp);
int			is_white_space(char c);
int			ft_count_cmd(char *inp);
int			file_exists(const char *filename);
char		*generate_name(char *base_name);
int			check_bultin(char *cmd);
int			ft_strcmp(const char *s1, const char *s2);
int			count_quotes(char *str, char c);
char		*extract_value(char *arg, int start, int end);
void		ft_execut_error(char *cmd);
void		remove_outermost_quotes(char *str);
void		check_error(char **cmd, char **env, char *chemin);
void		execute(char *s, char **env, t_data *data);
char		*ft_add_sep(char *s);
int			check_next(char *line, int i);
int			parse_single_input(char *line, char c);
int			parse_redirection(char *line);
int			builtins(t_data *data);
t_env		*export_fct(char **args, t_env *env, char **eenv);
int			existe_deja(char *key, t_env *env);
void		ft_rm_quotes(char *str);
int			verif_export(char *str);
void		is_null(char **args, t_env *env);
void		concatenation(char **args, t_env *env, char *key);
void		is_equal(char **args, t_env *export_i, char *key);
t_env		*not_null(char **args, t_env *env);
void		fct_equal(char **args, t_env *env, char *key);
void		ftc_concatination(char **args, t_env *env, char *key);
char		*pwd_without_options(char **args, char *pwd);
t_env		*unset_fct(char **args, t_env *env);
t_env		*execute_cd(char **args, t_env *lst, char *curr);
void		echo_fct(char **args);
void		exit_fct(char **cmds);
void		ft_execution(t_data *data);
void		execute(char *s, char **env, t_data *data);
void		supprimerguillemets(char *chaine);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*get_env(char *s, char **env);
char		*get_path(char *cmd, char **env);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
char		*file_nc(char *s);
void		execute_with_redirection(t_data *data);
int			execute_with_redirection_builtins(t_data *data);
int			only_spaces(char *str);
t_env		*split_env(char **env, t_env *lst);
t_env		*split_export_i(t_env *lst);
t_env		*add_env_entry(t_env *head, char *key, char *value);
char		*ft_itoa(unsigned int n);
int			ft_atoi(char *str);
char		*get_env_key(char *s, int j);
char		*get_env_value(char *key, t_env *export_i);
char		*ft_str_replace(char *s, char *key, char *value);
void		handle_sigint_heredoc(int sig);
void		signals_init(void);
char		*print_directory(char *pwd);
char		*get_directory(char *pwd);
char		*add_write_str(char *str1, char *str2, char *str3);
void		add2write(char *dest, char *str, int *j);
void		ft_putstr_fd(char *s, int fd);
int			ft_lstsize(void *lst);
void		redirection_in(char *oper, char *redirection, int *fd);
void		redirection_double_out(char *redirection, int *fd);
void		redirection_out(char *redirection, int *fd);
int			redirection_in_builtins(char *oper, char *redirection, int *fd);
int			redirection_double_out_builtins(char *redirection, int *fd);
int			redirection_out_builtins(char *redirection, int *fd);
void		del_qotes1(char *chaine);
void		del_qotes(char *chaine);
void		del_dbl_quotes(char *chaine);
void		del_sngl_quotes(char *chaine);
void		supprimerguillemets(char *chaine);
void		add_last_cmd(t_env **lst, char **args);
char		**struct_to_char(t_env **lst);
char		**check_quotes_before_execution(char *s);
t_noued_cmd	*new_noued_cmd(char *commande, char *redirection);
t_noued_cmd	*split_args_by_pipe(char **args);
t_noued_cmd	*ft_expanding(t_data **data, t_env *export_i);
void		ft_rm_quotes(char *str);
void		sng_q(char *chaine);
void		dbl_q(char *chaine);
char		*variable_with_value(char *full_key, char *key, char *value,
				char *exp_commande);
char		**split_with_quotes(const char *text);
char		*get_value(char **env, char *key, int i, int j);
char		*ft_strstr(char *str, char *to_find);
t_env		*begin_export(t_env *env, char **args, char *key);
void		increment_j(t_env *env);
char		*my_strjoin(char const *s1, char const *s2);
int			handle_delimeter(char **delim);
void		cleanup_heredoc(int fd, char	**delem, char	*file_name);
int			file_exists(const char *filename);
void		execute_builtin(t_data *data, char *chemin);
void		handle_execve_error(char **cmd, char *chemin);
void		handle_child_process(t_data *data);
void		handle_path_error(char **cmd);
void		execute(char *s, char **env, t_data *data);
char		**splt_args(char *line);
void		process_command(char **cmd);
int			should_remove_quotes(char *s);
char		**handle_backslash_case(char *s);
char		**check_quotes_before_execution(char *s);
void		update_env_value(t_env *env, char *key, char *value);
void		fct_equal(char **args, t_env *env, char *key);
void		concat_value(t_env *env, char *key, char *value);
void		handle_invalid_key(char *key);
void		handle_invalid_plus(char *key, char *arg, int j);
int			is_invalid_plus(char *arg, int j);
char		*extract_key(char *arg, int *j);
int			contains_space_or_tab(char *arg);
void		init_t_p(t_p	*p);
char		*replace_exit_status(char	*exp_commande);
void		print_error(char	*str, char	*type);
char		*get_env_var(t_env	*lst, char	*key);
int			set_env_var(t_env	**lst, char	*key, char	*value);
void		put_ambiguous(char *redirection);
void		put_errno(char *redirection);
void		put_ambiguous_builtins(char *redirection);
void		put_errno_builtins(char *redirection);
int			check_bultin(char *cmd);
char		*format_value_if_needed(char *key, t_env *export_i);
void		*ft_malloc(size_t size);
void		handle_path_error(char **cmd);
char		*ft_check(char *str);
#endif

// // #include <stdio.h>
// // #include <libc.h>
// // int is_single(char *str)
// // {
// // 	int s;
// // 	int d;
// // 	int i;

// // 	i = 0;
// // 	s = d = 0;
// // 	int j = 0;
// // 	while (str[i])
// // 	{
// // 		if (str[i] == '\'' && d == 0)
// // 			s = s + 1;
// // 		else if (str[i] == '"' && s == 0)
// // 			d = d + 1;
// // 		if (d == 2)
// // 			d = 0;
// // 		if (s == 2)
// // 			s = 0;
// // 		if (str[i] == '$')
// // 			break;
// // 		i++;
// // 	}
// // 	if (s == 1)
// // 		return (1);
// // 	else
// // 		return (0);

// // 	return (0);
// // }
// // void f()
// // {
// // 	system("leaks a.out");
// // }
// // int main()
// // {
// // 	atexit(f);
// // 	// char *str = "  \"'\"'$PWD'\"'\"   ";
// // 	char *str = "  'PWD'   ";
// // 	printf("%d\n", is_single(str));
	
// // 	return (0);
// // }

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// #define MAX_TOKEN_LENGTH 100

// char** split_with_quotes(const char* text) {
//     char** tokens = malloc(sizeof(char*) * MAX_TOKEN_LENGTH);
//     int token_count = 0;
//     int in_quote = 0;
//     const char* start = text;
//     const char* end = text;

//     while (*end != '\0') {
//         if (*end == '"' || *end == '\'') {
//             in_quote = !in_quote;
//             end++;
//         } else if ((*end == ' ' || *end == '\t') && !in_quote) {
//             int length = end - start;
//             if (length > 0) {
//                 tokens[token_count] = malloc(sizeof(char) * (length + 1));
//                 strncpy(tokens[token_count], start, length);
//                 tokens[token_count][length] = '\0';
//                 token_count++;
//             }
//             while (*end == ' ' || *end == '\t') {
//                 end++;
//             }
//             start = end;
//         } else {
//             end++;
//         }
//     }

//     int length = end - start;
//     if (length > 0) {
//         tokens[token_count] = malloc(sizeof(char) * (length + 1));
//         strncpy(tokens[token_count], start, length);
//         tokens[token_count][length] = '\0';
//         token_count++;
//     }

//     tokens[token_count] = NULL;
//     return tokens;
// }

// void free_tokens(char** tokens) {
//     for (int i = 0; tokens[i] != NULL; i++) {
//         free(tokens[i]);
//     }
//     free(tokens);
// }

// int main() {
//     const char* text = "export x=\"ls -la\" \"    kk    ll\"  'll k'";
//     char** tokens = split_with_quotes(text);
    
//     printf("Tokens:\n");
//     for (int i = 0; tokens[i] != NULL; i++) {
//         printf("%s\n", tokens[i]);
//     }
    
//     free_tokens(tokens);

//     return 0;
// }

// int	is_builtins(char **args, s_env **export_i, char **env, int *flag)
// {
// 	char *pwd;
// 	supprimerGuillemets(args[0]);
// 	if (!strcmp(args[0], "exit"))
// 	{
// 		printf("exit\n");
// 		exit(EXIT_SUCCESS);
// 	}
// 	else if (!strcmp(args[0], "echo"))
// 		echo_fct(args, *export_i);
// 	else if (!strcmp(args[0], "pwd"))
// 	{
// 		pwd = getcwd(NULL, 0);
// 		pwd_without_options(args, pwd);
// 		free(pwd);
// 	}
// 	else if (!strcmp(args[0], "export"))
// 		*export_i = export_fct(args, *export_i, env);
// 	else if (!strcmp(args[0], "unset"))
// 	{
// 		*export_i = unset_fct(args, *export_i);
// 	}
// 	else if (!strcmp(args[0], "cd"))
// 		*export_i = execute_cd(args, *export_i);        
// 	else if (!strcmp(args[0], "env") && !args[1])
// 	{   
// 		if (*(env) || !*(env))	
// 			print_list(*export_i);
// 	}
// 	else
// 		*flag = 1;
// 	return (*flag);
// }

// int builtins(ExecutionData *data)
// {
// 	char **args = NULL;
// 	int flag = 0;

// 	if (data->lst->cmd[0] != '\0'/* && data->lst->cmd[0]*/)
// 	{
// 		args = split_with_quotes(data->lst->cmd);
// 		if (!args)
// 			return (0);
// 		flag = is_builtins(args, &data->export_i, data->env ,&flag);
// 	}
// 	else
// 		return (1);
// 	return(flag);
// }

// char *file_nc(char *s)
// {
// 	int i;
// 	int x;
// 	char *f;
	
// 	i = 0;
// 	x = 0;
// 	if (!s)
// 		return (NULL);
// 	f = (char *)malloc(sizeof(char) * (strlen(s) + 1));
// 	if (f == NULL)
// 		exit(EXIT_FAILURE);
// 	while (s[i] != '\0')
// 	{
// 		if (s[i] == '"' || s[i] == '\'')
// 		{
// 			char quote = s[i];
// 			i++;
// 			while (s[i] != '\0' && s[i] != quote)
// 			{
// 				f[x] = s[i];
// 				i++;
// 				x++;
// 			}
// 			if (s[i] == '\0')
// 				exit(EXIT_FAILURE);
// 		}
// 		else
// 		{
// 			f[x] = s[i];
// 			x++;
// 		}
// 		i++;
// 	}
// 	f[x] = '\0';
// 	return f;
// }


// void redirection_double_out(char *redirection, int *fd)
// {
// 	if (redirection)
// 	{
// 		if (redirection[0] == '$')
// 		{
// 			ft_putstr_fd("minishell: ", 2);
// 			ft_putstr_fd(redirection, 2);
// 			ft_putstr_fd(": ambiguous redirect\n", 2);
// 			exit(EXIT_FAILURE);
// 		}
//         *fd = open(file_nc(redirection), O_WRONLY | O_CREAT | O_APPEND, 0666);
// 		if (*fd < 0)
// 		{
// 			ft_putstr_fd("minishell: ", 2);
// 			ft_putstr_fd(redirection, 2);
// 			ft_putstr_fd(": No such file or directory\n", 2);
// 			exit(EXIT_FAILURE);
// 		}
// 		redirection = NULL;
//         dup2(*fd, STDOUT_FILENO);
//         close(*fd);
// 	}
// }

// void redirection_in(char *redirection, int *fd)
// {
// 	if (redirection != NULL)
// 	{
// 		if (redirection[0] == '$')
// 		{
// 			ft_putstr_fd("minishell: ", 2);
// 			ft_putstr_fd(redirection, 2);
// 			ft_putstr_fd(": ambiguous redirect\n", 2);
// 			exit(EXIT_FAILURE);
// 		}
// 		*fd = open(file_nc(redirection), O_RDONLY);
// 		if (*fd < 0)
// 		{
// 			ft_putstr_fd("minishell: ", 2);
// 			ft_putstr_fd(redirection, 2);
// 			ft_putstr_fd(": No such file or directory\n", 2);
// 			exit(EXIT_FAILURE);
// 		}
// 		redirection = NULL;
// 		dup2(*fd, STDIN_FILENO);
// 		close(*fd);
// 	}
// }

// void redirection_out(char *redirection, int *fd)
// {
// 	if (redirection)
// 	{
// 		if (redirection[0] == '$')
// 		{
// 			ft_putstr_fd("minishell: ", 2);
// 			ft_putstr_fd(redirection, 2);
// 			ft_putstr_fd(": ambiguous redirect\n", 2);
// 			exit(EXIT_FAILURE);
// 		}
//         *fd = open(file_nc(redirection), O_WRONLY | O_CREAT | O_TRUNC, 0666);
//         if (*fd < 0)
// 		{
//             printf("minishell: %s: No such file or directory\n", redirection);
//             exit(EXIT_FAILURE);
//         }
// 		redirection = NULL;
//         dup2(*fd, STDOUT_FILENO);
//         close(*fd);
// 	}
// }

// void execute_with_redirection(ExecutionData *data)
// {
//     int fd_in;
//     int fd_out;
// 	int i;
// 	char **red;

// 	(1) && (fd_in = 0, fd_out = 1, i = 0,
// 	red = line_to_args(data->lst->redirection));
// 	if (!red)
// 		return ;
// 	while (red[i])
// 	{
// 		if (!strcmp(red[i], "<") && red[i + 1])
// 			redirection_in(red[i + 1], &fd_in);
// 		if (!strcmp(red[i], ">>") && red[i + 1])
// 			redirection_double_out(red[i + 1], &fd_out);
// 		if (!strcmp(red[i], ">") && red[i + 1])
// 			redirection_out(red[i + 1], &fd_out);
// 		if (!strcmp(red[i], "<<") && red[i + 1])
// 			heredoc(red[i + 1], data);
// 		i++;
// 	}
// 	if (data->lst->cmd != NULL && strspn(data->lst->cmd, " ") != strlen(data->lst->cmd))
// 		execute(data->lst->cmd, data->env);
// }

// void execute(char *s, char **env)
// {
// 	char	*chemin;
// 	char	**cmd;

// 	(1) && (cmd = NULL, chemin = NULL);
// 	if (*env)
// 	{
// 		cmd = check_quotes_before_execution(s);
// 		if (cmd[0][0] == '\'')
// 			del_sngl_quotes(cmd[0]);
// 		else if (cmd[0][0] == '\"')
// 			del_dbl_quotes(cmd[0]);
// 		chemin = get_path(cmd[0], env);
// 		if (execve(chemin, cmd, env) == -1 /*&& strcmp(cmd[0], "\0")*/)
// 		{
// 			if (strcmp(cmd[0], "\0"))
// 				ft_execut_error(cmd[0]);
// 			(ft_free_tab(cmd), exit(EXIT_FAILURE));
// 		}
// 	}
// }

// static void handle_child_process(ExecutionData *data)
// {
// 	if (data->lst->redirection != NULL)
// 	{
// 		execute_with_redirection(data);
// 	}
// 	else
// 	{
// 		if (data->lst->cmd != NULL)
// 		{
// 			if (builtins(data) == 1)
// 				execute(data->lst->cmd, data->env);
// 			exit(EXIT_SUCCESS);
// 		}
// 	}
// }

// static void execute_command(ExecutionData *data)
// {
// 	int pipefd[2];
//     pid_t pid;

// 	if (pipe(pipefd) == -1 || (pid = fork()) == -1)
// 		exit(EXIT_FAILURE);
// 	else if (pid == 0)
// 	{
// 		signal(SIGINT, SIG_DFL);
// 		if (data->lst->next != NULL)
//         	dup2(pipefd[1], STDOUT_FILENO);
// 		close(pipefd[1]);
// 		close(pipefd[0]);
// 		handle_child_process(data);
// 	}
// 	else
// 	{
// 		signal(SIGINT, SIG_IGN);
// 		dup2(pipefd[0], STDIN_FILENO);
// 		close(pipefd[1]);
// 		close(pipefd[0]);
// 	}
// }


// void	ft_execution(ExecutionData *data)
// {
//     add_last_cmd(&data->export_i, data->args);
// 	if (!ft_strncmp(data->args[0], "<<", 2) && !data->args[1])
// 		(syntax_error(), exit(EXIT_FAILURE));
// 	if (data->lst->next == NULL)
// 	{
// 		if (builtins(data) == 1)
// 			execute_command(data);
// 	}
// 	else
// 	{
// 		signal(SIGINT, SIG_IGN);
// 		while (data->lst)
// 		{
// 			g_flags.envire = ft_merge_envr(data->export_i);
// 			if (builtins(data) == 1)
// 				execute_command(data);
// 			data->lst = data->lst->next;         
// 		}
// 	}
//     while (0 < wait(NULL))
// 		;
// }


// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// char* concat_strings(char **strings, int count) {
//     // Calculer la longueur totale nécessaire
//     int total_length = 0;
//     for (int i = 0; i < count; i++) {
//         total_length += strlen(strings[i]);
//     }
//     // Ajouter de l'espace pour les séparateurs et le caractère nul de fin
//     total_length += count - 1;  // Pour les espaces ou autres séparateurs
//     total_length += 1;          // Pour le caractère nul de fin

//     // Allouer de la mémoire pour la chaîne résultante
//     char *result = (char *)malloc(total_length * sizeof(char));
//     if (result == NULL) {
//         fprintf(stderr, "Erreur d'allocation de mémoire\n");
//         exit(1);
//     }

//     // Initialiser la chaîne résultante avec une chaîne vide
//     result[0] = '\0';

//     // Concaténer les chaînes
//     for (int i = 0; i < count; i++) {
//         strcat(result, strings[i]);
//         if (i < count - 1) {
//             strcat(result, " ");  // Ajouter un espace entre les mots, par exemple
//         }
//     }

//     return result;
// }

// int main() {
//     char *strings[] = {"Bonjour", "le", "monde"};
//     int count = sizeof(strings) / sizeof(strings[0]);

//     char *result = concat_strings(strings, count);
//     printf("Résultat : %s\n", result);

//     // Libérer la mémoire allouée
//     free(result);

//     return 0;
// }

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// // Mocking external functions
// char *ft_strchr(const char *s, int c) {
//     return strchr(s, c);
// }

// char *ft_substr(char const *s, unsigned int start, size_t len) {
//     char *substr = (char *)malloc(len + 1);
//     if (substr) {
//         strncpy(substr, s + start, len);
//         substr[len] = '\0';
//     }
//     return substr;
// }

// char *ft_strjoin(char const *s1, char const *s2) {
//     size_t len1 = strlen(s1);
//     size_t len2 = strlen(s2);
//     char *joined = (char *)malloc(len1 + len2 + 1);
//     if (joined) {
//         strcpy(joined, s1);
//         strcat(joined, s2);
//     }
//     return joined;
// }

// char *ft_str_replace(char *orig, char *rep, char *with) {
//     char *result, *ins, *tmp;
//     int len_rep, len_with, len_front, count;

//     if (!orig || !rep)
//         return NULL;
//     len_rep = strlen(rep);
//     if (len_rep == 0)
//         return NULL;
//     if (!with)
//         with = "";
//     len_with = strlen(with);

//     ins = orig;
//     for (count = 0; (tmp = strstr(ins, rep)); ++count) {
//         ins = tmp + len_rep;
//     }

//     tmp = result = malloc(strlen(orig) + (len_with - len_rep) * count + 1);

//     if (!result)
//         return NULL;

//     while (count--) {
//         ins = strstr(orig, rep);
//         len_front = ins - orig;
//         tmp = strncpy(tmp, orig, len_front) + len_front;
//         tmp = strcpy(tmp, with) + len_with;
//         orig += len_front + len_rep;
//     }
//     strcpy(tmp, orig);
//     return result;
// }

// char get_q(char *str) {
//     while (*str) {
//         if (ft_strchr("'\"", *str)) {
//             return *str;
//         }
//         str++;
//     }
//     return 0;
// }

// int is_within_quotes(char *str, int pos) {
//     int i = 0;
//     char quote = 0;

//     while (i < pos) {
//         if (str[i] == '\'' || str[i] == '"') {
//             if (quote == 0) {
//                 quote = str[i];
//             } else if (quote == str[i]) {
//                 quote = 0;
//             }
//         }
//         i++;
//     }
//     return (quote == '\'');
// }

// char *get_env_key(char *str, int pos) {
//     // Mock implementation for example
//     return "MOCK_KEY";
// }

// char *get_env_value(char *key, void *export_i) {
//     // Mock implementation for example
//     return "MOCK_VALUE";
// }

// void supprimerDoll(char *str) {
//     // Mock implementation for example
// }

// char *ft_expanding(char *commande, void *export_i) {
//     char *exp_commande = strdup(commande);
//     char *exp_cmd = NULL;
//     char *key = NULL;
//     char *value = NULL;
//     int i = 0;

//     if (!exp_commande)
//         exit(EXIT_FAILURE);

//     while (exp_commande && exp_commande[i] != '\0') {
//         if (exp_commande[i] == '\'' || exp_commande[i] == '"') {
//             char quote = exp_commande[i];
//             i++;
//             while (exp_commande[i] && exp_commande[i] != quote) {
//                 i++;
//             }
//             i++;
//         } else if (exp_commande[i] == '$' && !is_within_quotes(exp_commande, i)) {
//             key = get_env_key(exp_commande, i);
//             if (!key)
//                 exit(EXIT_FAILURE);
//             value = get_env_value(key, export_i);
//             if (!value || !strcmp(value, "") || !strcmp(value, " ")) {
//                 exp_commande = ft_str_replace(exp_commande, key, strdup(""));
//                 free(key);
//                 free(value);
//             } else {
//                 key = ft_strjoin("$", key);
//                 exp_cmd = ft_str_replace(exp_commande, key, value);
//                 free(exp_commande);
//                 exp_commande = exp_cmd;
//                 free(key);
//                 free(value);
//             }
//         }
//         i++;
//     }

//     if (strstr(exp_commande, "$") && is_within_quotes(exp_commande, 0) == 0)
//         supprimerDoll(exp_commande);
//     return exp_commande;
// }



// char *sera_expander_quotes(char *str)
// {
// 	int i = 0;
// 	int j = 0;
// 	char *new_str = (char *)malloc((strlen(str) + 1) * sizeof(char));
// 	if (!new_str)
// 		exit(EXIT_FAILURE);
// 	while (str[i])
// 	{
// 		if (str[i] == '"')
// 		{
// 			i++;
// 			while (str[i] && str[i] != '"')
// 				new_str[j++] = str[i++];
// 		}
// 		else if (str[i] == '\'')
// 		{
// 			i++;
// 			while (str[i] && str[i] != '\'')
// 				new_str[j++] = str[i++];
// 		}
// 		else
// 			i++;
// 			// new_str[j++] = str[i++];
// 	}
// 	new_str[j] = '\0';
// 	return (new_str);		
// }


// int is_closed(char *str, int n)
// {
// 	int i = 0;

// 	while (str[i] && i < n)
// 	{
// 		if (str[i] == '"')
// 		{
// 			i++;
// 			while (str[i] && str[i] != '"')
// 				i++;
// 			if (str[i] == '\0' || i >= n)
// 				return (0);
// 		}
// 		i++;
// 	}
// 	return (1);
// }

// int main(int arc, char **arv)
// {
// 	printf("%d\n", is_closed(arv[1], atoi(arv[2])));
// }


// char *supp_quotes(char *str)
// {
// 	char *new_str;
// 	int i = 0;
// 	int j = 0;

// 	new_str = (char *)malloc(sizeof(char) * (strlen(str) + 1));
// 	if (!new_str)
// 		return NULL;
// 	while (str[i])
// 	{
// 		if (str[i] != '\"')
// 		{
// 			while (str[i] && str[i] != '\"')
// 			{
// 				new_str[j] = str[i];
// 				i++;
// 				j++;
// 			}
// 		}
// 		else if (str[i] == '\"')
// 		{
// 			i++;
// 			while (str[i] && str[i] != '\"')
// 			{
// 				new_str[j] = str[i];
// 				i++;
// 				j++;
// 			}
// 		}
// 		i++;
// 	}
// 	new_str[j] = '\0';
// 	return new_str;
// }

// char *supp_quotes(char *str) {
//     char *new_str;
//     int i = 0;
//     int j = 0;
//     int quote_open = 0; // 0: no quote, 1: single quote, 2: double quote

//     new_str = (char *)malloc(sizeof(char) * (strlen(str) + 1));
//     if (!new_str)
//         return NULL;
    
//     while (str[i]) {
//         if (str[i] == '\'' && quote_open != 2) {
//             quote_open = (quote_open == 1) ? 0 : 1;
//             i++;
//         } else if (str[i] == '\"' && quote_open != 1) {
//             quote_open = (quote_open == 2) ? 0 : 2;
//             i++;
//         } else {
//             new_str[j++] = str[i++];
//         }
//     }
//     new_str[j] = '\0';
//     return new_str;
// }


// int main(int arc, char **arv)
// {
// 	printf("%s\n", supp_quotes("\"'''''''''''''''''ls\""));
// 	printf("\n");
// 	return (0);
// }

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// char *replace_substring(const char *original, const char *key, const char *value) {
//     const char *pos = strstr(original, key);
//     if (!pos) {
//         return strdup(original);
//     }

//     size_t original_len = strlen(original);
//     size_t key_len = strlen(key);
//     size_t value_len = strlen(value);

//     size_t new_len = original_len - key_len + value_len;
//     char *new_str = (char *)malloc(new_len + 1);
//     if (!new_str) {
//         return NULL;
//     }

//     size_t prefix_len = pos - original;
//     strncpy(new_str, original, prefix_len);
//     new_str[prefix_len] = '\0';

//     strcat(new_str, value);
//     strcat(new_str, pos + key_len);

//     return new_str;
// }

// int main() {
//     char *original = "Hello $USER, welcome!";
//     char *key = "$USER";
//     char *value = "";
//     char *result = replace_substring(original, key, value);

//     if (result) {
//         printf("Original: %s\n", original);
//         printf("Result: %s\n", result);
//         free(result);
//     } else {
//         printf("Memory allocation failed\n");
//     }

//     return 0;
// }

// #include "minishell.h"

// char *concat_str(char *s, char **args)
// {
// 	int i = 1;
// 	while (args[i])
// 	{
// 		s = ft_strjoin(s, args[i]);
// 		i++;
// 	}
// 	return (s);
// }

// void new(char *str)
// {
// 	char **args = ft_split(str, ' ');
// 	char *s = NULL;
	
// 	if (strcmp(args[0], "export") == 0)
// 	{
// 		s = concat_str(s, args);
// 	}
// 	printf("s = %s\n", s);
// }
// int main()
// {
// 	new("export x p xx");
// 	return (0);
// }

// static int var;
// int exit_s(int stat)
// {

//     if (stat != -1)
//         var = stat;
//     return (var);
// }


// int main()
// {
//    exit_s(255);
//    exit_s(-1);
// printf("%d", var);
// }




void	handle_heredocs(char **delem, ExecutionData *data)
{
	int		fd;
	int		flag;
	char	*buf;

	(void)data;
	flag = 0;
	fd = open("tmp,txt", O_CREAT | O_WRONLY | O_RDWR, 0777);
	buf = readline("heredocs >> ");
	// if (strstr(*delem, "\"") || strstr(*delem, "'"))
	// {
	// 	flag = 1;
	// 	supprimerGuillemets(*delem);
	// }
	while (1)
	{
		if (strcmp(buf, *delem) == 0)
			break ;
		// if (flag == 1)
		// {
		// 	ft_expanding(&data, data->export_i);
		// }
		write(fd, buf, ft_strlen(buf));
		write(fd, "\n", 1);
		buf = readline("heredocs >> ");
	}
	free(buf);
	if (close(fd) == -1)
		exit(1);
	*delem = ft_strdup("tmp,txt");
}

void check_here_doc(ExecutionData *data)
{
	int i;
	
	i = 0;
	if (!data->args)
		return ;
	while (data->args[i])
	{
		if (!strcmp(data->args[i], "<<") && data->args[i + 1])
			handle_heredocs(&data->args[i + 1], data);
		i++;
	}
}

void loop_fct(ExecutionData *data, char *line)
{
	char	*pwd;
	
	pwd = NULL;
	while (42)
	{
		// (pwd = print_directory(pwd), line = readline(pwd));
		line = readline(ANSI_COLOR_GREEN "minishell > " ANSI_RESET_ALL);
		if (!line)
			(printf("exit\n"),exit(0));
		if(line != NULL && only_spaces(line) == 0)
		{
			add_history(line);
			if(parsing(line) == 1)
			{
				syntax_error();
				exit_stat(258);
			}
			else
			{
				data->args = line_to_args(line);
				check_here_doc(data);
				data->lst = split_args_by_pipe(data->args);
				data->lst = ft_expanding(&data, data->export_i);
				// print_command_list(data->lst);
				(dup2(0, 3),dup2(1, 4), ft_execution(data));
				(dup2(3, 0), dup2(4, 1), close(3), close(4));
				(free (data->args)/*, free_noued_cmd(data->lst)*/);
			}
		}
		// else
			// exit_stat(66048);    
	}	
}
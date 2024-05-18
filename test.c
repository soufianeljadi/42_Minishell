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


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* concat_strings(char **strings, int count) {
    // Calculer la longueur totale nécessaire
    int total_length = 0;
    for (int i = 0; i < count; i++) {
        total_length += strlen(strings[i]);
    }
    // Ajouter de l'espace pour les séparateurs et le caractère nul de fin
    total_length += count - 1;  // Pour les espaces ou autres séparateurs
    total_length += 1;          // Pour le caractère nul de fin

    // Allouer de la mémoire pour la chaîne résultante
    char *result = (char *)malloc(total_length * sizeof(char));
    if (result == NULL) {
        fprintf(stderr, "Erreur d'allocation de mémoire\n");
        exit(1);
    }

    // Initialiser la chaîne résultante avec une chaîne vide
    result[0] = '\0';

    // Concaténer les chaînes
    for (int i = 0; i < count; i++) {
        strcat(result, strings[i]);
        if (i < count - 1) {
            strcat(result, " ");  // Ajouter un espace entre les mots, par exemple
        }
    }

    return result;
}

int main() {
    char *strings[] = {"Bonjour", "le", "monde"};
    int count = sizeof(strings) / sizeof(strings[0]);

    char *result = concat_strings(strings, count);
    printf("Résultat : %s\n", result);

    // Libérer la mémoire allouée
    free(result);

    return 0;
}

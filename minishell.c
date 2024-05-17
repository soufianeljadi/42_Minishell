/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 23:52:10 by sdiouane          #+#    #+#             */
/*   Updated: 2024/05/16 16:46:22 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void supprimerGuillemets__(char *chaine)
{
    int i = 0;
	int j = 0;

    while (chaine[i])
	{
        if (chaine[i] != '\'')
            chaine[j++] = chaine[i];
        i++;
    }
    chaine[j] = '\0';
}

// char* protect_single_quote(const char* input)
// {
//     size_t input_length = strlen(input);
//     // Allouer suffisamment de mémoire pour la chaîne de sortie
//     char* output = (char*)malloc((input_length * 2 + 1) * sizeof(char)); // *2 pour la possibilité de doubler la longueur
//     if (output == NULL)
//         exit(EXIT_FAILURE);

//     size_t output_index = 0;
//     for (size_t i = 0; i < input_length; ++i) {
//         if (input[i] == '\'' || input[i] == '"') {
//             // Ajouter un backslash
//             output[output_index++] = '\\';
//         }
//         // Ajouter le caractère actuel
//         output[output_index++] = input[i];
//     }
//     // Ajouter le caractère de fin de chaîne
//     output[output_index] = '\0';
//     return output;
// }


void supprimerGuillemetsdoll(char *chaine)
{
    int i = 0;
	int j = 0;

    while (chaine[i])
	{
        if (chaine[i] != '$')
            chaine[j++] = chaine[i];
        i++;
    }
    chaine[j] = '\0';
}

int is_single(char *str)
{
	int s;
	int d;
	int i;

	(1) && (i = 0, s = 0, d = 0);
	while (str[i])
	{
		if (str[i] == '\'' && d == 0)
			s = s + 1;
		else if (str[i] == '"' && s == 0)
			d = d + 1;
		if (d == 2)
			d = 0;
		if (s == 2)
			s = 0;
		if (str[i] == '$' && (str[i + 1] == ' ' || str[i + 1] == '\0' || str[i + 1] == '\t'))
			return (1);
		else if (str[i] == '$' && (str[i + 1] == '"' || str[i + 1] == '\''))
			return (1);
		else if (str[i] == '$')
			break;
		i++;
	}
	if (s == 1)
		return (1);
	return (0);
}

ExecutionData *init_data(char **args, noued_cmd *cmd, s_env *export_i)
{
	ExecutionData *data;
	data = (ExecutionData *)malloc(sizeof(ExecutionData));
	if (!data)
		return (NULL);
	data->lst = cmd;
	data->args = args;
	data->export_i = export_i;
	return (data);
}


void loop_fct(ExecutionData *data, char *line)
{
	char	*pwd;
	
	pwd = NULL;
	while (42)
	{
		(pwd = print_directory(pwd), line = readline(pwd));
		if (!line)
			(printf("exit\n"),exit(0));
		if(line != NULL && only_spaces(line) == 0)
		{
			add_history(line);
			if(parsing(line) == 1)		
				syntax_error();
			else 
			{
				// protect_single_quote(line);
				data->args = line_to_args(line);
				data->lst = split_args_by_pipe(data->args);
				data->lst->cmd = ft_expanding(data->lst->cmd, data->export_i);
				(dup2(0, 3),dup2(1, 4), ft_execution(data));
				(dup2(3, 0), dup2(4, 1), close(3), close(4));
				print_command_list(data->lst);
				(free (data->args), free_noued_cmd(data->lst));
			}
		}
	}	
}

void	main_loop(char *line, s_env *export_i)
{
	char			**args;
	noued_cmd		*cmd;
	ExecutionData	*data;
	
	data = NULL;
	args = NULL;
	cmd = NULL;
	data = init_data(args, cmd, export_i);
	loop_fct(data, line);
	free(line);
	clear_history();
	free_noued_cmd(cmd);
	ft_free_tab(args);
}

void	f(void)
{     
	system("leaks minishell");					
}

int main(int ac, char **av, char **env)
{
	(void)av;
	// atexit(f);
	char *line;
	s_env *export_i;

	(export_i = NULL, line = NULL);
	if (ac != 1)
		(printf("Args not allowed !\n"),exit(EXIT_FAILURE));
	if (env[0] == NULL)
		export_i = split_export_i(export_i);
	else
		export_i = split_env(env);
	rl_catch_signals = 0;
	signals_init();
	main_loop(line, export_i);
	// free(line);
	free_s_env(export_i);
	return 0;
}

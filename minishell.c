/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jadi <sel-jadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 23:52:10 by sdiouane          #+#    #+#             */
/*   Updated: 2024/05/11 20:29:54 by sel-jadi         ###   ########.fr       */
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

void before_expanding(char **args)
{
	// char *tmp;
	int i = 0;
	int j = 0;
	while (args[i])
	{
		j = 0;
		if (args[i][j] == '"')
		{
			while (args[i][j] != '"')
				i++;
			args[i] = ft_substr2(args[i], 1, strlen(args[i]) - 1);
			supprimerGuillemets(args[i]);
			printf("tmp = %s\n", args[i]);
		}
		i++;
	}
}

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

	i = 0;
	s = d = 0;
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
		if (str[i] == '$')
			break;
		i++;
	}
	if (s == 1)
		return (1);
	else
		return (0);
	return (0);
}

ExecutionData *init_data(char **args, noued_cmd *cmd, s_env *export_i)
{
	ExecutionData *data = (ExecutionData *)malloc(sizeof(ExecutionData));
	if (!data)
		return (NULL);
	data->lst = cmd;
	data->args = args;
	data->export_i = export_i;
	return (data);
}


char	*add2write(char *dest, char *str3, int j)
{
	int	i;

	i = 0;
	if (str3)
	{
		while (str3[i])
		{
			dest[j] = str3[i];
			i++;
			j++;
		}
	}
	dest[j] = '\0';
	return (dest);
}
char	*add_write_str(char *str1, char *str2, char *str3)
{
	char	*dest;
	int		i;
	int		j;

	i = 0;
	j = 0;
	dest = malloc(sizeof(char) * (ft_strlen(str1) + ft_strlen(str2)
				+ ft_strlen(str3)  + 1));
	if (str1)
	{
		while (str1[i])
		{
			dest[j] = str1[i];
			i++;
			j++;
		}
	}
	i = 0;
	if (str2)
	{
		while (str2[i])
		{
			dest[j] = str2[i];
			i++;
			j++;
		}
	}
	add2write(dest, str3, j);
	return (dest);
}


char	*get_directory(char *pwd)
{
	char	*str;
	int		len;
	int		i;

	i = ft_strlen(pwd);
	while (i > 0)
	{
		if (pwd[i] == '/')
			break ;
		i--;
	}
	i++;
	str = malloc(sizeof(char) * ((ft_strlen(pwd) - i) + 3));
	len = 0;
	while (pwd[i] && pwd[i + 1])
	{
		str[len] = pwd[i];
		len++;
		i++;
	}
	str[len] = pwd[i];
	str[len + 1] = '>';
	str[len + 2] = ' ';
	str[len + 3] = '\0';
	return (str);
}
char	*print_directory(char *pwd)
{
	char	*directory = NULL;
	char	*pwd2 = NULL;
	char	*fin =  NULL;

	pwd2 = getcwd(NULL, 0);
	if (pwd2)
	{
		directory = get_directory(pwd2);
		fin = add_write_str((ANSI_COLOR_RED), directory ,(ANSI_COLOR_WHITE));
		free(directory);
		free(pwd);
		free(pwd2);
		return (fin);
	}
	return (pwd);
}

void loop_fct(ExecutionData *data, char *line)
{
	char	*pwd = NULL;

	(1) && (dup2(0, 3),dup2(1, 4));
	while (42)
	{
		pwd = print_directory(pwd);
		//read_line
		line = readline(pwd);
		if (!line)
			(printf("exit\n"),exit(0));
		if(line != NULL && only_spaces(line) == 0)
		{
			add_history(line);
			if(parsing(line) == 1)		
				syntax_error();
			else 
			{
				data->args = line_to_args(line);
				// if (!strcmp(data->args[0], "|"))
				// 	syntax_error();
				// ft_expanding(data->args, data->export_i);
				data->lst = split_args_by_pipe(data->args);
				ft_expanding(data->args, data->export_i);
				print_command_list(data->lst);
				(1) && (dup2(0, 3),dup2(1, 4));
				ft_execution(data);
				(1) && (dup2(3, 0), dup2(4, 1));
				(1) && (close(3), close(4));
				(free (data->args), free_noued_cmd(data->lst));
			}
		}
	}	
}

void	main_loop(char *line, s_env *export_i)
{
	char **args;
	noued_cmd *cmd;
	ExecutionData *data;
	
	data = NULL;
	args = NULL;
	cmd = NULL;
	data = init_data(args, cmd, export_i);
	loop_fct(data, line);
	free(line);
	clear_history();
	free_noued_cmd(cmd);
	// ft_free_tab(args);
}

void	f(void)
{     
	// system("lsof minishell > file");
	system("leaks minishell");					
}

int main(int ac, char **av, char **env)
{
	(void)av;
	// atexit(f);
	char *line = NULL;
	s_env *export_i = NULL;

	if (ac != 1)
		(printf("Args not allowed !\n"),exit(EXIT_FAILURE));
	if (!env[0])
		export_i = split_export_i(export_i);
	else
		export_i = split_env(env);
	//signals
	rl_catch_signals = 0;
	signal(SIGQUIT, signal_ctrl_c_d);
	signal(SIGINT, signal_ctrl_c_d);
	main_loop(line, export_i);
	// free(line);
	free_s_env(export_i);
	return 0;
}

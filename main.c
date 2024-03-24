/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 23:52:10 by sdiouane          #+#    #+#             */
/*   Updated: 2024/03/24 00:09:21 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

char **init_env(char **env)
{
	if (!env || !(*env))
		return (NULL);
	char **new_env = NULL;
	new_env = env;
	return (new_env);
}

int only_spaces(char *str)
{
	int i = 0;
	while(str[i])
	{
		if(str[i] == ' ' || str[i] == '\t')
			i++;
		else
			return (0);	
	}
	return(1);
}

int get_len_env(char **env)
{
	int i = 0;
	while (env[i])
		i++;
	return (i);	
}

void check_var_qu(char *line)
{
	int i = 0;
	
	while (line[i])
	{
		if (line[i] == '"')
		{
			while (line[i] != '$')
			{
				printf("%c", line[i]);
				i++;
			}
			if (line[i] == '$')
			{
				while (line[i] != '$')
				{
					printf("%c", line[i]);
					i++;
				}
			}
		}
		i++;
	}
}

void check_variables(char *line, s_env	*lst)
{
	int i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	while (line[i])
	{
			if (line[i] == '$' && line[i + 1] != ' ' && line[i + 1] != '\t')
			{
				i++;
				while (lst)
				{
					if (strcmp(line + i, lst->key) == 0)
					{
						printf("%s\n", lst->value);
					}
					lst = lst->next;
				}
			}
			
		i++;
		}
}

// int global_value(int n)
// {
// 	static int i;
// 	if (n != -1)
// 		i = n;
// 	return (i);
// }

//add non valuable keys 
s_env *split_env(char **env)
{
	int i = 0;
	int j = 0;
	s_env	*lst = NULL;
	while (env[i])
	{
		j = 0;
		while (env[i][j] != '=')
			j++;
		ft_lstadd_back(&lst, ft_lstnew_data(ft_substr(env[i] ,j + 1 ,strlen(env[i])) ,ft_substr(env[i] ,0 , j)));
		i++;
	}
	return (lst);
}

// void add_space(char *line) // ls>file
// {
// 	int i = 0;
// 	while (line[i] == ' ' || line[i] == '\t')
// 		i++;
// 	while (line[i] != '>'  && line[i] != '<' && line[i] != '|')
// 		i++;
// 	// while (line[i])
// 	// {
// 	// }
// 	printf("%s\n", &line[i]);
// }

int only_env(char *line)
{
	int i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	i +=3;
	while ((line[i] == ' ' || line[i] == '\t') && line[i] != '\0')
		i++;
	if(line[i] == '\0')
		return(0);
	else
	return(1);
}

int main(int ac, char **av, char **env)
{
	((void)ac, (void)av);	
	char *line = NULL;
	char **new_env;

	new_env = env;
	s_env *splited_env = NULL;
	splited_env = split_env(new_env);
	
	//signals
    rl_catch_signals = 0;
    signal(SIGQUIT, signal_ctrl_c_d);
    signal(SIGINT, signal_ctrl_c_d);

	while (1)
	{  
		//read_line
        line = readline("Minishell :$ ");
        if (!line)
        {
            printf("exit\n");
            exit(0);
        }
        if(line != NULL && only_spaces(line) == 0)
		{
			// add spaces :
			// add_space(line);
			// history :
			add_history(line);
			if(parsing(line) == 1)		
				syntax_error();
			else
			{
				// echo :
				echo_fct(line);
				// pwd :
				pwd_without_options(line);
				// unset :
				splited_env = unset_fct(line, splited_env);
				// export :
				if (!strcmp(line, "export"))
					print_export(splited_env);
				else
				{
					splited_env = export_fct(line, splited_env);
					// env :
					if (!strcmp(line, "env"))
					{
						int i = 0;
						while (line[i] == ' ' || line[i] == '\t')
							i++;
						i +=3;
						while ((line[i] == ' ' || line[i] == '\t') && line[i] != '\0')
							i++;
						if(line[i] == '\0')
							print_list(splited_env);
						else
							syntax_error();
					}
					
				}
				// $variables :
				check_variables(line, splited_env);
			}
			//exit
			if (strncmp(line, "exit", 4) == 0)
			{
				printf("exit\n");
				free(line);
				break;
			}
		}
		free(line);
		signal(SIGINT, signal_ctrl_c_d);
	}
	return 0;
}

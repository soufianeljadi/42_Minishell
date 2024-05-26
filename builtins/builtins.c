/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 01:07:33 by sel-jadi          #+#    #+#             */
/*   Updated: 2024/05/26 14:48:32 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int get_len_env(char **env)
{
	int i = 0;
	while (env[i])
		i++;
	return (i);	
}

void print_env_i(s_env *lst)
{
	while (lst)
	{
		if (!strcmp(lst->key, "PWD"))
			printf("%s=%s\n", lst->key, lst->value);
		else if (!strcmp(lst->key, "SHLVL"))
			printf("%s=%s\n", lst->key, lst->value);
		else if (!strcmp(lst->key, "_"))
			printf("%s=%s\n", lst->key, lst->value);
		lst = lst->next;
	}
}
char** split_with_quotes(const char* text)
{
    char** tokens = malloc(sizeof(char*) * MAX_TOKEN_LENGTH);
    int token_count = 0;
    int in_quote = 0;
    const char* start = text;
    const char* end = text;

    while (*end != '\0')
	{
        if (*end == '"' || *end == '\'')
		{
            in_quote = !in_quote;
            end++;
        }
		else if ((*end == ' ' || *end == '\t') && !in_quote)
		{
            int length = end - start;
            if (length > 0)
			{
                tokens[token_count] = malloc(sizeof(char) * (length + 1));
                strncpy(tokens[token_count], start, length);
                tokens[token_count][length] = '\0';
                token_count++;
            }
            while (*end == ' ' || *end == '\t') {
                end++;
            }
            start = end;
        }
		else
            end++;
    }

    int length = end - start;
    if (length > 0)
	{
        tokens[token_count] = malloc(sizeof(char) * (length + 1));
        strncpy(tokens[token_count], start, length);
        tokens[token_count][length] = '\0';
        token_count++;
    }

    tokens[token_count] = NULL;
    return tokens;
}

int	is_builtins(char **args, s_env **export_i, char **env, int *flag)
{
	char *pwd;

	if (strcmp(args[0], ""))
		supprimerGuillemets(args[0]);            
	if (!strcmp(args[0], "exit"))
	{
		printf("exit\n");
		exit(EXIT_SUCCESS);
	}
	else if (!strcmp(args[0], "echo"))
		echo_fct(args);
	else if (!strcmp(args[0], "pwd"))
	{
		pwd = getcwd(NULL, 0);
		pwd_without_options(args, pwd);
		free(pwd);
	}
	else if (!strcmp(args[0], "export"))
		*export_i = export_fct(args, *export_i, env);
	else if (!strcmp(args[0], "unset"))
		*export_i = unset_fct(args, *export_i);
	else if (!strcmp(args[0], "cd"))
		*export_i = execute_cd(args, *export_i);        
	else if (!strcmp(args[0], "env") && !args[1])
	{   
		if (*(env) || !*(env))	
			print_list(*export_i);
	}
	else
		*flag = 1;
	return (*flag);
}

int is_not_empty(char *str)
{
	int i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (1);
		i++;
	}
	return (0);
}

int builtins(ExecutionData *data)
{
	char **args = NULL;
	int flag = 0;
	if (data->lst->cmd[0] != '\0' && is_not_empty(data->lst->cmd))
	{
		args = split_with_quotes(data->lst->cmd);
		if (!args)
			return (0);
		flag = is_builtins(args, &data->export_i, data->env ,&flag);
	}
	else
		return (1);
	return(flag);
}

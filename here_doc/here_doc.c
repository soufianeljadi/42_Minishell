/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:45:36 by sdiouane          #+#    #+#             */
/*   Updated: 2024/06/05 16:59:33 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	file_exists(const char* filename)
{
    struct dirent	*entry;
	
    DIR *dir = opendir(".");
    if (dir == NULL)
        return 0;
    while ((entry = readdir(dir))!= NULL)
	{
        if (strcmp(entry->d_name, filename) == 0)
		{
            closedir(dir);
            return 1;
        }
    }
    closedir(dir);
    return 0;
}

char	*generate_name(char* base_name)
{
    char	*filename;
	
	filename = malloc(ft_strlen(base_name));
	check_memory_allocation(filename);
    if (file_exists(filename))
	{
        free(filename);
        return (generate_name(base_name));
    }
    return (filename);
}

char *expand_in_heredoc(char *commande, s_env *export_i)
{
	char	*exp_commande;
	t_p		p;
	
	(1) && (p.i = 0, p.j = 0, p.q_open = 0, p.cur_quote = 0);
	if (!commande)
		exit(exit_stat(1));
	exp_commande = ft_strdup(commande);
	check_memory_allocation(exp_commande);
	while (exp_commande && exp_commande[p.i] != '\0')
	{
		handle_quotes(exp_commande, &p);
		if (exp_commande[p.i] == '$' && exp_commande[p.i + 1] == '?')
		{
			exp_commande = ft_str_replace(exp_commande, ft_strdup("$?"), ft_itoa(exit_stat(-1)));
			check_memory_allocation(exp_commande);
		}
		if (exp_commande[p.i] == '$')
		{
			exp_commande = process_variable(exp_commande, &p, export_i);
			check_memory_allocation(exp_commande);
		}
		p.i++;
	}
	return (exp_commande);
}

int handle_delimeter(char **delim)
{
	int flag;

	flag = 0;
	if (strstr(*delim, "'") || strstr(*delim, "\""))
	{
		flag = 1;
		if (*delim[0] == '"' || *delim[0] == '\'')
		{
			*delim = ft_substr2(*delim, 1, ft_strlen(*delim) - 2);
			check_memory_allocation(*delim);
		}
		else
			supprimerGuillemets(*delim);
	}
	return (flag);
}

void	handle_heredocs(char **delem, t_data *data)
{
	int		fd;
	char	*buf;
	char	*file_name;
	int		flag;
	int		p;
	
	(1) && (p = 0, flag = 0, file_name = generate_name("tmp.txt"));
	fd = open("tmp.txt", O_TRUNC | O_CREAT | O_RDWR, 0777);
	if (fd < 0)
		exit(EXIT_FAILURE);
	(buf = readline("heredocs >> "), flag = handle_delimeter(delem));
	while (1)
	{
		if (strcmp(buf, *delem) == 0)
			break ;
		if (flag == 0)
			(buf = expand_in_heredoc(buf, data->export_i),
				check_memory_allocation(buf));
		(1) && (write(fd, buf, ft_strlen(buf)), write(fd, "\n", 1));
		buf = readline("heredocs >> ");
		check_memory_allocation(buf);
	}
	(free(buf), close(fd));
	*delem = ft_strdup("tmp.txt");
	check_memory_allocation(*delem);
}

void	check_here_doc(t_data *data)
{
	int	i;

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

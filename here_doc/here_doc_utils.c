/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jadi <sel-jadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 23:36:22 by sel-jadi          #+#    #+#             */
/*   Updated: 2024/07/15 00:44:33 by sel-jadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	file_exists(const char *filename)
{
	struct dirent	*entry;
	DIR				*dir;

	dir = opendir(".");
	entry = readdir(dir);
	if (dir == NULL)
		return (0);
	while (entry)
	{
		if (ft_strcmp(entry->d_name, filename) == 0)
		{
			closedir(dir);
			return (1);
		}
	}
	closedir(dir);
	return (0);
}

int	handle_delimeter(char **delim)
{
	int	flag;

	flag = 0;
	if (ft_strstr(*delim, "'") || ft_strstr(*delim, "\""))
		flag = 1;
	del_dbl_quotes(*delim);
	del_sngl_quotes(*delim);
	*delim = ft_check(*delim);
	return (flag);
}

void	cleanup_heredoc(int fd, char	**delem, char	*file_name)
{
	close(fd);
	signals_init();
	free(*delem);
	*delem = ft_strdup(file_name);
	free(file_name);
}

char	*generate_name(char *base_name)
{
	char	*filename;

	filename = ft_malloc(ft_strlen(base_name));
	check_memory_allocation(filename);
	if (file_exists(filename))
	{
		free(filename);
		return (generate_name(base_name));
	}
	return (filename);
}

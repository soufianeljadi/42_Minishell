/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   promt.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 20:27:18 by sel-jadi          #+#    #+#             */
/*   Updated: 2024/06/05 15:10:34 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add2write(char *dest, char *str, int *j)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			dest[*j] = str[i];
			i++;
			(*j)++;
		}
	}
}

char	*add_write_str(char *str1, char *str2, char *str3)
{
	char	*dest;
	int		j;

	j = 0;
	dest = malloc(sizeof(char) * (ft_strlen(str1)
				+ ft_strlen(str2) + ft_strlen(str3) + 1));
	add2write(dest, str1, &j);
	add2write(dest, str2, &j);
	add2write(dest, str3, &j);
	dest[j] = '\0';
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
	char	*directory;
	char	*pwd2;
	char	*fin;

	directory = NULL;
	pwd2 = NULL;
	fin = NULL;
	pwd2 = getcwd(NULL, 0);
	if (pwd2)
	{
		directory = get_directory(pwd2);
		fin = add_write_str((ANSI_COLOR_GREEN), directory, (ANSI_COLOR_WHITE));
		free(directory);
		free(pwd);
		free(pwd2);
		return (fin);
	}
	return (pwd);
}

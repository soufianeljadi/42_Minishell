/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_two.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jadi <sel-jadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 15:23:54 by sdiouane          #+#    #+#             */
/*   Updated: 2024/07/14 00:18:02 by sel-jadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*ft_strcpy(char *dest, const char *src)
{
	char		*d;
	const char	*s;

	d = dest;
	s = src;
	while (*s != '\0')
	{
		*d = *s;
		d++;
		s++;
	}
	*d = '\0';
	return (dest);
}

char	*my_strjoin(char const *s1, char const *s2)
{
	char	*joined;
	size_t	len1;
	size_t	len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	joined = ft_malloc(len1 + len2 + 1);
	if (!joined)
		return (NULL);
	ft_strcpy(joined, s1);
	ft_strcat(joined, s2);
	return (joined);
}

void	handle_path_error(char **cmd)
{
	ft_free_tab(cmd);
	exit(EXIT_FAILURE);
}

void	supprimer_protection(char *chaine)
{
	char	*source;
	char	*destination;

	(1) && (source = chaine, destination = chaine);
	while (*source != '\0')
	{
		if (*source != '\\')
		{
			*destination = *source;
			destination++;
		}
		source++;
	}
	*destination = '\0';
}

int	is_blank(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			i++;
		else
			return (0);
	}
	return (1);
}

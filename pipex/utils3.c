/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 22:39:38 by sdiouane          #+#    #+#             */
/*   Updated: 2023/12/27 23:51:52 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//substr
char	*ft_strdup(const char *s1)
{
	char	*s2;
	int		i;
	int		len;

	i = 0;
	len = strlen(s1);
	s2 = (char *)malloc(sizeof(char) * (len + 1));
	if (!s2)
		return (NULL);
	while (s1[i] != '\0')
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

//strcmp
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*p1;
	unsigned char	*p2;

	i = 0;
	p1 = (unsigned char *)s1;
	p2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (p1[i] == p2[i] && (p1[i] != '\0' && p2[i] != '\0') && i < n - 1)
		i++;
	return (p1[i] - p2[i]);
}

//strjoin
static size_t	ft_strlcat(char	*dest, const char	*src, size_t	size)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	if ((!dest && !size) || !size)
		return (strlen(src));
	while (dest[j] && j < size)
		j++;
	while (src[i] && size && (j + i) < size - 1)
	{
		dest[j + i] = src[i];
		i++;
	}
	if (j < size)
		dest[j + i] = '\0';
	i = 0;
	while (src[i])
		i++;
	return (j + i);
}

static size_t	ft_strlcpy(char	*dst, const char	*src, size_t	size)
{
	size_t	j;
	size_t	i;

	j = 0;
	i = 0;
	while (src[j] != '\0')
		j++;
	if (size == 0)
		return (j);
	while (src[i] != '\0' && i < (size - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (j);
}

char	*ft_strjoin(char const	*s1, char const	*s2)
{
	char	*str;
	size_t	len1;
	size_t	len2;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len1 = strlen(s1);
	len2 = strlen(s2);
	str = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, (char *)s1, len1 + 1);
	ft_strlcat(str + (len1), (char *)s2, len2 + 1);
	return (str);
}

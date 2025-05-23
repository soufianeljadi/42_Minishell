/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jadi <sel-jadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 16:59:26 by sdiouane          #+#    #+#             */
/*   Updated: 2025/05/18 21:06:53 by sel-jadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup(char *s1)
{
	char	*s2;
	int		i;
	int		len;

	if (!s1)
		return (NULL);
	i = 0;
	len = ft_strlen(s1);
	s2 = (char *)ft_malloc(sizeof(char) * (len + 1));
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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	if (!s)
		return (NULL);
	if (!len || start >= ft_strlen(s))
		return (ft_strdup(""));
	i = ft_strlen(s) - start ;
	if (i > len)
		i = len;
	str = (char *)ft_malloc(sizeof(char) * (i + 1));
	if (!str)
		return (0);
	ft_strncpy(str, s + start, i + 1);
	return (str);
}

char	*ft_substr2(const char *inp, int start, int end)
{
	int		len;
	char	*s;
	int		i;

	i = 0;
	len = end - start;
	s = NULL;
	s = (char *)ft_malloc(len + 2);
	if (!s)
		return (syntax_error(), NULL);
	while (end >= start + i)
	{
		s[i] = inp[i + start];
		i++;
	}
	s[i] = '\0';
	return (s);
}

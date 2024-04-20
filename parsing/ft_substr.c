/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 16:59:26 by sdiouane          #+#    #+#             */
/*   Updated: 2024/04/20 08:26:39 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup(char *s1)
{
	char	*s2;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(s1);
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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	if (!s)
		return (NULL);
	if (!len || start >= strlen(s))
		return (ft_strdup(""));
	i = strlen(s) - start ;
	if (i > len)
		i = len;
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (0);
	strlcpy(str, s + start, i + 1);
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
	s = (char *)malloc(len + 2);
	if (!s)
		return (syntax_error(),  NULL);
	while (end >= start + i)
	{
		s[i] = inp[i + start];
		i++;
	}
	s[i] = '\0';
	return (s);
}

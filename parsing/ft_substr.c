/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jadi <sel-jadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 16:59:26 by sdiouane          #+#    #+#             */
/*   Updated: 2024/03/26 00:38:39 by sel-jadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	if (!s)
		return (NULL);
	if (!len || start >= strlen(s))
		return (strdup(""));
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
	while (start + i <= end)
	{
		s[i] = inp[i + start];
		i++;
	}
	s[i] = '\0';
	return (s);
}
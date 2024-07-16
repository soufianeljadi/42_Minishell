/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_space_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jadi <sel-jadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:00:39 by sdiouane          #+#    #+#             */
/*   Updated: 2024/07/11 23:24:06 by sel-jadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_wrds(char const *s, char c)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		while (s[i] == c || s[i] == '\t')
			i++;
		if (s[i] != '\0')
			cnt++;
		while ((s[i] != '\t' && s[i] != c) && s[i])
			i++;
	}
	return (cnt);
}

static char	*allocation_words(const char *s1, int n)
{
	int		i;
	char	*new;

	i = 0;
	new = (char *)ft_malloc(n + 1);
	if (!new)
		return (NULL);
	while (i < n)
	{
		new[i] = s1[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	**split_space_tab(char *s, char c)
{
	int		i;
	int		j;
	int		len;
	char	**ch;

	(1) && (len = count_wrds(s, c), j = -1);
	ch = (char **)ft_malloc((sizeof(char *)) * (len + 1));
	if (!ch)
		return (NULL);
	while (++j < len)
	{
		i = 0;
		while (*s && (*s == c || *s == '\t'))
			s++;
		while ((*(s + i) != '\t' && *(s + i) != c) && *(s + i))
			i++;
		ch[j] = allocation_words(s, i);
		if (!ch[j])
			return (ft_free_tab(ch), NULL);
		s += i;
	}
	ch[j] = NULL;
	return (ch);
}

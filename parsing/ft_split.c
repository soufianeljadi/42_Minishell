/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jadi <sel-jadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 23:51:36 by sdiouane          #+#    #+#             */
/*   Updated: 2024/07/11 23:24:47 by sel-jadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_words(char const *s, char c)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
			cnt++;
		while (s[i] != c && s[i])
			i++;
	}
	return (cnt);
}

static char	*mall_wrd(const char *s1, int n)
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

void	ft_free_tab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	**ft_split(char	*s, char c)
{
	int		i;
	int		j;
	int		len;
	char	**ch;

	len = count_words(s, c);
	j = -1;
	ch = (char **)ft_malloc((sizeof(char *)) * (len + 1));
	if (!ch)
		return (NULL);
	while (++j < len)
	{
		i = 0;
		while (*s && *s == c)
			s++;
		while (*(s + i) != c && *(s + i))
			i++;
		ch[j] = mall_wrd(s, i);
		if (!ch[j])
			ft_free_tab(ch);
		while (*s && *s != c)
			s++;
	}
	ch[j] = NULL;
	return (ch);
}

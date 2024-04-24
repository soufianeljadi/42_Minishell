/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 22:15:00 by sdiouane          #+#    #+#             */
/*   Updated: 2024/01/02 15:58:10 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
//split
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
	new = (char *)malloc(n + 1);
	if (new == NULL)
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

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		len;
	char	**ch;

	len = count_words(s, c);
	j = -1;
	ch = (char **)malloc((sizeof(char *)) * (len + 1));
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

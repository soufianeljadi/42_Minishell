/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_sep.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 23:56:31 by sel-jadi          #+#    #+#             */
/*   Updated: 2024/06/05 10:07:45 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_add(char c, char *s, int index)
{
	int		len;
	char	*tmp;

	len = strlen(s);
	tmp = (char *)malloc(sizeof(char) * (len + 2));
	if (!tmp)
	{
		free(s);
		return (NULL);
	}
	for (int i = 0, j = 0; i <= len; i++, j++)
	{
		if (j == index)
			tmp[j++] = c;
		tmp[j] = s[i];
	}
	tmp[len + 1] = '\0';
	return (tmp);
}

int	ft_sep_red(char **s, int *i)
{
	if ((*s)[*i + 1] == (*s)[*i])
	{
		*s = ft_add(' ', *s, *i);
		if (*s == NULL)
			return (-1);
		(*i) += 2;
	}
	else if ((*s)[*i] == '>' || (*s)[*i] == '<')
	{
		*s = ft_add(' ', *s, *i);
		if (*s == NULL)
			return (-1);
		(*i)++;
	}
	(*i)++;
	*s = ft_add(' ', *s, *i);
	if (*s == NULL)
		return (-1);
	return (1);
}

void	ft_count_quotes(char *s, int i, t_parse *d)
{
	if (s[i] == '\'' && d->dq == 0)
		(d->sq)++;
	if (s[i] == '"' && d->sq == 0)
		(d->dq)++;
	if (d->sq == 2)
		d->sq = 0;
	else if (d->dq == 2)
		d->dq = 0;
}

int	check_after(char *s, int i)
{
	while (s[i])
	{
		if (s[i] == ' ' || s[i] == '\t')
			i++;
		else
			return (0);
	}
	return (1);
}

char	*ft_add_sep(char *s, t_parse d)
{
	if (!s)
		return (NULL);
	d.i = 0;
	d.dq = 0;
	d.sq = 0;
	while (s[(d.i)] != '\0')
	{
		if (s[d.i] == '\'' || s[d.i] == '"')
			ft_count_quotes(s, d.i, &d);
		else if ((s[d.i] == '>' || s[d.i] == '<') && (d.sq == 0 && d.dq == 0))
		{
			if (ft_sep_red(&s, &(d.i)) == -1)
				return (NULL);
		}
		else if ((s[d.i] == '|') && (d.sq == 0 && d.dq == 0))
		{
			s = ft_add(' ', s, d.i);
			if (s == NULL)
				return (NULL);
			d.i += 2;
			s = ft_add(' ', s, d.i);
			if (s == NULL)
				return (NULL);
		}
		d.i++;
	}
	return (s);
}

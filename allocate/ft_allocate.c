/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_allocate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:40:04 by sdiouane          #+#    #+#             */
/*   Updated: 2024/05/23 13:52:26 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_memset(void	*b, int c, size_t	len)
{
	unsigned char	*p;
	size_t			i;

	p = (unsigned char *)b;
	i = 0;
	while (i < len)
	{
		p[i] = c;
		i++;
	}
	return (b);
}

void	ft_bzero(void *b, size_t n)
{
	ft_memset(b, 0, n);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*tmp;
	size_t	len;

	len = count * size;
	tmp = malloc(len);
	if (!tmp)
		return (NULL);
	ft_bzero(tmp, len);
	return (tmp);
}

void	*allocate(t_allocate **collec, size_t count, size_t size)
{
	t_allocate	*new;

	new = malloc(sizeof(t_allocate));
	if (!new)
		return (NULL);
	new->block = ft_calloc(count, size);
	if (!new->block)
		return (free(new), NULL);
	(1) && (new->next = *collec, *collec = new);
	return (new->block);
}

void	cleanup(t_allocate **collec)
{
	t_allocate	*set;
	t_allocate	*next;

	set = *collec;
	while (set)
	{
		next = set->next;
		if (set->block)
			free(set->block);
		(free(set), set = next);
	}
	*collec = NULL;
}

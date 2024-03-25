/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 16:59:01 by sdiouane          #+#    #+#             */
/*   Updated: 2024/03/25 16:59:06 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

char	*ft_strchr(const char *str, int c)
{
	int		i;
	char	*test;

	i = 0;
	test = (char *)str;
	while (test[i] != (char)c)
	{
		if (test[i] == '\0')
			return (0);
		i++;
	}
	return (&test[i]);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jadi <sel-jadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 16:59:01 by sdiouane          #+#    #+#             */
/*   Updated: 2024/05/03 18:45:45 by sel-jadi         ###   ########.fr       */
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

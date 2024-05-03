/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtock.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jadi <sel-jadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 22:28:09 by sdiouane          #+#    #+#             */
/*   Updated: 2024/05/03 18:48:37 by sel-jadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strtok(char *str, const char *delim)
{
	static char	*remainder;
	char		*ret;
	int			len;

	if (str)
		remainder = str;
	if (!remainder)
		return (NULL);
	while (*remainder && ft_strchr(delim, *remainder))
		remainder++;
	len = 0;
	while (remainder[len] && !ft_strchr(delim, remainder[len]))
		len++;
	if (!len)
		return (NULL);
	ret = ft_substr(remainder, 0, len);
	remainder += len;
	if (*remainder && ft_strchr(delim, *remainder))
		remainder++;
	return (ret);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 16:59:26 by sdiouane          #+#    #+#             */
/*   Updated: 2024/03/25 16:59:28 by sdiouane         ###   ########.fr       */
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

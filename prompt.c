/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jadi <sel-jadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:07:35 by sel-jadi          #+#    #+#             */
/*   Updated: 2024/03/13 14:07:49 by sel-jadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putchar_fd(char c, int fd)
{
	if (fd >= 0)
		write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (fd >= 0)
	{
		while (s && *s)
		{
			ft_putchar_fd(*s, fd);
			s++;
		}
	}
}

char *prompt() {
    char *tmp;
    size_t len;
    size_t count_slash;

    tmp = getcwd(NULL, 0);
    len = strlen(tmp);
    count_slash = 0;
    while (--len && count_slash < 3)
        if (tmp[len] == '/')
            count_slash++;
    while (tmp[++len])
        ft_putchar_fd(tmp[len], 1);
    ft_putstr_fd("$ ", 1);
    free(tmp);
    return NULL;
}
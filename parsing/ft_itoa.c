/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 06:29:59 by sel-jadi          #+#    #+#             */
/*   Updated: 2024/07/16 16:05:22 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_intlen(int n)
{
	int	i;

	i = 1;
	if (n == -2147483648)
		return (11);
	else
	{
		if (n < 0)
		{
			n = n * -1;
			i++;
		}
		while (n > 9)
		{
			n = n / 10;
			i++;
		}
		return (i);
	}
}

static int	sign(char *p, int n)
{
	int	i;

	i = 0;
	if (n == -2147483648)
	{
		p[i] = '-';
		p[++i] = '2';
		n = 147483648;
	}
	if (n < 0)
	{
		p[i] = '-';
		n = n * -1;
	}
	return (n);
}

char	*ft_itoa(unsigned int n)
{
	char	*p;
	int		i;
	int		len;

	i = 0;
	len = ft_intlen(n);
	p = (char *)ft_malloc(sizeof(*p) * (len + 1));
	if (!p)
		return (0);
	p[len] = '\0';
	n = sign(p, n);
	while (n > 9)
	{
		p[len - 1] = (n % 10) + '0';
		len--;
		n = n / 10;
	}
	if (n <= 9)
		p[len - 1] = n + '0';
	return (p);
}

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi( char *str)
{
	int		i;
	int		s;
	long	x;

	i = 0;
	s = 1;
	x = 0;
	if (!str[0])
		return (-1);
	while (str[i] == ' ')
		i++;
	if ((str[i] == '-' || str[i] == '+') && (str[i + 1]))
		s = 44 - str[i++];
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (-1);
		if (((x * 10 + str[i] - '0') > 2147483647 && s == 1)
			|| ((x * 10 + str[i] - '0') > 2147483648 && s == -1))
			return (-1);
		x = x * 10 + str[i] - '0';
		i++;
	}
	return (x * s);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jadi <sel-jadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 06:29:59 by sel-jadi          #+#    #+#             */
/*   Updated: 2024/04/07 21:30:19 by sel-jadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


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
	p = (char *)malloc(sizeof(*p) * (len + 1));
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
//atoi
static int	ft_sing(const char *str, int *hi)
{
	int	sign;
	int	i;

	i = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	if (str[i] == 45 || str[i] == 43)
	{
		if (str[i] == 45)
			sign *= -1;
		i++;
	}
	*hi = i;
	return (sign);
}
int	ft_atoi(const char *str)
{
	int	sign;
	int	result;
	int	i;

	result = 0;
	i = 0;
	sign = ft_sing(str, &i);
	while (str[i] && str[i] >= 48 && str[i] <= 57)
	{
		result *= 10;
		result += str[i] - 48;
		i++;
	}
	result *= sign;
	return (result);
}
#include "minishell.h"

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

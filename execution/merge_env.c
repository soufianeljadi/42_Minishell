/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 09:54:49 by sdiouane          #+#    #+#             */
/*   Updated: 2024/06/05 18:50:41 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_lstsize(void  *lst)
{
	int		c;
	s_env	*p;

	c = 0;
	p = lst;
	while (p)
	{
		p = p->next;
		c++;
	}
	return (c);
}

char	**ft_merge_envr(s_env *export_i)
{
	char	**str;
	int		len;
	int		i;
	s_env	*temp;

	(1) && (i = 0, str = NULL);
	len = ft_lstsize(export_i);
	str = malloc(sizeof(char *) * (len + 1));
	if (!str)
		return (NULL);
	temp = export_i;
	while (temp)
	{
		str[i] = ft_strdup("");
		str[i] = ft_strjoin(str[i], temp->key);
		if (temp->value)
		{
			str[i] = ft_strjoin(str[i], "=");
			str[i] = ft_strjoin(str[i], temp->value);
		}
		temp = temp->next;
		i++;
	}
	str[i] = NULL;
	return (str);
}

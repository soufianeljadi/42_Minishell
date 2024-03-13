/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lsts.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 00:32:13 by sdiouane          #+#    #+#             */
/*   Updated: 2024/03/13 01:03:55 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_sep	*create_cell(char *cmd_sep)
// {
//   t_sep	*cell;

//   cell = malloc(sizeof(t_sep));
//   if (!(cell))
//   	return (NULL);
//   cell->next = NULL;
//   cell->cmd_sep = cmd_sep;
//   return (cell);
// }

// t_sep	*add_cell(t_sep *list, char *cmd_sep, int pos)
// {
//   t_sep	*cur;
//   t_sep	*cell;
//   int		i;

//   cur = list;
//   i = 0;
//   cell = create_cell(cmd_sep);
//   if (list == NULL)
//   	return (cell);
//   while (i < pos)
//   {
//   	i++;
//   	cur = cur->next;
//   }
//   cell->next = cur;
//   return (list);
// }

t_sep	*ft_lstnew(char *data)
{
	t_sep	*b;

	b = (t_sep *)malloc(sizeof(t_sep));
	if (!b)
		exit(EXIT_FAILURE);
	b ->cmd_sep = data;
	b ->next = NULL;
	return (b);
}

void	ft_lstadd_back(t_sep **lst, t_sep *new)
{
	t_sep	*tmp;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
    

}

void	print_list(t_sep *list)
{
  int		i;

  i = 0;
  while (list)
  {
  	printf("-----------------------------------\n");
  	printf("| i = %d                            \n", i);
  	printf("| list->cmd_sep : %s            \n", list->cmd_sep);
  	printf("-----------------------------------\n");
  	list = list->next;
  	i++;
  }
}
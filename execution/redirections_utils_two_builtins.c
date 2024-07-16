/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils_two_builtins.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 01:29:40 by sel-jadi          #+#    #+#             */
/*   Updated: 2024/07/16 11:38:58 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	put_ambiguous_builtins(char *redirection)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(redirection, 2);
	ft_putstr_fd(": ambiguous redirect\n", 2);
}

void	put_errno_builtins(char *redirection)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(redirection, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errno), 2);
}

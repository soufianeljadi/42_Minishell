/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 22:30:21 by sdiouane          #+#    #+#             */
/*   Updated: 2024/06/08 07:50:07 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_sigint_heredoc(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	exit(2);
}

static void	signal_ctrl_c(int signal)
{
	(void)signal;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	exit_stat(1);
}

static void	signal_ctrl_d(int sig)
{
	(void)sig;
	rl_redisplay();
	exit(1);
}

void	signals_init(void)
{
	signal(SIGINT, signal_ctrl_c);
	signal(SIGQUIT, signal_ctrl_d);
}

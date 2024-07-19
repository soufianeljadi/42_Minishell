/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jadi <sel-jadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 22:30:21 by sdiouane          #+#    #+#             */
/*   Updated: 2024/07/19 23:07:31 by sel-jadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_signal = 0;

void	handle_sigint_heredoc(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	exit(0);
}

static void	signal_ctrl_c(int signal)
{
	(void)signal;
	rl_on_new_line();
	printf("\n");
	g_signal = 1;
	rl_replace_line("", 0);
	rl_redisplay();
	exit_stat(1);
}

void	signals_init(void)
{
	signal(SIGINT, signal_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}

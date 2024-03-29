/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jadi <sel-jadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 22:30:21 by sdiouane          #+#    #+#             */
/*   Updated: 2024/03/25 21:34:30 by sel-jadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void signal_ctrl_c_d(int signal)
{
    if (signal == SIGINT || signal == SIGQUIT) {
        rl_on_new_line();
        printf("\n");
        rl_replace_line("", 0);
        rl_redisplay();
    }
}
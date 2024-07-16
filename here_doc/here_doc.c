/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:45:36 by sdiouane          #+#    #+#             */
/*   Updated: 2024/07/16 22:17:25 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expand_in_heredoc(char *commande, t_env *export_i)
{
	char	*exp_commande;
	t_p		p;

	(1) && (p.i = 0, p.j = 0, p.q_open = 0, p.cur_quote = 0);
	if (!commande)
		exit(exit_stat(1));
	exp_commande = ft_strdup(commande);
	check_memory_allocation(exp_commande);
	while (exp_commande && exp_commande[p.i] != '\0')
	{
		handle_quotes(exp_commande, &p);
		if (exp_commande[p.i] == '$' && exp_commande[p.i + 1] == '?')
		{
			exp_commande = ft_str_replace(exp_commande,
					ft_strdup("$?"), ft_itoa(exit_stat(-1)));
			check_memory_allocation(exp_commande);
		}
		if (exp_commande[p.i] == '$')
		{
			exp_commande = prc_variable(exp_commande, &p, export_i);
			check_memory_allocation(exp_commande);
		}
		p.i++;
	}
	return (free(commande), exp_commande);
}

void	process_heredoc(int fd, char *delem, int flag, t_data *data)
{
	char	*buf;

	buf = NULL;
	while (1)
	{
		buf = readline("heredocs >> ");
		if (buf && ft_strcmp(buf, delem) == 0)
		{
			free(buf);
			break ;
		}
		if (!buf)
			return ;
		if (flag == 0)
		{
			buf = expand_in_heredoc(buf, data->export_i);
			check_memory_allocation(buf);
		}
		write(fd, buf, ft_strlen(buf));
		write(fd, "\n", 1);
		if (buf)
			free(buf);
	}
}

char	*setup_heredoc(int *fd)
{
	char	*file_name;

	file_name = ft_strdup("/tmp/tmp.txt");
	*fd = open(file_name, O_TRUNC | O_CREAT | O_RDWR, 0777);
	if (*fd < 0)
		exit(EXIT_FAILURE);
	return (file_name);
}

void	handle_heredocs(char **delem, t_data *data)
{
	char	*file_name;
	int		fd;
	int		flag;
	int		pid;

	file_name = setup_heredoc(&fd);
	flag = handle_delimeter(delem);
	rl_catch_signals = 1;
	pid = fork();
	if (pid < 0)
		(perror("fork"), exit(EXIT_FAILURE));
	if (pid == 0)
	{
		signal(SIGINT, handle_sigint_heredoc);
		process_heredoc(fd, *delem, flag, data);
		exit(0);
	}
	else
	{
		waitpid(pid, NULL, 0);
		signal(SIGINT, SIG_IGN);
		signal(SIGINT, SIG_DFL);
		cleanup_heredoc(fd, delem, file_name);
	}
	rl_catch_signals = 0;
}

void	check_here_doc(t_data *data)
{
	int	i;

	i = 0;
	if (!data->args)
		return ;
	while (data->args[i] && !g_signal)
	{
		if (!ft_strcmp(data->args[i], "<<") && data->args[i + 1])
		{
			handle_heredocs(&data->args[i + 1], data);
		}
		i++;
	}
}

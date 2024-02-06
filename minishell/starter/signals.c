/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabdul-k <fabdul-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 20:13:11 by tponnusa          #+#    #+#             */
/*   Updated: 2024/02/02 13:51:35 by fabdul-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	event(void)
{
	return (EXIT_SUCCESS);
}

void	sigint_handler(int sig)
{
	if (g_sig_interrupt == 101 || g_sig_interrupt == 102)
	{
		g_sig_interrupt = 1;
		rl_redisplay();
		rl_done = 1;
		return ;
	}
	if (g_sig_interrupt == 100)
	{
		g_sig_interrupt = 1;
		rl_replace_line("", 0);
		rl_redisplay();
		rl_done = 1;
		return ;
	}
	(void) sig;
}

int	handle_eof(char *command_line)
{
	if (!command_line)
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}

void	init_signals(void)
{
	rl_event_hook = event;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabdul-k <fabdul-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:39:15 by tponnusa          #+#    #+#             */
/*   Updated: 2024/02/01 21:21:08 by fabdul-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	check_input(char **cmds, t_shell *data, int len)
{
	if (len == 1)
	{
		ft_putendl_fd("exit", 1);
		exit_mini_shell(data, 0);
	}
	if (len == 2 && cmds[1] && is_number(cmds[1]))
	{
		if (ft_atoi(cmds[1]) <= 255)
		{
			data -> status_code = ft_atoi(cmds[1]);
			ft_putendl_fd("exit", 1);
			exit_mini_shell(data, 1);
		}
		else if (ft_atoi(cmds[1]) <= LLONG_MAX && ft_atoi(cmds[1]) >= LLONG_MIN)
		{
			ft_putendl_fd("exit", 1);
			data -> status_code = ft_atoi(cmds[1]) % 256;
			exit_mini_shell(data, 1);
		}
	}
	return (EXIT_FAILURE);
}

void	call_exit(char **cmds, t_shell *data)
{
	int	len;

	len = ft_strlen_2(cmds);
	if (!check_input(cmds, data, len))
		return ;
	if (cmds[1] && !is_number(cmds[1]))
	{
		ft_putendl_fd("exit", 1);
		print_error2(14, data);
	}
	else if (len > 2)
	{
		ft_putendl_fd("exit", 1);
		data->status_code = EXIT_FAILURE;
		print_error2(15, data);
	}
}

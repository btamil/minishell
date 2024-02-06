/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabdul-k <fabdul-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 17:13:39 by tponnusa          #+#    #+#             */
/*   Updated: 2024/01/25 23:49:01 by fabdul-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_option_n(char *s)
{
	int	i;

	i = 2;
	if (s)
	{
		if (s[0] == '-' && s[1] == 'n')
		{
			while (s[i] && s[i] == 'n')
				i++;
			if (s[i] == '\0')
				return (1);
		}
	}
	return (0);
}

void	call_echo(char **cmds, t_shell *data)
{
	int	len;
	int	i;
	int	is_option_enabled;

	len = ft_strlen_2(cmds);
	i = 1;
	is_option_enabled = 0;
	if (check_option_n(cmds[1]))
	{
		is_option_enabled = 1;
		i++;
	}
	while (i < len && check_option_n(cmds[i]))
		i++;
	while (i < len && cmds[i])
	{
		ft_putstr_fd(cmds[i], 1);
		if (cmds[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (!is_option_enabled)
		ft_putstr_fd("\n", 1);
	data->status_code = EXIT_SUCCESS;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabdul-k <fabdul-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:22:50 by tponnusa          #+#    #+#             */
/*   Updated: 2024/02/02 14:32:14 by fabdul-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_valid_input(char *cmd)
{
	int	i;

	i = 1;
	if (cmd && (cmd[0] == '_' || ft_isalpha(cmd[0])))
	{
		while (cmd[i] && cmd[i] != '=')
		{
			if (check_special_sympols(cmd[i]))
				return (0);
			i++;
		}
	}
	else
		return (0);
	return (1);
}

void	call_unset(char **cmds, t_shell *data)
{
	int	len;
	int	i;
	int	status_flag;

	i = 1;
	len = ft_strlen_2(cmds);
	status_flag = 0;
	if (len == 1)
		return ;
	while (cmds[i])
	{
		if (is_valid_input(cmds[i]))
		{
			if (is_key_present(data->env, cmds[i]))
				delete_node(cmds[i], &data -> env);
		}
		else
		{
			status_flag = 1;
			print_error_exec(13);
		}
		i++;
	}
	data -> status_code = status_flag;
}

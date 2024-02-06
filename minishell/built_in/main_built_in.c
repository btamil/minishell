/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponnusa <tponnusa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 13:49:24 by tponnusa          #+#    #+#             */
/*   Updated: 2024/02/02 12:58:42 by tponnusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_env(char **cmds, t_shell *data)
{
	if (ft_strlen_2(cmds) > 1)
	{
		data->status_code = COMMAND_NOT_FOUND;
		print_error(5);
	}
	else
	{
		print_env(0, &data->env);
	}
}

int	is_built_in(char **cmds)
{
	if (cmds && cmds[0] && ((ft_strcmp(cmds[0], "cd") == 0)
			|| (ft_strcmp(cmds[0], "export") == 0)
			|| (ft_strcmp(cmds[0], "unset") == 0)
			|| (ft_strcmp(cmds[0], "pwd") == 0)
			|| (ft_strcmp(cmds[0], "echo") == 0)
			|| (ft_strcmp(cmds[0], "env") == 0)
			|| (ft_strcmp(cmds[0], "exit") == 0)))
		return (1);
	else
		return (0);
}

int	execute_built_ins(t_shell *data, char **cmds)
{
	char	*tmp;

	tmp = NULL;
	if (ft_strcmp(cmds[0], "cd") == 0)
		return (call_cd_execution(data, cmds), data->status_code);
	else if (ft_strcmp(cmds[0], "env") == 0)
		return (exec_env(cmds, data), data->status_code);
	else if (ft_strcmp(cmds[0], "export") == 0)
		return (call_export(cmds, data), data->status_code);
	else if (ft_strcmp(cmds[0], "unset") == 0)
		return (call_unset(cmds, data), data->status_code);
	else if (ft_strcmp(cmds[0], "exit") == 0)
		call_exit(cmds, data);
	else if (ft_strcmp(cmds[0], "echo") == 0)
		return (call_echo(cmds, data), data->status_code);
	else if (ft_strcmp(cmds[0], "pwd") == 0)
	{
		tmp = get_env_value("PWD", &data->env);
		if (tmp != NULL)
		{
			ft_putendl_fd(tmp, 1);
		}
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

void	execute_built_in_main(t_shell *data)
{
	if (execute_built_ins(data, data->command->args) == 1)
	{
		data->status_code = EXIT_FAILURE;
		return ;
	}
}

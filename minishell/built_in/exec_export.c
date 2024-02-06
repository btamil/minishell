/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponnusa <tponnusa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 18:06:43 by tponnusa          #+#    #+#             */
/*   Updated: 2024/02/06 12:52:46 by tponnusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_key(char *cmd, int j)
{
	char	*new_key;

	new_key = NULL;
	if (j > 0 && cmd[j - 1] && cmd[j - 1] == '+')
		new_key = ft_substr(cmd, 0, j - 1);
	else
		new_key = ft_substr(cmd, 0, j);
	return (new_key);
}

void	get_export_pair(int index, char **cmds, t_shell *data)
{
	int		j;
	char	*new_key;
	char	*new_value;
	int		is_value;

	new_key = NULL;
	new_value = NULL;
	is_value = 0;
	j = 0;
	while (cmds[index][j])
	{
		if (cmds[index][j] == '=')
		{
			new_key = get_key(cmds[index], j);
			new_value = ft_substr(cmds[index], j + 1,
					ft_strlen(cmds[index]) - j);
			is_value = 1;
			break ;
		}
		j++;
	}
	if (!is_value)
		add_to_list(new_key, 0, data);
	else
		add_to_list(new_key, new_value, data);
}

static int	is_valid_input(char *cmd)
{
	int	i;

	i = 1;
	if (cmd && (cmd[0] == '_' || ft_isalpha(cmd[0])))
	{
		while (cmd[i] && cmd[i] != '=')
		{
			if (cmd[i] == '+' && cmd[i + 1] && cmd[i + 1] == '=')
				return (1);
			if (check_special_sympols(cmd[i]))
				return (0);
			i++;
		}
	}
	else
		return (0);
	return (1);
}

void	call_export(char **cmds, t_shell *data)
{
	int	len;
	int	i;
	int	status_flag;

	i = 1;
	len = ft_strlen_2(cmds);
	status_flag = 0;
	if (len == 1)
	{
		sort_list_ao(&data->env, ft_lstsize(data->env));
		print_env(1, &data->env);
		return ;
	}
	while (cmds[i] && i < len)
	{
		if (is_valid_input(cmds[i]))
			get_export_pair(i, cmds, data);
		else
		{
			status_flag = 1;
			print_error_exec(12);
		}
		i++;
	}
	data->status_code = status_flag;
}

void	print_export(t_env_list *itr)
{
	char	*export_str;

	export_str = ft_strdup("declare -x ");
	if (export_str != NULL)
	{
		while (itr)
		{
			ft_putstr_fd(export_str, 1);
			if (itr->key)
				ft_putstr_fd(itr->key, 1);
			if (itr->value)
			{
				ft_putstr_fd("=\"", 1);
				ft_putstr_fd(itr->value, 1);
				ft_putstr_fd("\"\n", 1);
			}
			else
				ft_putchar_fd('\n', 1);
			itr = itr->next;
		}
		free(export_str);
	}
}

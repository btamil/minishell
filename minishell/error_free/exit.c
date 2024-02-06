/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabdul-k <fabdul-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 12:44:42 by tponnusa          #+#    #+#             */
/*   Updated: 2024/02/02 17:25:39 by fabdul-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_env_list(t_env_list *lst)
{
	t_env_list	*tmp;

	tmp = lst;
	while (lst)
	{
		tmp = lst->next;
		if (lst->key)
			free(lst->key);
		if (lst->value)
			free(lst->value);
		free(lst);
		lst = tmp;
	}
	free(lst);
}

void	exit_mini_shell(t_shell *data, int i)
{
	int	exit_code;

	if (!data)
		return ;
	exit_code = data->status_code;
	if (data->prompt_str)
		free(data->prompt_str);
	if (data->child_pid)
		free(data->child_pid);
	free_command(data->command);
	if (data->env)
		free_env_list(data->env);
	free(data);
	if (i == 1)
		exit(exit_code);
	else
		exit(EXIT_SUCCESS);
}

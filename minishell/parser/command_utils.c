/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabdul-k <fabdul-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 11:21:15 by fabdul-k          #+#    #+#             */
/*   Updated: 2023/11/28 07:24:55 by fabdul-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_command	*find_last(t_command *lst)
{
	t_command	*last;

	last = lst;
	if (!lst)
		return (NULL);
	while (last->next != NULL)
	{
		last = last->next;
	}
	return (last);
}

int	add_command_node(t_command **command, t_command *node)
{
	t_command	*last;

	if (!node)
		return (1);
	if (!(*command))
	{
		*command = node;
		return (0);
	}
	else
	{
		last = find_last(*command);
		last->next = node;
	}
	return (0);
}

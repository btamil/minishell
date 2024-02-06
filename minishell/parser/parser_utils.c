/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabdul-k <fabdul-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 12:13:33 by fabdul-k          #+#    #+#             */
/*   Updated: 2024/01/25 14:58:55 by fabdul-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_pipes(t_lexer *list)
{
	int		count;
	t_lexer	*temp;

	temp = list;
	count = 0;
	while (temp)
	{
		if (temp->token == PIPE)
			count++;
		temp = temp->next;
	}
	return (count);
}

int	count_args(t_lexer *list)
{
	int		count;
	t_lexer	*temp;

	temp = list;
	count = 0;
	while (temp)
	{
		if (temp->token && temp->token == PIPE)
			break ;
		else if (temp->token && temp->token != PIPE)
		{
			temp = temp->next;
			if (temp && temp->word)
				temp = temp->next;
		}
		if (temp && temp->word)
		{
			count++;
			temp = temp->next;
		}
	}
	return (count);
}

void	init_node(t_command **node)
{
	(*node)->redirection = NULL;
	(*node)->hd_file_name = NULL;
	(*node)->num_redirection = 0;
	(*node)->args = NULL;
	(*node)->next = NULL;
	return ;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabdul-k <fabdul-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:38:04 by fabdul-k          #+#    #+#             */
/*   Updated: 2023/11/06 11:38:04 by fabdul-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_redirection(t_lexer *list)
{
	int		count;
	t_lexer	*temp;

	temp = list;
	count = 0;
	while (temp)
	{
		if (temp->token && temp->token != PIPE)
			count++;
		else if (temp->token == PIPE)
			break ;
		temp = temp->next;
	}
	return (count);
}

int	add_redirection(t_lexer **list, t_lexer *temp
		, t_command **node, t_shell *shell)
{
	int	index_tok;
	int	index_arg;

	if (!add_lexernode(&((*node)->redirection),
			ft_strdup(temp->next->word), temp->token))
	{
		print_error(2);
		shell->status_code = 1;
		return (1);
	}
	index_tok = temp->index;
	index_arg = temp->next->index;
	delete_one_node(list, index_tok);
	delete_one_node(list, index_arg);
	return (0);
}

int	handle_redirection(t_lexer **list
	, t_command **node, int num_red, t_shell *shell)
{
	t_lexer	*temp;

	temp = *list;
	while (temp && temp->token == 0)
		temp = temp->next;
	if (!temp || temp->token == PIPE)
		return (0);
	if (!temp->next)
		return (print_parse_error(3, shell, list));
	if (temp->next->token)
		return (print_parse_error(2, shell, list));
	if (temp->token >= LESS && temp->token <= LESS_LESS)
		if (add_redirection(list, temp, node, shell))
			return (1);
	num_red--;
	while (num_red)
	{
		if (handle_redirection(list, node, num_red, shell))
			return (1);
		num_red--;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_clear_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabdul-k <fabdul-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 08:38:02 by fabdul-k          #+#    #+#             */
/*   Updated: 2023/11/07 08:38:02 by fabdul-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_lexer	*ft_lexerclear_one(t_lexer **lst)
{
	if ((*lst)->word)
	{
		free((*lst)->word);
		(*lst)->word = NULL;
	}
	free(*lst);
	*lst = NULL;
	return (NULL);
}

void	ft_lexerdel_first(t_lexer **lst)
{
	t_lexer	*node;

	node = *lst;
	*lst = node->next;
	ft_lexerclear_one(&node);
}

void	delete_one_node(t_lexer **lst, int key)
{
	t_lexer	*node;
	t_lexer	*prev;
	t_lexer	*start;

	start = *lst;
	node = start;
	if ((*lst)->index == key)
	{
		ft_lexerdel_first(lst);
		return ;
	}
	while (node && node->index != key)
	{
		prev = node;
		node = node->next;
	}
	if (node)
	{
		if (prev)
			prev->next = node->next;
		else
			start = node->next;
		ft_lexerclear_one(&node);
	}
	*lst = start;
}

void	ft_lexerclear(t_lexer **lst)
{
	t_lexer	*tmp;

	if (!*lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		if ((*lst)->word)
			free((*lst)->word);
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}

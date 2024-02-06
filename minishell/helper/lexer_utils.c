/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabdul-k <fabdul-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 12:52:02 by fabdul-k          #+#    #+#             */
/*   Updated: 2024/02/02 17:19:04 by fabdul-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_lexer	*lex_lstnew(char *word, t_token token)
{
	t_lexer		*new_node;
	static int	i = 0;

	new_node = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new_node)
		return (NULL);
	new_node->index = i++;
	new_node->word = word;
	new_node->token = token;
	new_node->next = NULL;
	return (new_node);
}

t_lexer	*ft_lstlast(t_lexer *lst)
{
	t_lexer	*last;

	last = lst;
	if (!lst)
		return (NULL);
	while (last->next != NULL)
	{
		last = last->next;
	}
	return (last);
}

int	lex_lstadd_back(t_lexer **list, t_lexer *new)
{
	t_lexer	*last;

	if (!new)
		return (0);
	if (*list == NULL)
	{
		*list = new;
		return (1);
	}
	else
	{
		last = ft_lstlast(*list);
		last->next = new;
	}
	return (1);
}

int	add_lexernode(t_lexer **list, char *word, t_token token)
{
	t_lexer	*new;

	new = lex_lstnew(word, token);
	if (!new)
		return (0);
	lex_lstadd_back(list, new);
	return (1);
}

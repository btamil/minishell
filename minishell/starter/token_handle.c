/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabdul-k <fabdul-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 06:53:08 by fabdul-k          #+#    #+#             */
/*   Updated: 2023/11/02 06:53:08 by fabdul-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_token(char c)
{
	int	j;
	int	token[3][2];

	token[0][0] = '|';
	token[0][1] = PIPE;
	token[1][0] = '<';
	token[1][1] = LESS;
	token[2][0] = '>';
	token[2][1] = GREAT;
	j = 0;
	while (j < 3)
	{
		if (c == token[j][0])
			return (token[j][1]);
		j++;
	}
	return (0);
}

int	handle_token(char *input, int i, t_lexer **lex)
{
	t_token	token;

	token = check_token(input[i]);
	if (token == LESS && input[i + 1] == '<')
	{
		if (!add_lexernode(lex, NULL, LESS_LESS))
			return (0);
		return (2);
	}
	if (token == GREAT && input[i + 1] == '>')
	{
		if (!add_lexernode(lex, NULL, GREAT_GREAT))
			return (0);
		return (2);
	}
	else
	{
		if (!add_lexernode(lex, NULL, token))
			return (0);
		return (1);
	}
}

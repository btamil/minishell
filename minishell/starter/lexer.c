/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabdul-k <fabdul-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 13:20:09 by fabdul-k          #+#    #+#             */
/*   Updated: 2023/11/29 14:46:30 by fabdul-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_word(char *input, int pos, t_lexer **lex)
{
	int		i;
	char	*word;

	i = pos;
	while (input[i] && !check_token(input[i]))
	{
		if (input[i] == 34)
			i = find_closing_quote(input, &i, 34);
		else if (input[i] == 39)
			i = find_closing_quote(input, &i, 39);
		if (input[i] == ' ')
			break ;
		i++;
	}
	if (i - pos)
	{
		word = ft_substr(input, pos, (i - pos));
		if (!add_lexernode(lex, word, 0))
		{
			free (word);
			return (0);
		}
	}
	return (i - pos);
}

int	init_lexer(char *args, t_lexer **lex)
{
	int		i;
	int		j;
	char	*input;

	i = 0;
	j = -1;
	input = ft_strtrim(args, " ");
	while (input[i] != '\0' && j != 0)
	{
		j = 0;
		while (input[i] == ' ' && input[i])
			i++;
		if (check_token(input[i]))
			j = handle_token(input, i, lex);
		else
			j = handle_word(input, i, lex);
		i = i + j;
	}
	free (input);
	if (j == 0)
	{
		print_error(2);
		return (1);
	}
	return (0);
}

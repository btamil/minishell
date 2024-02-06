/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabdul-k <fabdul-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 13:07:48 by fabdul-k          #+#    #+#             */
/*   Updated: 2024/02/02 17:19:27 by fabdul-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef enum s_token
{
	PIPE = 1,
	LESS,
	GREAT,
	GREAT_GREAT,
	LESS_LESS
}t_token;

typedef struct s_lexer
{
	int				index;
	char			*word;
	t_token			token;
	struct s_lexer	*next;
}t_lexer;

int		find_closing_quote(char *input, int *pos, char c);
int		check_token(char c);
int		handle_token(char *input, int i, t_lexer **lex);
int		init_lexer(char *args, t_lexer **lex);
int		add_lexernode(t_lexer **list, char *word, t_token token);

#endif

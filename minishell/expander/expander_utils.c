/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponnusa <tponnusa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 18:01:55 by fabdul-k          #+#    #+#             */
/*   Updated: 2024/01/28 18:52:51 by tponnusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	dollar_index(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (i + 1);
		i++;
	}
	return (0);
}

char	*char_to_str(char c)
{
	char	*str;

	str = ft_calloc(sizeof(char), 2);
	str[0] = c;
	return (str);
}

int	handle_question(t_shell *shell, char **tmp)
{
	char		*new;
	char		*code_str;

	code_str = ft_itoa(shell->status_code);
	new = ft_strjoin(*tmp, code_str);
	free(*tmp);
	*tmp = new;
	free (code_str);
	return (2);
}

int	check_if_not_alphnum(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]))
			return (i + 1);
		i++;
	}
	return (0);
}

int	check_enclosed(char*str, int j, int *pos)
{
	int		i;
	int		close_pos;
	char	q;

	i = *pos;
	while (i < j)
	{
		q = find_first_quote(str, &i);
		if (q == '\0' || i > j)
			return (0);
		close_pos = find_closing(str, i, q);
		if (q == '\'' && close_pos > j)
			return (1);
		if (close_pos == (int)ft_strlen(str) - 1 || close_pos == (j - 1))
			break ;
		*pos = close_pos + 1;
		i = *pos;
	}
	return (0);
}

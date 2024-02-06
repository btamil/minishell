/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabdul-k <fabdul-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 14:33:16 by fabdul-k          #+#    #+#             */
/*   Updated: 2024/02/01 20:30:52 by fabdul-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	find_closing_quote(char *input, int *pos, char c)
{
	int	i;

	i = *pos;
	i++;
	while (input[i] != c && input[i] != '\0')
		i++;
	*pos = i;
	if (input[i] == c)
		return (i);
	else
		return (0);
}

int	check_quotes(char *input, t_shell *shell_data)
{
	int	i;
	int	flag;

	i = 0;
	flag = 1;
	if (ft_strchr(input, 34) || ft_strchr(input, 39))
	{
		while (input[i] != '\0' && flag)
		{
			if (input[i] == 34)
				flag = find_closing_quote(input, &i, 34);
			if (input[i] == 39)
				flag = find_closing_quote(input, &i, 39);
			if (!flag)
				break ;
			i++;
		}
		if (!flag)
		{
			shell_data->status_code = INCORRECT_CMD_USAGE;
			return (0);
		}
	}		
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabdul-k <fabdul-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 16:56:18 by fabdul-k          #+#    #+#             */
/*   Updated: 2023/11/25 16:56:18 by fabdul-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	find_first_quote(char *str, int *pos)
{
	int	i;

	i = *pos;
	while (str[i])
	{
		*pos = i;
		if (str[i] == '\'')
			return ('\'');
		else if (str[i] == '\"')
			return ('\"');
		i++;
	}
	return ('\0');
}

int	find_closing(char *str, int start, char q)
{
	int	i;

	i = start + 1;
	while (str[i])
	{
		if (str[i] == q)
			return (i);
		i++;
	}
	return (-1);
}

char	*delete_in_between(char *str, char q, int i, int len)
{
	char	*new;
	char	*temp;
	char	*beg;
	char	*set;
	char	*tmp;

	temp = ft_substr(str, i, len);
	if (q == '\"')
		set = ft_strdup("\"");
	else
		set = ft_strdup("\'");
	new = ft_strtrim(temp, set);
	if (i != 0)
	{
		beg = ft_substr(str, 0, i);
		tmp = ft_strjoin(beg, new);
		free (new);
		new = tmp;
		free (beg);
	}
	free (set);
	free (temp);
	return (new);
}

char	*delete_and_join(char *str, char q, int *pos, int j)
{
	char	*temp;
	char	*new;
	int		i;

	i = *pos;
	new = delete_in_between(str, q, i, j - i + 1);
	temp = ft_substr(str, j + 1, (ft_strlen(str) - j));
	free (str);
	str = ft_strjoin(new, temp);
	free (temp);
	*pos = ft_strlen(new);
	free (new);
	return (str);
}

char	*delete_quote(char *str)
{
	char	q;
	int		j;
	int		i;

	i = 0;
	while (i < (int)ft_strlen(str) && str[i])
	{
		q = find_first_quote(str, &i);
		if (q != '\0')
		{
			j = find_closing(str, i, q);
			if (j > 0)
				str = delete_and_join(str, q, &i, j);
		}
		else
			break ;
	}
	return (str);
}

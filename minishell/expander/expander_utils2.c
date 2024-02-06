/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabdul-k <fabdul-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 21:47:52 by fabdul-k          #+#    #+#             */
/*   Updated: 2024/01/19 21:47:52 by fabdul-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	loop_if_dollar_sign(t_shell *shell, char *str, char **tmp, int j)
{
	int			len;
	t_env_list	*temp;
	char		*new;

	len = 0;
	temp = shell->env;
	while (temp)
	{
		if (ft_strncmp(str + j + 1, temp->key, ft_strlen(temp->key)) == 0
			&& temp->value != NULL)
		{
			if (ft_isalnum(str[j + 1 + ft_strlen(temp->key)]))
				break ;
			new = ft_strjoin(*tmp, temp->value);
			free(*tmp);
			*tmp = new;
			len = ft_strlen(temp->key) + 1;
		}
		temp = temp->next;
	}
	if (len == 0 && !check_if_not_alphnum((str + j + 1)))
		return (ft_strlen(str) - j);
	else if (len == 0 && check_if_not_alphnum(str + j + 1))
		return (check_if_not_alphnum(str + j + 1));
	return (len);
}

int	handle_if_dollar(t_shell *shell, char *str, char **tmp, int j)
{
	if (str[j] == '$' && ft_isdigit(str[j + 1]) == 1)
		j += 2;
	else if (str[j] == '$' && str[j + 1] == '?')
		j += handle_question(shell, tmp);
	else if (str[j] == '$' && (str[j + 1] != ' ' && (str[j + 1] != '"'
				|| str[j + 2] != '\0')) && str[j + 1] != '\0')
		j += loop_if_dollar_sign(shell, str, tmp, j);
	return (j);
}

char	*handle_dollar(t_shell *shell, char *str)
{
	int		j;
	char	*tmp;
	char	*new;
	char	*temp;
	int		close_pos;

	j = 0;
	close_pos = 0;
	tmp = ft_strdup("\0");
	while (str[j])
	{
		if (str[j] == '$' && !check_enclosed(str, j, &close_pos)
			&& (!check_special_sympols(str[j + 1])
				|| str[j + 1] == '?') && str[j + 1] != '\0')
			j = handle_if_dollar(shell, str, &tmp, j);
		else
		{
			new = char_to_str(str[j++]);
			temp = ft_strjoin(tmp, new);
			free(tmp);
			tmp = temp;
			free(new);
		}
	}
	return (tmp);
}

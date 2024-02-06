/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponnusa <tponnusa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:26:22 by tponnusa          #+#    #+#             */
/*   Updated: 2023/11/27 20:42:25 by tponnusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	ft_strlen_2(char **s)
{
	size_t	l;

	l = 0;
	if (!s)
		return (0);
	while (s[l])
		l++;
	return (l);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 && !s2)
		return (1);
	while (s1[i] && s2[i] && (s1[i] == s2[i]))
		i++;
	return (s1[i] - s2[i]);
}

void	ft_strcpy(char *dst, const char *src)
{
	size_t	i;

	if (!dst || !src)
		return ;
	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

int	is_present(char *s, char c)
{
	while (s && *s)
	{
		if (*s == (unsigned char)c)
			return (1);
		s++;
	}
	return (0);
}

int	get_char_count(char *s, char ch)
{
	int	c;
	int	i;

	c = 0;
	i = 0;
	while (s && s[i])
	{
		if (s[i] == (unsigned char)ch)
			c++;
		i++;
	}
	if (s[i] == '\0' && c == i)
		return (c);
	return (0);
}

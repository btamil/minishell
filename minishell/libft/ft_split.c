/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponnusa <tponnusa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 15:22:33 by tponnusa          #+#    #+#             */
/*   Updated: 2023/10/26 15:42:20 by tponnusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_get_no_of_strings(char const *s, char c)
{
	size_t	i;
	size_t	nos;

	i = 0;
	nos = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			nos++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (nos);
}

static void	ft_free(char **s, int i)
{
	while (i >= 0)
	{
		if (s[i] != NULL)
			free(s[i]);
		i--;
	}
	free(s);
}

static char	**ft_split2(char **strs, char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	start;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			start = i;
			while (s[i] && s[i] != c)
				i++;
			strs[j] = ft_substr(s, start, (i - start));
			if (!strs[j])
				ft_free(strs, j);
			j++;
		}
		else
			i++;
	}
	strs[j] = 0;
	return (strs);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	size_t	nos;

	if (!s)
		return (0);
	nos = ft_get_no_of_strings(s, c);
	if (nos == 0)
		return (0);
	strs = malloc((sizeof(char *) * (nos + 1)));
	if (!strs)
		return (0);
	ft_split2(strs, s, c);
	return (strs);
}

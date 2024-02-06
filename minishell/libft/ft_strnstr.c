/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponnusa <tponnusa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 11:30:19 by tponnusa          #+#    #+#             */
/*   Updated: 2022/11/25 13:21:32 by tponnusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	nlen;

	nlen = ft_strlen(needle);
	if (nlen == 0 || haystack == needle)
		return ((char *)haystack);
	if (len == 0)
		return ((void *)0);
	i = 0;
	while (haystack[i] != '\0')
	{
		j = 0;
		if (haystack[i] == needle[j])
		{
			while (needle[j] != '\0' && ((i + j) < len)
				&& (haystack[i + j] == needle[j]))
				j++;
			if (needle[j] == '\0')
				return ((char *)(haystack + i));
		}
		i++;
	}
	return (0);
}

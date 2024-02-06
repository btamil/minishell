/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponnusa <tponnusa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 10:29:04 by tponnusa          #+#    #+#             */
/*   Updated: 2023/10/26 13:12:17 by tponnusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	while (s && *s && (*s != (unsigned char)c))
		s++;
	if (*s == (unsigned char)c)
		return ((char *)s);
	return (0);
}

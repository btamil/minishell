/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponnusa <tponnusa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:38:13 by tponnusa          #+#    #+#             */
/*   Updated: 2022/11/25 13:21:41 by tponnusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	ch;
	int				pos;
	int				i;

	i = 0;
	pos = 0;
	ch = c;
	while (s[i])
	{
		if (s[i] == ch)
			pos = i;
		i++;
	}
	if (s[i] == ch)
		return ((char *)(s + i));
	else if (s[pos] == ch)
		return ((char *)(s + pos));
	return (0);
}

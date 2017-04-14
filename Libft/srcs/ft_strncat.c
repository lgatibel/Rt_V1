/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strncat.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgatibel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 12:35:20 by lgatibel          #+#    #+#             */
/*   Updated: 2015/12/11 12:02:43 by lgatibel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	size_t	i1;
	size_t	i2;

	i2 = 0;
	i1 = 0;
	while (s1[i1] != '\0')
		i1++;
	while (i2 < n && s2[i2])
	{
		s1[i1] = s2[i2];
		i2++;
		i1++;
	}
	s1[i1] = '\0';
	return (s1);
}
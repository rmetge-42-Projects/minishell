/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmetge <rmetge@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:00:08 by rmetge            #+#    #+#             */
/*   Updated: 2024/11/05 12:30:27 by rmetge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memset(void	*str, int val, size_t n)
{
	unsigned char	*s;
	unsigned char	v;
	size_t			i;

	s = str;
	v = (unsigned char)val;
	i = 0;
	while (i < n)
	{
		s[i] = v;
		i++;
	}
	return (str);
}

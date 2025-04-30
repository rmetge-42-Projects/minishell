/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmetge <rmetge@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 17:13:44 by rmetge            #+#    #+#             */
/*   Updated: 2024/11/08 11:54:57 by rmetge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t s)
{
	size_t	i;
	size_t	d;

	i = 0;
	d = ft_strlen(dest);
	if (s > d)
	{
		while (src[i] && d + i < s -1)
		{
			dest[d + i] = src[i];
			i++;
		}
		dest[d + i] = '\0';
	}
	if (d >= s)
		d = s;
	return (d + ft_strlen(src));
}

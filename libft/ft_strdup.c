/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmetge <rmetge@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 08:54:11 by rmetge            #+#    #+#             */
/*   Updated: 2024/11/08 11:55:19 by rmetge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strdup(const char *src)
{
	size_t	len;
	char	*dest;

	len = ft_strlen(src);
	dest = (ft_calloc(len + 1, sizeof(char)));
	if (!dest)
		return (NULL);
	dest[len] = src[len];
	while (len-- > 0)
		dest[len] = src[len];
	return (dest);
}

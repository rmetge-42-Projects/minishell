/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmetge <rmetge@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 17:55:50 by rmetge            #+#    #+#             */
/*   Updated: 2024/11/14 13:43:17 by rmetge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strchr(const char *str, int r)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == (char) r)
			break ;
		i++;
	}
	if (str[i] == (char)r)
		return ((char *)(str + i));
	return (NULL);
}

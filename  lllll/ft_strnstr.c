/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmetge <rmetge@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 09:35:39 by rmetge            #+#    #+#             */
/*   Updated: 2024/11/08 11:52:51 by rmetge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strnstr(const char	*s1, const char *s2, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!s2[0])
		return ((char *)(s1));
	while (i < len && s1[i])
	{
		j = 0;
		while ((s1[i + j] == s2[j]) && (i + j < len))
		{
			j++;
			if (s2[j] == '\0')
				return ((char *)(&s1[i]));
		}
		i++;
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmetge <rmetge@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 09:09:44 by rmetge            #+#    #+#             */
/*   Updated: 2024/11/14 13:43:29 by rmetge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int	ft_strncmp(const char	*fir, const char	*sec, size_t l)
{
	size_t	i;

	i = 0;
	while (i < l - 1 && fir[i] && sec[i])
	{
		if ((unsigned char)fir[i] != (unsigned char)sec[i])
			break ;
		i++;
	}
	if (i < l)
		return ((unsigned char)fir[i] - (unsigned char)sec[i]);
	return (0);
}

// #include "stdio.h"
// int	main(void)
// {
// 	const char	*f = "bonjonr";
// 	const char	*s = "bonjour";

// 	printf("%d\n", ft_strncmp(f, s, 7));
// }
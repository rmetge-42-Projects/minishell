/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmetge <rmetge@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:25:23 by rmetge            #+#    #+#             */
/*   Updated: 2024/11/13 15:44:01 by rmetge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memchr(const void *block, int rch, size_t s)
{
	const unsigned char	*b;
	size_t				i;

	b = (const unsigned char *)block;
	i = 0;
	while (i < s)
	{
		if (b[i] == (unsigned char)rch)
			return ((void *)(block + i));
		i++;
	}
	return (NULL);
}

// #include <stdio.h>

// int	main(void)
// {
// 	const char	*b = "gggggghhggg";
// 	int	r = 'h';
// 	printf("%s\n", (char *)ft_memchr((const void *)b, r, 50));
// }
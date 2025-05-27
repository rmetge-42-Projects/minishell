/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemma <bemma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:46:08 by rmetge            #+#    #+#             */
/*   Updated: 2025/05/27 16:57:28 by bemma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	char	*dest;
	int		j;

	i = 0;
	if (!s1)
		return (NULL);
	j = ft_strlen(s1);
	while (ft_strchr(set, s1[i]))
		i++;
	while (ft_strchr(set, s1[j]))
		j--;
	j = j + 1 - i;
	dest = ft_substr(s1, i, j);
	return (dest);
}

// #include <stdio.h>
// int	main(void)
// {
// 	char const	*s1 = "xoxxoyuedhjoxoox";
// 	char const	*set = "xo";
// 	printf("%s\n", ft_strtrim(s1, set));
// }
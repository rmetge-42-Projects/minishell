/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmetge <rmetge@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 10:28:43 by rmetge            #+#    #+#             */
/*   Updated: 2024/11/13 11:35:42 by rmetge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	lennbr(int n)
{
	int	nbr;

	nbr = 0;
	if (n < 0)
	{
		nbr = 1;
		n *= -1;
	}
	else if (n == 0)
	{
		nbr = 1;
	}
	while (n > 0)
	{
		if (n > 9)
			n = n / 10;
		else
			n = 0;
		nbr++;
	}
	return (nbr);
}

static void	ft_charnbr(char *dest, int n, int *i)
{
	if (n < 0)
	{
		dest[*i] = '-';
		n *= -1;
		(*i)++;
	}
	if (n > 9)
	{
		ft_charnbr(dest, (n / 10), i);
		ft_charnbr(dest, (n % 10), i);
	}
	else
	{
		dest[(*i)++] = n + '0';
	}
}

char	*ft_itoa(int n)
{
	char	*dest;
	int		i;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	else
	{
		dest = (char *)malloc((lennbr(n) + 1) * sizeof(char));
		if (!dest)
			return (NULL);
		i = 0;
		ft_charnbr(dest, n, &i);
		dest[i] = '\0';
	}
	return (dest);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_nbr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmetge <rmetge@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 11:00:56 by rmetge            #+#    #+#             */
/*   Updated: 2024/12/19 18:02:12 by rmetge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_nbr(int *nbr, char c)
{
	ft_putchar_fd(c, 1);
	(*nbr)++;
}

void	ft_nbrlen(int *nbr, int n)
{
	if (n == -2147483648)
	{
		ft_putnbr_fd(-2147483648, 1);
		(*nbr) += 11;
	}
	else
	{
		if (n < 0)
		{
			n *= -1;
			ft_putchar_nbr(nbr, '-');
		}
		ft_putnbr_fd(n, 1);
		while (n > 9)
		{
			n = n / 10;
			(*nbr)++;
		}
		if (n >= 0)
			(*nbr)++;
	}
}

void	ft_strlen_pf(int *nbr, char *str)
{
	if (str)
	{
		ft_putstr_fd(str, 1);
		(*nbr) += ft_strlen(str);
	}
	else
	{
		ft_strlen_pf(nbr, "(null)");
	}
}

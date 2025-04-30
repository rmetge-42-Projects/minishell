/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexaupp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmetge <rmetge@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 10:47:54 by rmetge            #+#    #+#             */
/*   Updated: 2024/12/19 18:04:19 by rmetge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_puthexaupp(int *nbr, unsigned int hex)
{
	if (hex > 15)
	{
		ft_puthexaupp(nbr, hex / 16);
		ft_puthexaupp(nbr, hex % 16);
	}
	else
	{
		if (hex < 10)
			ft_putchar_nbr(nbr, hex + '0');
		else
			ft_putchar_nbr(nbr, hex + 55);
	}
}

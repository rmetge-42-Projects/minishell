/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexalow.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmetge <rmetge@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 14:51:51 by rmetge            #+#    #+#             */
/*   Updated: 2024/12/19 18:04:12 by rmetge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_puthexalow(int *nbr, unsigned int hex)
{
	if (hex > 15)
	{
		ft_puthexalow(nbr, hex / 16);
		ft_puthexalow(nbr, hex % 16);
	}
	else
	{
		if (hex < 10)
			ft_putchar_nbr(nbr, hex + '0');
		else
			ft_putchar_nbr(nbr, hex + 87);
	}
}

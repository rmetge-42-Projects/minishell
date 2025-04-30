/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmetge <rmetge@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 09:49:33 by rmetge            #+#    #+#             */
/*   Updated: 2024/12/19 18:01:49 by rmetge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putunsigned(int *nbr, unsigned int n)
{
	if (n > 9)
	{
		ft_putunsigned(nbr, n / 10);
		ft_putunsigned(nbr, n % 10);
	}
	else
		ft_putchar_nbr(nbr, n + '0');
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmetge <rmetge@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:41:57 by rmetge            #+#    #+#             */
/*   Updated: 2024/11/08 11:53:26 by rmetge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t s)
{
	void	*a;

	if (s != 0 && nmemb * s / s != nmemb)
		return (NULL);
	a = (void *)malloc(nmemb * s);
	if (!a)
		return (NULL);
	ft_bzero(a, nmemb * s);
	return (a);
}

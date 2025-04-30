/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmetge <rmetge@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 11:35:55 by rmetge            #+#    #+#             */
/*   Updated: 2024/12/19 18:02:25 by rmetge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	process_format(int *nbr, char format, va_list args)
{
	if (format == 'c')
		ft_putchar_nbr(nbr, va_arg(args, int));
	else if (format == 's')
		ft_strlen_pf(nbr, va_arg(args, char *));
	else if (format == 'p')
		ft_puthex(nbr, (unsigned long int)va_arg(args, void *));
	else if (format == 'd' || format == 'i')
		ft_nbrlen(nbr, va_arg(args, int));
	else if (format == 'u')
		ft_putunsigned(nbr, va_arg(args, unsigned int));
	else if (format == 'x')
		ft_puthexalow(nbr, va_arg(args, unsigned int));
	else if (format == 'X')
		ft_puthexaupp(nbr, va_arg(args, unsigned int));
	else if (format == '%')
		ft_putchar_nbr(nbr, '%');
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		nbr;

	va_start(args, format);
	i = 0;
	nbr = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			process_format(&nbr, format[i], args);
		}
		else
			ft_putchar_nbr(&nbr, format[i]);
		i++;
	}
	return (nbr);
}

// int	main(void)
// {
// 	//char *N = NULL;
// 	//unsigned int u = 17;
// 	void * v = 0;
// 	//int	i = -2147483648;
// 	//ft_printf("%d", ft_printf("%p", some_var));
// 	printf("%d\n", ft_printf(" %p ", v));
// 	//printf("%d", printf("%p", some_var));
// 	printf("%d\n", printf(" %x ", v));
// }

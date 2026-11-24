/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlejamte <mlejamte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 14:58:40 by mlejamte          #+#    #+#             */
/*   Updated: 2026/01/11 15:04:06 by mlejamte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	what_to_print(va_list args, const char format)
{
	int	len_print;

	len_print = 0;
	if (format == 's')
		len_print = ft_putstring(va_arg(args, const char *));
	else if (format == 'c')
		len_print = ft_putchar(va_arg(args, int));
	else if (format == '%')
		len_print = ft_putchar('%');
	else if (format == 'x')
		len_print = ft_putnbr_b(va_arg(args, unsigned int), "0123456789abcdef");
	else if (format == 'X')
		len_print = ft_putnbr_b(va_arg(args, unsigned int), "0123456789ABCDEF");
	else if (format == 'u')
		len_print = ft_putnbr_b(va_arg(args, unsigned int), "0123456789");
	else if (format == 'p')
		len_print = ft_print_pointer(va_arg(args, unsigned long));
	else if (format == 'd' || format == 'i')
		len_print = ft_putnbr(va_arg(args, int));
	return (len_print);
}

int	ft_printf(const char *format, ...)
{
	int		len_print;
	va_list	args;

	if (!format)
		return (-1);
	va_start(args, format);
	len_print = 0;
	while (*format)
	{
		if (*format != '%')
		{
			len_print += write(1, format, 1);
			format++;
		}
		else
		{
			len_print += what_to_print(args, format[1]);
			format += 2;
		}
	}
	va_end (args);
	return (len_print);
}

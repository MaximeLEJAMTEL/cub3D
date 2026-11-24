/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlejamte <mlejamte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 17:41:11 by mlejamte          #+#    #+#             */
/*   Updated: 2026/01/11 15:04:10 by mlejamte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_pointer(size_t pnt)
{
	int	len_print;

	if (pnt == 0)
	{
		len_print = write(1, "(nil)", 5);
		return (len_print);
	}
	len_print = write(1, "0x", 2);
	len_print += ft_putnbr_b(pnt, "0123456789adcdef");
	return (len_print);
}

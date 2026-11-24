/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlejamte <mlejamte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 17:39:49 by mlejamte          #+#    #+#             */
/*   Updated: 2026/01/11 15:03:55 by mlejamte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_b(unsigned long nb, char *base)
{
	int				len_print;
	unsigned int	len_base;

	len_base = 0;
	len_print = 0;
	while (base[len_base])
		len_base++;
	if (nb > len_base - 1)
	{
		len_print += ft_putnbr_b(nb / len_base, base);
		len_print += ft_putnbr_b(nb % len_base, base);
	}
	else
		len_print += write(1, &base[nb], 1);
	return (len_print);
}

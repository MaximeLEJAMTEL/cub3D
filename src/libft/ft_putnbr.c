/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlejamte <mlejamte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 17:42:10 by mlejamte          #+#    #+#             */
/*   Updated: 2026/01/11 15:03:48 by mlejamte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr(int n)
{
	long	nb;
	int		len_print;

	nb = n;
	len_print = 0;
	if (nb < 0)
	{
		len_print += write(1, "-", 1);
		nb *= -1;
	}
	if (nb > 9)
	{
		len_print += ft_putnbr(nb / 10);
		len_print += ft_putnbr(nb % 10);
	}
	else
	{
		nb += 48;
		len_print += write(1, &nb, 1);
	}
	return (len_print);
}

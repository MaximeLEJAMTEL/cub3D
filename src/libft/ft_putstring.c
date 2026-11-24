/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstring.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlejamte <mlejamte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 17:37:58 by mlejamte          #+#    #+#             */
/*   Updated: 2026/01/11 15:03:28 by mlejamte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstring(const char *c)
{
	int	len;

	len = 0;
	if (c == NULL)
	{
		len = write(1, "(null)", 6);
		return (len);
	}
	while (c[len])
		write (1, &c[len++], 1);
	return (len);
}

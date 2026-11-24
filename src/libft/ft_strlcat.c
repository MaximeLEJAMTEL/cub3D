/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlejamte <mlejamte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 17:33:21 by mlejamte          #+#    #+#             */
/*   Updated: 2025/10/30 15:49:21 by mlejamte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	x;

	i = 0;
	j = 0;
	while (i < size && dst[i])
		i++;
	while (src[j])
		j++;
	x = i;
	if (size <= i)
		return (size + j);
	while (src[x - i] && x < size - 1)
	{
		dst[x] = src[x - i];
		x++;
	}
	dst[x] = '\0';
	return (i + j);
}

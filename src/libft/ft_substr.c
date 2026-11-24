/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlejamte <mlejamte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 18:38:05 by mlejamte          #+#    #+#             */
/*   Updated: 2025/10/30 15:55:13 by mlejamte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	size;
	char	*array;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		size = 0;
		array = malloc(sizeof(char));
		if (!array)
			return (NULL);
		*array = 0;
		return (array);
	}
	size = ft_strlen(s) - start;
	if (len < size)
		size = len;
	size++;
	array = malloc(size);
	if (!array)
		return (NULL);
	ft_strlcpy(array, s + start, size);
	return (array);
}

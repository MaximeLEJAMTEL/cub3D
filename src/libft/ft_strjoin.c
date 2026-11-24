/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlejamte <mlejamte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 18:41:30 by mlejamte          #+#    #+#             */
/*   Updated: 2025/10/30 16:06:20 by mlejamte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	y;
	char	*s3;

	i = 0;
	y = 0;
	if (!s1 || !s2)
		return (NULL);
	i = ft_strlen(s1) + ft_strlen(s2) + 1;
	s3 = malloc(i);
	if (!s3)
		return (NULL);
	while (s1[y])
	{
		s3[y] = s1[y];
		y++;
	}
	i = 0;
	while (s2[i])
	{
		s3[y + i] = s2[i];
		i++;
	}
	s3[y + i] = '\0';
	return (s3);
}

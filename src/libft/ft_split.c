/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlejamte <mlejamte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 15:18:21 by mlejamte          #+#    #+#             */
/*   Updated: 2025/10/30 17:28:43 by mlejamte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	static	count_w(char const *s, char c)
{
	size_t	i;
	size_t	cpt;

	i = 0;
	cpt = 0;
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			cpt++;
		i++;
	}
	return (cpt);
}

char static	*malloc_w(const char *s, char c)
{
	int		len;
	char	*word;
	int		i;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	word = malloc(len + 1);
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

void static	free_all(char **s, int i)
{
	while (i > 0)
	{
		i--;
		free(s[i]);
	}
	free(s);
}

char static	**cut(char const *s, char c, char **array)
{
	int		i;

	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			array[i] = malloc_w(s, c);
			if (!array[i++])
			{
				free_all(array, i);
				return (NULL);
			}
			while (*s && *s != c)
				s++;
		}
	}
	array[i] = NULL;
	return (array);
}

char	**ft_split(char const *s, char c)
{
	char	**array;

	if (!s)
		return (NULL);
	array = malloc(sizeof(char *) * (count_w(s, c) + 1));
	if (!array)
		return (NULL);
	array = cut(s, c, array);
	return (array);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakeshi <rtakeshi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 12:07:16 by rtakeshi          #+#    #+#             */
/*   Updated: 2022/01/09 22:04:27 by rtakeshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	h;
	size_t	n;
	size_t	aux;

	h = 0;
	n = ft_strlen(needle);
	if (n == 0)
		return ((char *)haystack);
	while (haystack[h] && h < len)
	{
		aux = 0;
		while ((haystack[h + aux] == needle[aux]) && ((h + aux) < len))
		{
			if (aux + 1 == n)
				return ((char *)haystack + h);
			aux++;
		}
		h++;
	}
	return (0);
}

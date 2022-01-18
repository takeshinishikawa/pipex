/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoken.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakeshi <rtakeshi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 20:32:16 by rtakeshi          #+#    #+#             */
/*   Updated: 2021/12/22 21:39:29 by rtakeshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

char	*ft_strtoken(char **str, char token)
{
	char	*piece;
	int		len;
	int		needle;
	char	*aux_str;

	if (*str == NULL || token == '\0')
		return (*str);
	len = 0;
	aux_str = *str;
	while ((aux_str[len] != token && aux_str[len]) \
	|| (aux_str[len - 1] == '\'' && aux_str[len + 1] == '\''))
		len++;
	piece = (char *)malloc(sizeof(char) * (len + 1));
	if (piece == NULL)
		return (*str);
	needle = -1;
	while (++needle < len)
		piece[needle] = aux_str[needle];
	piece[len] = '\0';
	while (aux_str[needle] == token)
		needle++;
	*str = &aux_str[needle];
	return (piece);
}

/*int	main(void)
{
	char	*str;
	char	*piece;

	str = "Este    é '  ' um teste";
	while (*str)
	{
		piece = ft_strtoken(&str, ' ');
		printf("'%s'\n", piece);
		printf("'%s'\n\n", str);
		free(piece);
	}
	return (0);
}
*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakeshi <rtakeshi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 12:06:43 by rtakeshi          #+#    #+#             */
/*   Updated: 2022/02/04 15:34:23 by rtakeshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

static void	*ft_free(char **str, size_t len)
{
	size_t	needle;

	needle = 0;
	while (needle < len)
		free(str[needle]);
	free(str);
	return (NULL);
}

static char	*ft_buildstr(const char *str, size_t len)
{
	char	*temp_str;
	size_t	needle;

	needle = 0;
	temp_str = (char *) malloc((len + 1) * sizeof(char));
	if (temp_str == NULL)
		return (NULL);
	while (needle < len)
	{
		temp_str[needle] = str[needle];
		needle++;
	}
	temp_str[needle] = '\0';
	return (temp_str);
}

static size_t	ft_wordlen(const char *str, char c)
{
	size_t	len;

	len = 0;
	while (str[len] != '\0' && str[len] != c)
		len++;
	return (len);
}

static size_t	ft_countwords(const char *str, char c)
{
	int		word;
	size_t	counter;

	word = 0;
	counter = 0;
	while (*str)
	{
		if (word == 0 && *str != c)
		{
			word = 1;
			counter++;
		}
		else if (word != 0 && *str == c)
			word = 0;
		str++;
	}
	return (counter);
}

char	**ft_split(char const *s, char c)
{
	char	**words;
	size_t	word_len;
	size_t	word_number;
	size_t	counter;

	counter = 0;
	if (s == NULL)
		return (NULL);
	word_number = ft_countwords(s, c);
	words = (char **) malloc((word_number + 1) * sizeof(char *));
	if (words == NULL)
		return (NULL);
	while (counter < word_number)
	{
		word_len = ft_wordlen(s, c);
		if (word_len)
		{
			words[counter] = ft_buildstr(s, word_len);
			if (words[counter++] == NULL)
				return (ft_free(words, counter - 1));
		}
		s += word_len + 1;
	}
	words[counter] = NULL;
	return (words);
}

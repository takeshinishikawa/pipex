/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakeshi <rtakeshi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 17:07:52 by rtakeshi          #+#    #+#             */
/*   Updated: 2022/02/05 17:07:55 by rtakeshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

int	ft_transfer_line(char **read_content, char **line)
{
	size_t	i;
	char	*aux;

	i = ft_linelen(*read_content);
	if ((*read_content)[i] == '\0')
	{
		*line = ft_strdup(*read_content);
		free(*read_content);
		*read_content = NULL;
		return (0);
	}
	*line = ft_linedup(*read_content);
	aux = ft_strdup((*read_content) + i + 1);
	free(*read_content);
	*read_content = aux;
	return (1);
}

static int	found_line(char *read_content)
{
	int	i;

	i = 0;
	if (read_content == NULL)
		return (0);
	while (read_content[i])
	{
		if (read_content[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static void	ft_cpy_content(char **read_content, char *buffer)
{
	char	*aux;

	if (!*read_content && !buffer)
		return ;
	else if (!*read_content && buffer)
		*read_content = ft_strdup(buffer);
	else
	{
		aux = ft_strjoin_gnl(*read_content, buffer);
		free(*read_content);
		*read_content = aux;
	}
	return ;
}

int	get_next_line(int fd, char **line)
{
	static char	*read_content;
	int			char_read;
	char		*buffer;

	if (line == NULL || fd < 0 || BUFFER_SIZE <= 0)
		return (-1);
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	char_read = 1;
	while (char_read > 0 && found_line(read_content) == 0)
	{
		char_read = read(fd, buffer, BUFFER_SIZE);
		if (char_read < 0)
		{
			free(buffer);
			return (-1);
		}
		buffer[char_read] = '\0';
		ft_cpy_content(&read_content, buffer);
	}
	free(buffer);
	return (ft_transfer_line(&read_content, line));
}

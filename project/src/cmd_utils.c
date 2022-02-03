/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakeshi <rtakeshi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 15:35:24 by rtakeshi          #+#    #+#             */
/*   Updated: 2022/02/03 19:35:48 by rtakeshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

size_t	get_cmd_len(char *orig_cmd)
{
	int		needle_orig;
	size_t	cmd_len;

	needle_orig = 0;
	cmd_len = 0;
	while (orig_cmd[needle_orig])
	{
		if (orig_cmd[needle_orig] == '\'')
			needle_orig++;
		if (orig_cmd[needle_orig] == '\'' && orig_cmd[needle_orig + 1] \
		== '\'')
		{
			needle_orig++;
			cmd_len++;
		}
		else if (orig_cmd[needle_orig] == '\'' && \
		orig_cmd[needle_orig + 1] != '\'')
			needle_orig++;
		else if (orig_cmd[needle_orig])
		{
			needle_orig++;
			cmd_len++;
		}
	}
	return (cmd_len);
}

void	found_token(char *orig_cmd, char **new_cmd, size_t *needle_orig, \
	size_t *needle_new)
{
	*needle_orig += 1;
	if (orig_cmd[*needle_orig] == '\'' && \
	orig_cmd[*needle_orig + 1] == '\'')
	{
		*(*new_cmd + (*needle_new)) = *(orig_cmd + (*needle_orig));
		*needle_new += 1;
		*needle_orig += 1;
	}
	while (orig_cmd[*needle_orig] != '\'')
	{
		if (orig_cmd[*needle_orig] == ' ')
			*(*new_cmd + (*needle_new)) = 1;
		else if ((orig_cmd[*needle_orig] == '\'' && \
		orig_cmd[*needle_orig + 1] != '\'') || orig_cmd[*needle_orig])
			*(*new_cmd + (*needle_new)) = *(orig_cmd + (*needle_orig));
		*needle_new += 1;
		*needle_orig += 1;
	}
	*needle_orig += 1;
}

char	*get_cmd(char *orig_cmd)
{
	size_t	needle_orig;
	size_t	needle_new;
	size_t	cmd_len;
	char	*new_cmd;

	needle_orig = 0;
	needle_new = 0;
	cmd_len = get_cmd_len(orig_cmd);
	new_cmd = malloc(sizeof(char) * (cmd_len + 1));
	while (orig_cmd[needle_orig] && needle_new != cmd_len)
	{
		if (orig_cmd[needle_orig] == '\'')
			found_token(orig_cmd, &new_cmd, &needle_orig, &needle_new);
		if (orig_cmd[needle_orig])
		{
			new_cmd[needle_new] = orig_cmd[needle_orig];
			needle_new++;
			needle_orig++;
		}
	}
	new_cmd[needle_new] = '\0';
	return (new_cmd);
}

char	**undo_token(char **cmd)
{
	int	word;
	int	needle;

	word = 0;
	while (cmd[word])
	{
		needle = 0;
		while (cmd[word][needle])
		{
			if (cmd[word][needle] == 1)
				cmd[word][needle] = ' ';
			needle++;
		}
		word++;
	}
	return (cmd);
}

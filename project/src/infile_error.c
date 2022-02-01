/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_not_found.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakeshi <rtakeshi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 01:40:32 by rtakeshi          #+#    #+#             */
/*   Updated: 2022/01/28 20:30:42 by rtakeshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	infile_error(char *str, char *envp[], int error)
{
	char	*shell;
	char	**head;

	head = envp;
	while (*envp)
	{
		if (ft_strnstr(*envp, "SHELL=", 6))
			shell = (*envp + 6);
		envp++;
	}
	ft_putstr_fd(shell, 1);
	ft_putstr_fd(": ", 1);
	ft_putstr_fd(str, 1);
	if (error == 2)
		ft_putstr_fd(": No such file or directory\n", 1);
	else if (error == 13)
		ft_putstr_fd(": Permission denied\n", 1);
	envp = head;
}

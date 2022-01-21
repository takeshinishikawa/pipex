/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_not_found.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakeshi <rtakeshi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 01:40:32 by rtakeshi          #+#    #+#             */
/*   Updated: 2022/01/20 16:15:26 by rtakeshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	file_not_found(char *str, char *envp[])
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
	ft_putstr_fd(": No such file or directory\n", 1);
	envp = head;
}

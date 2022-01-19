/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_not_found.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakeshi <rtakeshi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 01:40:32 by rtakeshi          #+#    #+#             */
/*   Updated: 2022/01/19 14:30:35 by rtakeshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	cmd_not_found(char *str, char *envp[])
{
	char	*shell;

	while (*envp)
	{
		if (ft_strnstr(*envp, "SHELL=", 6))
			shell = (*envp + 6);
		envp++;
	}
	ft_putstr_fd(shell, 1);
	ft_putstr_fd(": ", 1);
	ft_putstr_fd(str, 1);
	ft_putstr_fd(": command not found\n", 1);
}

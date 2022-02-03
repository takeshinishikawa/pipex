/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permission_denied.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakeshi <rtakeshi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 01:40:32 by rtakeshi          #+#    #+#             */
/*   Updated: 2022/02/01 14:42:47 by rtakeshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	permission_denied(char *str, char *envp[])
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
	ft_putstr_fd(": Permission denied\n", 1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakeshi <rtakeshi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 21:06:02 by rtakeshi          #+#    #+#             */
/*   Updated: 2022/02/04 14:30:39 by rtakeshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

/**
**Program must have at least the following config
**./pipex infile "cmd1" "cmd2" outfile
**which would be argc == 5
*/
int	check_argc(int argc)
{
	if (argc != 5)
	{
		errno = EINVAL;
		perror("Error");
		ft_putstr_fd("Pipex needs at least four arguments.\n", 1);
		ft_putstr_fd("The correct pipex usage is \
		\"./pipex infile \"cmd1\" \"cmd2\" outfile\".\n", 1);
		return (errno);
	}
	return (0);
}

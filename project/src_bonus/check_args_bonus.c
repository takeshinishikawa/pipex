/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakeshi <rtakeshi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 21:06:02 by rtakeshi          #+#    #+#             */
/*   Updated: 2022/02/05 19:43:46 by rtakeshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

/**
**Program must have at least the following config
**./pipex infile "cmd1" "cmd2" outfile
**which would be argc == 5
*/
int	check_argc(int argc, t_pipex *pipex)
{
	if (!pipex->here_doc && argc < 5)
	{
		errno = EINVAL;
		perror("Error");
		ft_putstr_fd("Pipex needs at least four arguments.\n", 1);
		ft_putstr_fd("The correct pipex usage is \
		\"./pipex infile \"cmd1\" \"cmd2\" outfile\".\n", 1);
	}
	else if (pipex->here_doc && argc < 6)
	{
		errno = EINVAL;
		perror("Error");
		ft_putstr_fd("Pipex needs at least five arguments.\n", 1);
		ft_putstr_fd("The correct pipex usage is \
		\"./pipex here_doc LIMITER \"cmd1\" \"cmd2\" outfile\".\n", 1);
	}
	return (errno);
}

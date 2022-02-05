/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakeshi <rtakeshi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 21:47:06 by rtakeshi          #+#    #+#             */
/*   Updated: 2022/02/05 19:47:22 by rtakeshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

/**
 * @Just the main calls
 *
 * @param argc at least 5
 * @param argv 0-program_name, 1-infile, 2-cmd1, 3-cmd2 and 4-outfile
 * @param envp environment variables
 * @return int 0 if ended and 1 if error
 */
int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;

	pipex.here_doc = 0;
	if (argc > 1)
	{
		if (!ft_strncmp(argv[1], "here_doc", 9))
			pipex.here_doc = 1;
	}
	if (check_argc(argc, &pipex))
		exit (EXIT_FAILURE);
	init_pipex(argc, argv, envp, &pipex);
	return (exec_pipex(&pipex, argv));
}

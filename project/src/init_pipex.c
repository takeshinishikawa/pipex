/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakeshi <rtakeshi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 19:06:29 by rtakeshi          #+#    #+#             */
/*   Updated: 2022/01/27 15:35:07 by rtakeshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

/**
 * @initiate function data structure
 *
 * @param argc given by the user in program execution
 * @param argv[0]: program name
 * @param argv[1]: infile location/name
 * @param argv[2 ~ (argc - 2)]: commands
 * @param argv[argc - 1]: outfile location/name
 * @param envp environment variable -> must get PATH and test with all commands
 * @param pipex data structure that is used to run the program
 * @return int status of the program ran
 */
void	init_pipex(int argc, char *argv[], char *envp[], t_pipex *pipex)
{
	pipex->infile = argv[1];
	pipex->outfile = argv[argc - 1];
	pipex->cmd_qty = argc - 3;
	pipex->offset = 2;
	pipex->cmd_lst = NULL;
	pipex->paths = NULL;
	pipex->envp = envp;
	pipex->previous_fd = 0;
}

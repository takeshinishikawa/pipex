/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakeshi <rtakeshi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 21:06:02 by rtakeshi          #+#    #+#             */
/*   Updated: 2022/01/17 19:04:12 by rtakeshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

/**
 * Check if the infile do exist and if it can be read
 * to proceed with the program execution.
 */

static int	check_infile(char *file)
{
	if (access(file, R_OK) != 0)
	{
		perror("Error");
		return (errno);
	}
	return (0);
}

/**
**Program must have at least the following config
**./pipex infile "cmd1" "cmd2" outfile
**which would be argc == 5
*/
static int	check_argc(int argc)
{
	if (argc < 5)
	{
		errno = EINVAL;
		perror("Error");
		printf("Pipex needs at least four arguments.\n");
		printf("The correct pipex usage is \
		\"./pipex infile \"cmd1\" \"cmd2\" outfile\".\n");
		return (errno);
	}
	return (0);
}

/**
 * Program name must be pipex
 * So, the exec is "/pipex"
 */
static int	check_name(char *argv)
{
	int	strlen;

	strlen = ft_strlen(argv);
	if (ft_strncmp(argv, PROGRAM_NAME, strlen))
	{
		errno = ENOEXEC;
		perror("Error");
		printf("Program name is incorrect.\n");
		return (1);
	}
	return (0);
}

int	check_args(int argc, char *argv[])
{
	int	i;

	i = 0;
	if (check_argc(argc) != 0)
		return (1);
	if (check_name(argv[i++]) != 0)
		return (1);
	if (check_infile(argv[i]) != 0)
		return (1);
	return (0);
}

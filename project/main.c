/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakeshi <rtakeshi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 21:47:06 by rtakeshi          #+#    #+#             */
/*   Updated: 2022/01/31 16:50:06 by rtakeshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/pipex.h"

/*int	flags_number(char *cmd, char token)
{
	int		len;
	int		flags;

	if (cmd == NULL || token == '\0')
		return (*cmd);
	len = 0;
	flags = 0;
	while (cmd[len])
	{
		printf("letter is %c\n", cmd[len]);
		if (cmd[len] == token && (cmd[len + 1] != '\'' && \
		cmd[len - 1] != '\'' && (cmd[len + 1] != token && \
		cmd[len + 1] != '\0')))
			flags++;
		len++;
	}
	printf("\n\nflags = %d\n\n", flags);
	return (flags);
}*/

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

	if (check_argc(argc))
		exit (EXIT_FAILURE);
	init_pipex(argc, argv, envp, &pipex);
	/*if (exec_pipex(&pipex, argv))
	{
		//free_cmd_lst(&pipex);
		if (pipex.outfile_fd == -1 || pipex.infile_fd == -1)
			return (1);
		exit (pipex.exec_status);
	}
	if (pipex.outfile_fd == -1)
		return (1);
	//free_cmd_lst(&pipex);
	return (pipex.exec_status);*/
	return (exec_pipex(&pipex, argv));
}

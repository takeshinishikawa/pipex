/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipex_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakeshi <rtakeshi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 18:59:41 by rtakeshi          #+#    #+#             */
/*   Updated: 2022/02/03 18:13:36 by rtakeshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	get_read_fd(t_pipex *pipex, int fd_read, int cmd_counter)
{
	if (cmd_counter == 0)
	{
		if (dup2(pipex->infile_fd, STDIN_FILENO) == -1)
		{
			if (pipex->cmd_lst)
				free_cmd_lst(pipex);
			free_paths(pipex);
			return (errno);
		}
		close(pipex->infile_fd);
		close (fd_read);
	}
	else
	{
		if (dup2(pipex->previous_fd, STDIN_FILENO) == -1)
		{
			perror("Error");
			return (errno);
		}
		close(pipex->previous_fd);
		close (fd_read);
	}
	return (0);
}

int	get_write_fd(t_pipex *pipex, int fd_write, int cmd_counter)
{
	if (cmd_counter == (pipex->cmd_qty - 1))
	{
		if (dup2(pipex->outfile_fd, 1) == -1)
		{
			perror("error");
			return (errno);
		}
		close(pipex->outfile_fd);
	}
	else if (!access(pipex->cmd_lst->cmd_file, X_OK))
	{
		if (dup2(fd_write, 1) == -1)
		{
			perror("error");
			return (errno);
		}
		close(fd_write);
	}
	return (0);
}

int	clean_child_process(t_pipex *pipex, int errnumber)
{
	int	exit_code;

	exit_code = 0;
	if (errnumber == 2)
	{
		cmd_not_found(pipex->cmd_lst->content[0], pipex->envp);
		exit_code = 127;
	}
	else if (errnumber == 13)
	{
		permission_denied(pipex->cmd_lst->content[0], pipex->envp);
		exit_code = 126;
	}
	else
		perror("error");
	if (pipex->cmd_lst)
		free_cmd_lst(pipex);
	free_paths(pipex);
	exit (exit_code);
}

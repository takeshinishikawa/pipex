/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipex_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakeshi <rtakeshi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 18:59:41 by rtakeshi          #+#    #+#             */
/*   Updated: 2022/02/05 17:08:23 by rtakeshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

/**
 * @brief execute the child process considering as input
 * 			- INFILE if p_fd == 0;
 * 			- fd[0] from the previous pipe if != 0;
 *
 * @param pipex: source of infile/outfile fds and cmd_lst
 * @param fd_read: pipefd[0] from pipe()
 * @param fd_write: pipefd[1] from pipe()
 * @param p_fd pipefd[0] from previous forked process or 0 if first execution
 * @return int
 */
int	child_process(t_pipex *pipex, int fd_read, int fd_write, int cmd_counter)
{
	if (!access(pipex->cmd_lst->cmd_file, F_OK))
	{
		if (get_read_fd(pipex, fd_read, cmd_counter))
			return (errno);
		if (get_write_fd(pipex, fd_write, cmd_counter))
			return (errno);
	}
	else
		close (fd_read);
	if (execve(pipex->cmd_lst->cmd_file, pipex->cmd_lst->content, \
	pipex->envp) == -1)
		return (clean_child_process(pipex, errno));
	return (0);
}

int	exec_cmd(t_pipex *pipex, int cmd_counter)
{
	int		fd[2];
	pid_t	pid;
	int		w_status;

	w_status = 0;
	if (get_exec_fd(fd))
		return (errno);
	get_previous_fd(pipex, fd);
	if (get_pid(&pid))
		return (errno);
	if (!pid)
		child_process(pipex, fd[0], fd[1], cmd_counter);
	else
	{
		if (cmd_counter == pipex->cmd_qty - 1)
			waitpid(pid, &w_status, 0);
		close(fd[1]);
		w_status = check_exit(w_status);
	}
	return (w_status);
}

/**
 * @brief In first iteration reads from infile and recalls itself until the
 * last cmd, when the output is set to the outfile
 *
 * @param pipex: source of the infile/outfile fds and cmd_lst
 * @param p_fd: 0 at the first iteration and fd[0] of the current process on
 * others
 * @return int: 0 if completed successfully and errno if any error found
 */
int	exec_pipex(t_pipex *pipex, char *argv[])
{
	int		cmd_counter;
	int		exec_status;
	t_list	*head;

	get_fd(pipex);
	pipex->cmd_lst = get_cmd_lst(argv, pipex->offset, pipex->cmd_qty);
	cmd_counter = 0;
	while (pipex->cmd_lst)
	{
		head = pipex->cmd_lst;
		exec_status = 0;
		get_path(pipex, pipex->cmd_lst, pipex->envp);
		exec_status = exec_cmd(pipex, cmd_counter);
		pipex->cmd_lst = pipex->cmd_lst->next;
		free_prev_cmd(head);
		head = NULL;
		cmd_counter++;
	}
	close (pipex->infile_fd);
	close (pipex->outfile_fd);
	if (access(pipex->outfile, W_OK))
		exit (EXIT_FAILURE);
	if (exec_status)
		exit (exec_status);
	return (0);
}

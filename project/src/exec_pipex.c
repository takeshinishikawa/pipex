/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakeshi <rtakeshi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 18:59:41 by rtakeshi          #+#    #+#             */
/*   Updated: 2022/01/27 00:31:52 by rtakeshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	get_read_fd(t_pipex *pipex, int fd_read, int cmd_counter)
{
	//if (cmd_counter == 0  && pipex->infile_fd != -1)
	if (cmd_counter == 0)
	{
		if (dup2(pipex->infile_fd, 0) == -1)
		{
			perror("Error");
			return (errno);
		}
		close(fd_read);
		close(pipex->infile_fd);
	}
	/*else if (!cmd_counter && pipex->infile_fd == -1)
	{
		if (dup2(-1, 0) == -1)
		{
			perror("Error");
			return (errno);
		}
		close(fd_read);
	}*/
	else
	{
		if (dup2(pipex->previous_fd, 0) == -1)
		{
			perror("Error");
			return (errno);
		}
		close(fd_read);
	}
	return (0);
}

int	get_write_fd(t_pipex *pipex, int fd_write, int cmd_counter)
{
	if (cmd_counter == (pipex->cmd_qty - 1))
	{
		if (dup2(pipex->outfile_fd, 1) == -1)
		{
			perror("Error");
			return (errno);
		}
		close(pipex->outfile_fd);
	}
	else
	{
		if (dup2(fd_write, 1) == -1)
		{
			perror("Error");
			return (errno);
		}
		close(fd_write);
	}
	return (0);
}

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
	//t_list	*head;

	//head = pipex->cmd_lst;
	if (get_read_fd(pipex, fd_read, cmd_counter))
		//return (errno);
	if (get_write_fd(pipex, fd_write, cmd_counter))
		//return (errno);
	if (execve(pipex->cmd_lst->cmd_file, pipex->cmd_lst->content, \
	pipex->envp) == -1)
	{
		//pipex->cmd_lst = pipex->cmd_lst->next;
		//free_prev_cmd(head);
		exit(127);
	}
	return (errno);
}

int	exec_cmd(t_pipex *pipex, int cmd_counter)
{
	int		fd[2];
	pid_t	pid;
	int		w_status;
	t_list	*head;

	if (get_exec_fd(fd))
		return (errno);
	get_previous_fd(pipex, fd);
	if (get_pid(&pid))
		return (errno);
	if (!pid)
	{
		/*if (child_process(pipex, fd[0], fd[1], cmd_counter))
			return (errno);*/
		child_process(pipex, fd[0], fd[1], cmd_counter);
		//free_prev_cmd(pipex->cmd_lst);
	}
	else
	{
		waitpid(pid, &w_status, WNOHANG);
		close(fd[1]);
		w_status = check_exit(w_status);
		if (!w_status)
		{
			head = pipex->cmd_lst;
			pipex->cmd_lst = pipex->cmd_lst->next;
			free_prev_cmd(head);
		}
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
	//t_list	*head;

	pipex->exec_status = get_fd(pipex);
	pipex->cmd_lst = get_cmd_lst(argv, pipex->offset, pipex->cmd_qty);

	cmd_counter = 0;
	exec_status = 0;
	while (pipex->cmd_lst)
	{
		//head = pipex->cmd_lst;
		exec_status = 0;
		get_path(pipex, pipex->cmd_lst, pipex->envp);
		exec_status = exec_cmd(pipex, cmd_counter);
		if (exec_status && (cmd_counter == pipex->cmd_qty - 1))
		{
			cmd_not_found(pipex->cmd_lst->content[0], pipex->envp);
			pipex->exec_status = exec_status;
			exec_status = 0;
		}
		//pipex->cmd_lst = pipex->cmd_lst->next;
		//free_prev_cmd(head);
		cmd_counter++;
	}
	//return (pipex->exec_status);
	return (exec_status);
}

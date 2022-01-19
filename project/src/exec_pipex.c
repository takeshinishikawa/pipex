/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakeshi <rtakeshi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 18:59:41 by rtakeshi          #+#    #+#             */
/*   Updated: 2022/01/19 15:26:55 by rtakeshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

/**
 * @brief free the cmd_lst variable already executed by child process
 *
 * @param pipex used to get the current cmd_lst and free it
 */
void	free_prev_cmd(t_pipex *pipex)
{
	t_list	*head;
	int		i;

	head = pipex->cmd_lst;
	pipex->cmd_lst = pipex->cmd_lst->next;
	i = 0;
	if (head->cmd_file)
		free(head->cmd_file);
	while (head->content[i])
	{
		free(head->content[i]);
		i++;
	}
	free(head->content);
	free(head);
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
int	child_process(t_pipex *pipex, int fd_read, int fd_write, int p_fd)
{
	if (dup2(fd_write, 1) == -1)
		return (errno);
	close(fd_write);
	if (p_fd == 0)
	{
		if (dup2(pipex->infile_fd, 0) == -1)
			return (errno);
		close(pipex->infile_fd);
	}
	else
	{
		if (dup2(p_fd, fd_read) == -1)
			return (errno);
		close(p_fd);
	}
	if (execve(pipex->cmd_lst->cmd_file, pipex->cmd_lst->content, \
	pipex->envp) == -1)
	{
		perror("Error");
		return (errno);
	}
	return (errno);
}

/**
 * @brief free process executed by child process and:
 * 			- if next cmd_lst->next != NULL function recalls itself in recursion
 * considering as INPUT the current pipefd[0];
 * 			- if cmd_lst->next == NULL (currrent cmd_lst is thelast command
 * in the list) the OUTPUT is changed to the outfile_fd;
 *
 * @param pipex: source of the cmd_lst and outfile_fd
 * @param fd_read: pipefd[0] of the current process
 * @param fd_write pipefd[1] of the current process
 * @return int: 0 if sucess, and errno if error
 */
int	parent_process(t_pipex *pipex, int fd_read, int fd_write)
{
	if (dup2(fd_read, 0) == -1)
		return (errno);
	close(fd_read);
	if (pipex->cmd_lst->next)
	{
		close(fd_write);
		exec_pipex(pipex, fd_read);
	}
	if (dup2(pipex->outfile_fd, 1) == -1)
		return (errno);
	close(pipex->outfile_fd);
	close(fd_write);
	if (execve(pipex->cmd_lst->cmd_file, pipex->cmd_lst->content, \
	pipex->envp) == -1)
	{
		perror("Error");
		return (errno);
	}
	return (errno);
}

/**
 * @brief Get the fd and pid object, and also tests for failure
 *
 * @param fd: calling process pipefds
 * @param pid: calling process pids (child and parent)
 * @return int: 0 if success and errno if failure
 */
int	get_fd_and_pid(int *fd, pid_t *pid)
{
	if (pipe(fd) == -1)
	{
		perror("Error");
		return (errno);
	}
	*pid = fork();
	if (*pid == -1)
	{
		perror("Error");
		return (errno);
	}
	return (0);
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
int	exec_pipex(t_pipex *pipex, int p_fd)
{
	pid_t	pid;
	int		fd[2];
	int		w_status;

	if (get_fd_and_pid(fd, &pid))
		return (errno);
	while (pipex->cmd_lst)
	{
		if (!pid)
		{
			if (child_process(pipex, fd[0], fd[1], p_fd))
				return (errno);
		}
		else
		{
			waitpid(pid, &w_status, WNOHANG);
			free_prev_cmd(pipex);
			if (parent_process(pipex, fd[0], fd[1]))
				return (errno);
		}
	}
	return (errno);
}

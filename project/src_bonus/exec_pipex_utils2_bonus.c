/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipex_utils2_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakeshi <rtakeshi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 18:59:41 by rtakeshi          #+#    #+#             */
/*   Updated: 2022/02/05 17:07:09 by rtakeshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

int	cmd_fd(t_pipex *pipex, int fd_read, int cmd_counter)
{
	if (cmd_counter)
	{
		if (dup2(pipex->previous_fd, STDIN_FILENO) == -1)
		{
			perror("Error");
			return (errno);
		}
		close(pipex->previous_fd);
		close (fd_read);
	}
	else if (dup2(pipex->infile_fd, STDIN_FILENO) == -1)
	{
		if (pipex->cmd_lst)
			free_cmd_lst(pipex);
		free_paths(pipex);
		return (errno);
	}
	close(pipex->infile_fd);
	close (fd_read);
	return (0);
}

int	first_cmd(t_pipex *pipex, int fd_read, int cmd_counter)
{
	int		here_doc_fd[2];
	char	*content;

	if (get_exec_fd(here_doc_fd))
		return (errno);
	pipex->infile_fd = here_doc_fd[0];
	while (pipex->here_doc)
	{
		ft_putstr_fd("> ", 1);
		get_next_line(STDIN_FILENO, &content);
		if (!ft_strncmp(content, pipex->limiter, ft_strlen(pipex->limiter)) \
		&& content[ft_strlen(pipex->limiter)] == '\0')
			break ;
		ft_putstr_fd(content, here_doc_fd[1]);
		ft_putstr_fd("\n", here_doc_fd[1]);
		free(content);
	}
	if (content)
		free(content);
	content = NULL;
	close(here_doc_fd[1]);
	return (cmd_fd(pipex, fd_read, cmd_counter));
}

int	get_read_fd(t_pipex *pipex, int fd_read, int cmd_counter)
{
	if (cmd_counter == 0 && !pipex->here_doc)
		return (cmd_fd(pipex, fd_read, cmd_counter));
	else if (cmd_counter == 0 && pipex->here_doc)
		return (first_cmd(pipex, fd_read, cmd_counter));
	else
		return (cmd_fd(pipex, fd_read, cmd_counter));
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

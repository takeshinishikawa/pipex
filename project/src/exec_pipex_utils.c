/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipex_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakeshi <rtakeshi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 18:59:41 by rtakeshi          #+#    #+#             */
/*   Updated: 2022/01/21 19:36:59 by rtakeshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

/**
 * @brief free the cmd_lst variable already executed by child process
 *
 * @param pipex used to get the current cmd_lst and free it
 */
/*void	free_prev_cmd(t_pipex *pipex)
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
}*/
void	free_prev_cmd(t_list *cmd)
{
	int		i;

	i = 0;
	if (cmd->cmd_file != cmd->content[0])
		free(cmd->cmd_file);
	while (cmd->content[i])
	{
		free(cmd->content[i]);
		i++;
	}
	free(cmd->content);
	free(cmd);
}

/**
 * @brief Get the fd and pid object, and also tests for failure
 *
 * @param fd: calling process pipefds
 * @param pid: calling process pids (child and parent)
 * @return int: 0 if success and errno if failure
 */
int	get_exec_fd(int *fd)
{
	if (pipe(fd) == -1)
	{
		perror("Error");
		return (errno);
	}
	return (0);
}

int	get_pid(int *pid)
{
	*pid = fork();
	if (*pid == -1)
	{
		perror("Error");
		return (errno);
	}
	return (0);
}

void	get_previous_fd(t_pipex *pipex, int *fd)
{
	if (!pipex->previous_fd)
		pipex->previous_fd = fd[0];
	else
		pipex->previous_fd = fd[0] - 1;
}

int	check_exit(int w_status)
{
	if (WIFEXITED(w_status))
	{
		w_status = WEXITSTATUS(w_status);
		if (w_status)
			return (w_status);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipex_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakeshi <rtakeshi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 18:59:41 by rtakeshi          #+#    #+#             */
/*   Updated: 2022/01/31 23:20:53 by rtakeshi         ###   ########.fr       */
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
	if (cmd == NULL)
		return ;
	if (cmd->cmd_file != cmd->content[0])
	{
		free(cmd->cmd_file);
		cmd->cmd_file = NULL;
	}
	while (cmd->content[i])
	{
		free(cmd->content[i]);
		cmd->content[i] = NULL;
		i++;
	}
	free(cmd->content);
	cmd->content = NULL;
	free(cmd);
	cmd = NULL;
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

int	get_pid(pid_t *pid)
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
	int	exit_status;

	exit_status = 0;
	if (w_status == -1)
	{
		perror("waitipid");
		return (EXIT_FAILURE);
	}
	//printf("\nw_status = %d\n", w_status);
	if (WIFEXITED(w_status))
	{
		exit_status = WEXITSTATUS(w_status);
		//printf("\nexit_status = %d\n", exit_status);
		if (exit_status)
			return (exit_status);
	}
	return (EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakeshi <rtakeshi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 21:47:06 by rtakeshi          #+#    #+#             */
/*   Updated: 2022/01/17 01:26:56 by rtakeshi         ###   ########.fr       */
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
int	init_pipex(int argc, char *argv[], char *envp[], t_pipex *pipex)
{
	pipex->infile = argv[1];
	pipex->outfile = argv[argc - 1];
	pipex->cmd_qty = argc - 3;
	pipex->exec_cmd = 0;
	pipex->offset = 2;
	pipex->cmd_lst = NULL;
	pipex->paths = NULL;
	if (get_fd(pipex))
		return (errno);
	pipex->cmd_lst = get_cmd_lst(argv, pipex->offset, pipex->cmd_qty);
	if (get_path(pipex, envp))
		return (errno);
	return (0);
}

/*void	child_process(t_pipex *pipex, int *write_fd)
{
	//child process
	printf("\n\nChild process\n");
	printf("Ainda não mudou o stdout\n");
	printf("pipefd write é %d\n", *write_fd);
	dup2(*write_fd, 1);
	close(*write_fd);
	execve(pipex->cmd_lst->cmd_file, pipex->cmd_lst->content, NULL);
}

void	parent_process(t_pipex *pipex, int *read_fd)
{
	//int	waitstatus;
	t_list	*head;
	int	i;
	int	pid;

	pid = fork();
	printf("\n\nParent process\n");
	if (!pid)
	{
		dup2(*read_fd, 0);
		close(*read_fd);
		printf("Read_fd is %d\n\n", *read_fd);
		printf("outfile_fd is %d\n\n", pipex->outfile_fd);
		dup2(pipex->outfile_fd, 1);
		//close(pipex->outfile_fd);
		head = pipex->cmd_lst;
		pipex->cmd_lst = pipex->cmd_lst->next;
		//free cmd executed by child process
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
		execve(pipex->cmd_lst->cmd_file, pipex->cmd_lst->content, NULL);
	}
	else
	{
		wait(NULL);
		//dup2(*read_fd, 0);
		//close(*read_fd);
	}
	if (waitstatus)
	{
		perror("Error");
		printf("\nWait status: %d\n", waitstatus);
		//return (errno);
	}
}


int	exec_pipex(t_pipex *pipex)
{
	int	pid;
	int	pipefd[2];
	//int	waitstatus;

	pid = fork();
	if (pid == -1)
	{
		perror("Error");
		return (errno);
	}
	if (pipe(pipefd))
	{
		perror("Error");
		return (errno);
	}
	printf("\npipefd read é %d\n", pipefd[0]);
	printf("pipefd write é %d\n", pipefd[1]);


	if (pid == 0)
	{
		close(pipefd[0]);
		child_process(pipex, &pipefd[1]);
	}
	else
	{
		//parent process
		wait(NULL);
		if (waitstatus)
		{
			perror("Error");
			printf("\nWait status: %d\n", waitstatus);
			return (errno);
		}
		close(pipefd[1]);
		parent_process(pipex, &pipefd[0]);
		close(pipefd[0]);
		printf("Cheguei aqui\n");
	}
	return (0);
}*/

//works for 2 cmds
int	exec_pipex(t_pipex *pipex)
{
	pid_t	pid;
	int		fd[2];
	t_list	*head;
	int		i;
	int		w_status;
	//fd[0] -> read
	//fd[1] -> write

	if (pipe(fd) == -1)
	{
		perror("Error");
		return (errno);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("Error");
		return (errno);
	}
	while(pipex->cmd_lst)
	{

		if (!pid)
		{
			dup2(fd[1], 1);
			close(fd[1]);
			dup2(pipex->infile_fd, 0);
			close(pipex->infile_fd);
			execve(pipex->cmd_lst->cmd_file, pipex->cmd_lst->content, NULL);
		}
		else
		{
			waitpid(pid, &w_status, WNOHANG);
			close(fd[1]);
			dup2(fd[0], 0);
			close(fd[0]);
			dup2(pipex->outfile_fd, 1);
			close(pipex->outfile_fd);
			head = pipex->cmd_lst;
			pipex->cmd_lst = pipex->cmd_lst->next;
			//free cmd executed by child process
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
			execve(pipex->cmd_lst->cmd_file, pipex->cmd_lst->content, NULL);
		}
	}
	return (0);
}

/*int	exec_pipex(t_pipex *pipex, int cmd_qty)
{
	pid_t	pid;
	int		fd[2];
	t_list	*head;
	int		i;
	int		w_status;
	//fd[0] -> read
	//fd[1] -> write

	pipe(fd);
	pid = fork();
	if (!pid)
	{
		close(fd[0]);
		pipex->exec_cmd++;
		if (pipex->exec_cmd != pipex->cmd_qty)
			exec_pipex(pipex, pipex->exec_cmd);
	}
	else
	{
		waitpid(pid, &w_status, WNOHANG);
		if (cmd_qty == 1)
		{
			dup2(pipex->outfile_fd, 1);
			close(pipex->outfile_fd);
			//dup2(fd[1], 1);
			//close (fd[1]);
		}
		else if (cmd_qty == pipex->cmd_qty)
		{
			close(fd[0]);
			dup2(pipex->infile_fd, 0);
			close(pipex->infile_fd);
			execve(pipex->cmd_lst->cmd_file, pipex->cmd_lst->content, NULL);
		}
		else
		{
			dup2(fd[0], 0);
			close(fd[0]);
			dup2(fd[1], 1);
			close(fd[1]);
		}
		head = pipex->cmd_lst;
		pipex->cmd_lst = pipex->cmd_lst->next;
		//free cmd executed by child process
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
		execve(pipex->cmd_lst->cmd_file, pipex->cmd_lst->content, NULL);
	}
	return (0);
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

	if (check_args(argc, argv))
		return (1);
	if (init_pipex(argc, argv, envp, &pipex))
	{
		free_paths(&pipex);
		free_cmd_lst(&pipex);
		return (1);
	}
	if (exec_pipex(&pipex))
	//if (exec_pipex(&pipex, pipex.cmd_qty))
	{
		free_paths(&pipex);
		free_cmd_lst(&pipex);
		return (errno);
	}

	free_paths(&pipex);
	free_cmd_lst(&pipex);

	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakeshi <rtakeshi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 21:47:06 by rtakeshi          #+#    #+#             */
/*   Updated: 2021/12/22 22:02:54 by rtakeshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> //tirar printf e incluid libc
#include <unistd.h> //execve
#include <time.h> //verificar se eh necessario
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include "./inc/pipex.h"

int	flags_number(char *cmd, char token)
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
}

int	init_pipex(int argc, char *argv[], t_argv *pipex)
{
	int		cmd;
	size_t	list_n;
	size_t	arg;

	pipex->commands = (char *)(sizeof(char *) * (argc - 3));
	if (pipex->commands == NULL)
	{
		printf("deu ruim\n");//ajustar o perror
		return (1);//verificar o codigo correto
	}
	if (!argv[0])
		printf("sem argv0"); //retirar essa checagem
	flags_number(argv[2], ' ');
	cmd = 0;
	while (cmd < (argc - 2))
	{
		list_n = 0;
		arg = 0;
		list_n = flags_number(argv[cmd + 2], ' ');
		pipex->commands[cmd] = malloc(sizeof(char *) * (list_n + 2));
		while (*argv[cmd + 2])
		{
			pipex->commands[cmd][arg] = ft_strtoken(&argv[cmd + 2], ' ');
			printf("'%s'\n", pipex->commands[cmd][arg]);
			printf("'%s'\n\n", argv[cmd + 2]);
			//free(piece);
		}
		cmd++;
	}
	return (0);
}



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
	t_argv	pipex;

	if (check_args(argc, argv))
		return (1);
	if (init_pipex(argc, argv, &pipex))
		return (1);
	int i;

	i = -1;
	while (envp[++i] != NULL)
		//printf("%s\n", envp[i]);

	/*
	int	pipefd[2];
	int	i;		close(pipefd[0]);
		write(fd[1], result, sizeof(result));
		close(fd[1]);

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (1);
	}
	i = 0;
	while (i < argc)
	{
		printf("%s\n", argv[i]);
		i++;
	}



	pid_t	pid;
	if ((pid = fork() < 0))
	{
		perror(fork);
		return (2);
	}
	if (pid == 0)
	{
		//Child process to execute the first command and write fd[1]
		close(pipefd[0]);
		write(fd[1], result, sizeof(result));
		close(fd[1]);

	}
	else (pid > 0)
	{
		//Parent process to read fd[0]
		close(pipefd[1]);
		read(fd[0], result, sizeof(result));
		close(fd[0]);
	}

*/


	return (0);
}

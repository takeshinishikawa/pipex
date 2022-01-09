/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakeshi <rtakeshi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 21:47:06 by rtakeshi          #+#    #+#             */
/*   Updated: 2022/01/09 22:00:50 by rtakeshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

/**
 * @brief Fill the cmd list object
 *
 * Fill commands considering a space character as split token
 * Model is flexibe to receive as many commands as needed
 */
t_list	*get_cmd_list(char *argv[], int offset, t_pipex *pipex)
{
	t_list *cmd_lst;
	int i;

	cmd_lst = NULL;
	i = 0;
	while (i < pipex->cmd_qty)
	{
		if (i == 0)
			cmd_lst = ft_lstnew(ft_split(argv[i + offset], ' '));
		else
			ft_lstadd_back(&cmd_lst, ft_lstnew(ft_split(argv[i + offset], ' ')));
		i++;
	}
	return (cmd_lst);
}

int	get_path(t_pipex *pipex, char *envp[])
{

}

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
	pipex->infile_fd = open(pipex->infile, O_RDONLY);
	pipex->outfile = argv[argc - 1];
	pipex->outfile_fd = open(pipex->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (pipex->outfile_fd == -1)
	{
		perror("Error");
		return (errno);
	}
	pipex->cmd_qty = argc - 3;
	pipex->offset = 2;
	pipex->cmd_lst = get_cmd_list(argv, pipex->offset, pipex);
	if (get_path(pipex, envp))
		return (errno);

	//test if cmd was correctly filled
	while (pipex->cmd_qty != 0)
	{
		printf("AQUI%s\n", pipex->cmd_lst->content[2]);
		pipex->cmd_lst = pipex->cmd_lst->next;
		pipex->cmd_qty--;
	}


	/*int		cmd;
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
	}*/
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
	t_pipex	pipex;

	if (check_args(argc, argv))
		return (1);
	if (init_pipex(argc, argv, envp, &pipex))
		return (1);

	//retirar o parse no path
	int i;

	i = -1;
	while (envp[++i] != NULL)
		printf("%s\n", envp[i]);

	/*int	pipefd[2];
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

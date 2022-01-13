/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakeshi <rtakeshi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 21:47:06 by rtakeshi          #+#    #+#             */
/*   Updated: 2022/01/13 18:27:50 by rtakeshi         ###   ########.fr       */
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
t_list	*get_cmd_list(char *argv[], int offset, int cmd_qty)
{
	t_list *cmd_lst;
	int i;

	i = 0;
	while (i < cmd_qty)
	{
		if (i == 0)
			cmd_lst = ft_lstnew(ft_split(argv[i + offset], ' '));
		else
			ft_lstadd_back(&cmd_lst, ft_lstnew(ft_split(argv[i + offset], ' ')));
		i++;
	}
	return (cmd_lst);
}

int	get_cmd_file(t_list *cmd_lst, char **paths)
{
	char	*aux;
	int		fd;

	aux = NULL;
	while (*paths)
	{
		aux = ft_strjoin(*paths,"/");
		if (aux == NULL)
		{
			perror("Error :");
			return(errno);
		}
		cmd_lst->cmd_file = ft_strjoin(aux, cmd_lst->content[0]);
		free(aux);
		fd = access(cmd_lst->cmd_file, R_OK);
		if (fd != -1)
			return (0);
		free (cmd_lst->cmd_file);
		paths++;
	}
	perror("Error");
	return (errno);
}
/**
 * @brief find the line that contains "PATH"
 *
 * @param envp ENVironment Pointer
 * @return char* Returns the line that contains "PATH=" without it or NULL if not found
 */
char	*find_line(char *envp[])
{
	while (*envp)
	{
		if (ft_strnstr(*envp, "PATH=", 5))
			return(*envp + 5);
		envp++;
	}
	return (NULL);
}


int	get_path(t_pipex *pipex, char *envp[])
{
	char	*aux_path;
	t_list	*tmp;

	aux_path = NULL;
	pipex->paths = NULL;
	tmp = pipex->cmd_lst;
	if (!(aux_path = find_line(envp)))
		return (-1);

	printf("\n\n");
	printf("%s\n", aux_path);
	printf("\n\n");

	pipex->paths = ft_split(aux_path, ':');

	printf("\n\n");
	int i = 0;
	while (pipex->paths[i])
	{
		printf("%s\n", (pipex->paths[i]));
		i++;
	}
	printf("\n\n");

	while((pipex->cmd_lst))
	{
		if (get_cmd_file(pipex->cmd_lst, pipex->paths))
			return (errno);
		printf("%s\n", pipex->cmd_lst->cmd_file);
		pipex->cmd_lst = pipex->cmd_lst->next;
	}
	pipex->cmd_lst = tmp;
	return(0);
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
	pipex->cmd_lst = get_cmd_list(argv, pipex->offset, pipex->cmd_qty);
	if (get_path(pipex, envp))
		return (errno);
	//test if cmd was correctly filled
	/*while (pipex->cmd_qty != 0)
	{
		printf("AQUI %s\n", pipex->cmd_lst->content[0]);
		printf("AQUI %s\n", pipex->cmd_lst->content[1]);
		printf("AQUI %s\n\n", pipex->cmd_lst->content[2]);
		pipex->cmd_lst = pipex->cmd_lst->next;
		pipex->cmd_qty--;
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

//trying to clean var pipex.paths
	char	*aux;
	char	**start;

	start = pipex.paths;
	while (*pipex.paths)
	{
		aux = *pipex.paths;
		printf("%s\n", aux);
		pipex.paths++;
		free(aux);
	}
	pipex.paths = start;
	free(pipex.paths);

//clean pipex cmd_struct
	t_list	*temp;
	int		i;

	while (pipex.cmd_lst != NULL)
	{
		temp = pipex.cmd_lst;
		i = 0;
		pipex.cmd_lst = pipex.cmd_lst->next;
		free(temp->cmd_file);
		while (temp->content[i])
		{
			printf("%s\n", temp->content[i]);
			free(temp->content[i]);
			i++;
		}
		free(temp->content);
		free(temp);
	}



	return (0);
}

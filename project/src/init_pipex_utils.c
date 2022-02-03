/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipex_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakeshi <rtakeshi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 15:14:30 by rtakeshi          #+#    #+#             */
/*   Updated: 2022/02/03 15:35:53 by rtakeshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

/**
 * @brief Fill the cmd list object
 *
 * Fill commands considering a space character as split token
 * Model is flexibe to receive as many commands as needed
 */
t_list	*get_cmd_lst(char *argv[], int offset, int cmd_qty)
{
	t_list	*cmd_lst;
	int		i;
	char	*aux;

	i = 0;
	while (i < cmd_qty)
	{
		aux = get_cmd(argv[i + offset]);
		if (i == 0)
			cmd_lst = ft_lstnew(undo_token(ft_split(aux, ' ')));
		else
			ft_lstadd_back(&cmd_lst, ft_lstnew(undo_token(ft_split(aux, ' '))));
		free(aux);
		i++;
	}
	return (cmd_lst);
}

/**
 * @brief Test possible paths of the cmd file and store it in a linked list
 *
 * @param cmd_lst -> store in cmd_lst->cmd_file the cmd path
 * @param paths -> source of the available paths
 * @return int -> o if SUCCESS and errno if error
 */
int	get_cmd_file(t_list *cmd_lst, char **paths)
{
	char	*aux;
	int		fd;

	aux = NULL;
	while (*paths)
	{
		aux = ft_strjoin(*paths, "/");
		if (aux == NULL)
			break ;
		cmd_lst->cmd_file = ft_strjoin(aux, cmd_lst->content[0]);
		free(aux);
		aux = NULL;
		fd = access(cmd_lst->cmd_file, R_OK);
		if (fd != -1)
			return (0);
		free (cmd_lst->cmd_file);
		cmd_lst->cmd_file = NULL;
		paths++;
	}
	return (errno);
}

/**
 * @brief find the line that contains "PATH"
 *
 * @param envp ENVironment Pointer
 * @return char* Returns the line that contains "PATH="
 * without it or NULL if not found
 */
char	*find_line(char *envp[])
{
	while (*envp)
	{
		if (ft_strnstr(*envp, "PATH=", 5))
			return (*envp + 5);
		envp++;
	}
	ft_putstr_fd("PATH not found.\n", 1);
	return (NULL);
}

/**
 * @brief Get the PATH line from envp variable and split it
 *
 * @param pipex -> fill the pipex->paths var
 * @param envp -> source of the PATH line
 * @return int -> o if SUCCESS and errno if error
 */
void	get_path(t_pipex *pipex, t_list *cmd_lst, char *envp[])
{
	char	*aux_path;

	aux_path = NULL;
	pipex->paths = NULL;
	aux_path = find_line(envp);
	if (!aux_path)
		return ;
	pipex->paths = ft_split(aux_path, ':');
	if (!access(cmd_lst->content[0], F_OK))
		cmd_lst->cmd_file = cmd_lst->content[0];
	else
	{
		if (get_cmd_file(cmd_lst, pipex->paths))
			cmd_lst->cmd_file = cmd_lst->content[0];
	}
	free_paths(pipex);
	return ;
}

/**
 * @brief Check if infile exists and get its fd and also create the oufile and
 * get its fd
 *
 * @param pipex -> fill the pipex->infile_fd and pipex->outfile_fd
 * @return int -> o if SUCCESS and errno if error
 */
int	get_fd(t_pipex *pipex)
{
	pipex->infile_fd = open(pipex->infile, O_RDONLY);
	if (pipex->infile_fd == -1)
		infile_error(pipex->infile, pipex->envp, errno);
	pipex->outfile_fd = open(pipex->outfile, \
		O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (pipex->outfile_fd == -1)
		perror("Error");
	return (errno);
}

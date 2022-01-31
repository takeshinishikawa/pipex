/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakeshi <rtakeshi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 15:14:30 by rtakeshi          #+#    #+#             */
/*   Updated: 2022/01/27 16:16:18 by rtakeshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

/**
 * @brief free command list structure (char *cmd_file and char **content)
 *
 * @param pipex used to get the cmd_lst t_list * variable
 */
void	free_cmd_lst(t_pipex *pipex)
{
	t_list	*aux;
	int		i;

	if (!pipex->cmd_lst)
		return ;
	while (pipex->cmd_lst != NULL)
	{
		aux = pipex->cmd_lst;
		i = 0;
		pipex->cmd_lst = pipex->cmd_lst->next;
		if (aux->cmd_file && (aux->cmd_file != aux->content[0]))
		{
			free(aux->cmd_file);
			aux->cmd_file = NULL;
		}
		while (aux->content[i])
		{
			free(aux->content[i]);
			aux->content[i] = NULL;
			i++;
		}
		free(aux->content);
		aux->content = NULL;
		free(aux);
		aux = NULL;
	}
	return ;
}

/**
 * @brief free the paths variable
 *
 * @param pipex used to get the paths char ** variable
 */
void	free_paths(t_pipex	*pipex)
{
	char	*aux;
	char	**start;

	if (!pipex->paths)
		return ;
	start = pipex->paths;
	while (*pipex->paths)
	{
		aux = *pipex->paths;
		pipex->paths++;
		free(aux);
		aux = NULL;
	}
	pipex->paths = start;
	free(pipex->paths);
	pipex->paths = NULL;
	return ;
}

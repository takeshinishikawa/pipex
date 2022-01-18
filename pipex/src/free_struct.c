/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakeshi <rtakeshi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 15:14:30 by rtakeshi          #+#    #+#             */
/*   Updated: 2022/01/14 15:40:09 by rtakeshi         ###   ########.fr       */
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
		if (aux->cmd_file)
			free(aux->cmd_file);
		while (aux->content[i])
		{
			free(aux->content[i]);
			i++;
		}
		free(aux->content);
		free(aux);
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
	}
	pipex->paths = start;
	free(pipex->paths);
	return ;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakeshi <rtakeshi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 17:21:56 by rtakeshi          #+#    #+#             */
/*   Updated: 2022/02/05 19:41:49 by rtakeshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <errno.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 128
# endif

typedef struct s_list
{
	char			**content;
	char			*cmd_file;
	struct s_list	*next;
}					t_list;

typedef struct s_pipex
{
	char	*infile;
	int		infile_fd;
	char	*outfile;
	int		outfile_fd;
	int		previous_fd;
	int		cmd_qty;
	int		here_doc;
	char	*limiter;
	int		offset;
	t_list	*cmd_lst;
	char	**paths;
	char	**envp;
}			t_pipex;

size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(char const *s, char c);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstlast(t_list *lst);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
char	*ft_strjoin(char const *s1, char const *s2);
int		check_argc(int argc, t_pipex *pipex);
void	init_pipex(int argc, char *argv[], char *envp[], t_pipex *pipex);
void	free_cmd_lst(t_pipex *pipex);
void	free_paths(t_pipex	*pipex);
t_list	*get_cmd_lst(char *argv[], int offset, int cmd_qty);
size_t	get_cmd_len(char *original_cmd);
char	*get_cmd(char *original_cmd);
char	**undo_token(char **cmd);
int		get_cmd_file(t_list *cmd_lst, char **paths);
char	*find_line(char *envp[]);
void	get_path(t_pipex *pipex, t_list *cmd_lst, char *envp[]);
int		get_fd(t_pipex *pipex);
void	infile_error(char *str, char *envp[], int error);
int		exec_pipex(t_pipex *pipex, char *argv[]);
int		get_exec_fd(int *fd);
int		get_pid(int *pid);
void	get_previous_fd(t_pipex *pipex, int *fd);
int		exec_cmd(t_pipex *pipex, int cmd_counter);
int		get_read_fd(t_pipex *pipex, int fd_read, int cmd_counter);
int		get_write_fd(t_pipex *pipex, int fd_write, int cmd_counter);
int		child_process(t_pipex *pipex, int fd_read, int fd_write, int p_exec);
void	cmd_not_found(char *str, char *envp[]);
void	permission_denied(char *str, char *envp[]);
int		clean_child_process(t_pipex *pipex, int errnumber);
int		check_exit(int w_status);
int		first_cmd(t_pipex *pipex, int fd_read, int cmd_counter);
void	free_prev_cmd(t_list *cmd);
char	*ft_strjoin_gnl(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);
size_t	ft_linelen(const char*s);
char	*ft_linedup(const char *s1);
int		get_next_line(int fd, char **line);

#endif

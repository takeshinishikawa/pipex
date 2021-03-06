#ifndef	PIPEX_H
# define PIPEX_H

# include <stdio.h> //tirar printf e incluid libc
# include <unistd.h> //execve
# include <fcntl.h> //read() open()
# include <time.h> //verificar se eh necessario
# include <sys/wait.h>
# include <sys/types.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <sysexits.h>
# include <stdlib.h>



typedef struct s_list
{
	char			**content;
	char			*cmd_file;
	struct s_list	*next;
}	t_list;

typedef struct s_pipex
{
	char	*infile;
	int		infile_fd;
	char	*outfile;
	int		outfile_fd;
	int		p_fd;
	int		cmd_qty;
	int		offset;
	t_list	*cmd_lst;
	char	**paths;
	char	**envp;
}	t_pipex;


size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		check_args(int argc, char *argv[]);
char	*ft_strtoken(char **str, char token);
char	**ft_split(char const *s, char c);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstlast(t_list *lst);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
char	*ft_strjoin(char const *s1, char const *s2);

int	init_pipex(int argc, char *argv[], char *envp[], t_pipex *pipex);
void	free_cmd_lst(t_pipex *pipex);
void	free_paths(t_pipex	*pipex);
t_list	*get_cmd_lst(char *argv[], int offset, int cmd_qty);
int		get_cmd_file(t_list *cmd_lst, char **paths, char *envp[]);
void	cmd_not_found(char *str, char *envp[]);
char	*find_line(char *envp[]);
int		get_path(t_pipex *pipex, char *envp[]);
int		get_fd(t_pipex *pipex);

int	exec_pipex(t_pipex *pipex, int p_fd);
void	free_prev_cmd(t_pipex *pipex);
int	child_process(t_pipex *pipex, int fd_read, int fd_write, int p_fd);
int	parent_process(t_pipex *pipex, int fd_read, int fd_write);
int	get_fd_and_pid(int *fd, pid_t *pid);


//incluir funções de lista

#endif

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

#define PROGRAM_NAME "./pipex"
#define QUOTATION_MARKS "\"" //check if really needs to maintain

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_pipex
{
	char	*infile;
	int		infile_fd;
	char	*outfile;
	int		outfile_fd;
	int		cmd_qty;
	int		offset;
	t_list	*cmd_list;
}	t_pipex;


size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		check_args(int argc, char *argv[]);
char	*ft_strtoken(char **str, char token);
char	**ft_split(char const *s, char c);
//incluir funções de lista

#endif

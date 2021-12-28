#ifndef	PIPEX_H
# define PIPEX_H

# include <stdio.h> //tirar printf e incluid libc
# include <unistd.h> //execve
# include <time.h> //verificar se eh necessario
# include <sys/wait.h>
# include <sys/types.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <sysexits.h>

#define PROGRAM_NAME "./pipex"
#define QUOTATION_MARKS "\"" //check if really needs to maintain
#define MAX_FLAGS 256

/*typedef struct s_cmd
{
	int		id;
	char	*cmd[id][MAX_FLAGS];
}	t_cmd;*/


typedef struct s_argv
{
	char	*infile;
	char	*outfile;
	char	*commands;
}	t_argv;



size_t	ft_strlen(const char *s);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
int	check_args(int argc, char *argv[]);
char	*ft_strtoken(char **str, char token);

#endif

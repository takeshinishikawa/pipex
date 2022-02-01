NAME = pipex

CFLAGS = -Wall -Wextra -Werror -g -ggdb3

SRC = main.c $(addprefix src/, ft_strlen.c ft_strncmp.c check_args.c \
	ft_strtoken.c ft_split.c ft_lstnew.c ft_lstadd_back.c ft_lstlast.c \
	ft_strnstr.c ft_putstr_fd.c ft_putchar_fd.c ft_strjoin.c \
	free_struct.c init_pipex.c init_pipex_utils.c exec_pipex.c \
	cmd_not_found.c exec_pipex_utils.c infile_error.c)

INC = ./inc/pipex.h

OBJ =	$(SRC:.c=.o)
RM =	rm -f


all:	 $(SRC)
	gcc $(CFLAGS) $(SRC) $(INC) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
		$(RM) $(NAME)
		rm outfile

re: 	fclean all

run:	all
	./$(NAME) assets/infile "tr a b" "tr b c" "tr c d" outs/outfile

runleak:	all
	valgrind -s --leak-check=full --trace-children=yes --show-leak-kinds=all --track-origins=yes ./$(NAME) assets/inf "grep a" "wc -l" outfile

A = $(shell ./pipex infile/deepthought.txt "grep Now" "exit 5" test_files/13outfile_pipex ; echo $$? )

testvar:
	echo $A > test_files/13outfile_pipex_exit
test13:
	< infile/deepthought.txt grep Now | exit 5 > test_files/13outfile_original
	./pipex infile/deepthought.txt "grep Now" "exit 5" test_files/13outfile_pipex
	diff test_files/13outfile_original test_files/13outfile_pipex
	diff test_files/13outfile_original_exit test_files/13outfile_pipex_exit

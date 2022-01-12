NAME = pipex

CFLAGS = -Wall -Wextra -Werror -g -ggdb3

SRC = main.c $(addprefix src/, ft_strlen.c ft_strncmp.c check_args.c \
	ft_strtoken.c ft_split.c ft_lstnew.c ft_lstadd_back.c ft_lstlast.c \
	ft_strnstr.c ft_putstr_fd.c ft_putchar_fd.c ft_strjoin.c)

INC = ./inc/pipex.h

OBJ =	$(SRC:.c=.o)
RM =	rm -f


all:	 $(SRC)
	gcc $(CFLAGS) $(SRC) $(INC) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
		$(RM) $(NAME)

re: 	fclean all

runleak:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -v ./$(NAME) "infile" "cmd a b c" "cmd" "outfile"

run:
	./$(NAME) "infile" "cmd1 a b c " "cmd2 d e f" "outfile"

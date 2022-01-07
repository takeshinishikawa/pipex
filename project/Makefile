NAME = pipex

CFLAGS = -Wall -Wextra -Werror -g -ggdb3

SRC = main.c $(addprefix src/, ft_strlen.c ft_strncmp.c check_args.c ft_strtoken.c ft_split.c)

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
	./$(NAME) "infile" "cmd a b c " "cmd" "outfile"

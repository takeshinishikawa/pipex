NAME = pipex

CFLAGS = -Wall -Wextra -Werror -g -ggdb3 -fsanitize=address

SRC = main.c $(addprefix src/, ft_strlen.c ft_strncmp.c check_args.c \
	ft_strtoken.c ft_split.c ft_lstnew.c ft_lstadd_back.c ft_lstlast.c \
	ft_strnstr.c ft_putstr_fd.c ft_putchar_fd.c ft_strjoin.c \
	free_struct.c init_pipex.c init_pipex_utils.c exec_pipex.c \
	cmd_not_found.c)

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
	./$(NAME) infile/infile "tr a b" "tr b c" "tr c d" outfile

runleak:	all
	valgrind -s --leak-check=full --trace-children=yes --show-leak-kinds=all --track-origins=yes ./$(NAME) infile "tr a b" "tr b c" "tr c d" outfile

rmtestfile:
	rm test_files/*

test1:
	< infile/infile | cat > test_files/1outfile_original
	./$(NAME) infile/infile " " "cat" test_files/1outfile_pipex
	make testdiff

test2:
	< infile/infile cat > test_files/2outfile_original
	./$(NAME) infile/infile cat test_files/2outfile_pipex
	make testdiff

test3:
	< infile/infile tr a b | tr b c > test_files/3outfile_original
	echo $? > test_files/3outfile_original_exit
	./$(NAME) infile/infile "tr a b" "tr b c" test_files/3outfile_pipex
	echo $? > test_files/3outfile_pipex_exit
	diff test_files/3outfile_original test_files/3outfile_pipex
	diff test_files/3outfile_original_exit test_files/3outfile_pipex_exit

test4:
	< infile/deepthought.txt cat | hostname > test_files/4outfile_original
	echo $? > test_files/4outfile_original_exit
	./$(NAME) infile/deepthought.txt "cat" "hostname" test_files/4outfile_pipex
	echo $? > test_files/4outfile_pipex_exit
	diff test_files/4outfile_original test_files/4outfile_pipex
	diff test_files/4outfile_original_exit test_files/4outfile_pipex_exit

test5:
	< infile/deepthought.txt grep Now | head -2 > test_files/5outfile_original
	echo $? > test_files/5outfile_original_exit
	./$(NAME) infile/deepthought.txt "grep Now" "head -2" test_files/5outfile_pipex
	echo $? > test_files/5outfile_pipex_exit
	diff test_files/5outfile_original test_files/5outfile_pipex
	diff test_files/5outfile_original_exit test_files/5outfile_pipex_exit

test6:
	< infile/deepthought.txt grep Now | cat > test_files/6outfile_original
	echo $? > test_files/6outfile_original_exit
	./$(NAME) infile/deepthought.txt "grep Now" "cat" test_files/6outfile_pipex
	echo $? > test_files/6outfile_pipex_exit
	diff test_files/6outfile_original test_files/6outfile_pipex
	diff test_files/6outfile_original_exit test_files/6outfile_pipex_exit

test7:
	< infile/deepthought.txt wc -w | cat > test_files/7outfile_original
	echo $? > test_files/7outfile_original_exit
	./$(NAME) infile/deepthought.txt "wc -w" "cat" test_files/7outfile_pipex
	echo $? > test_files/7outfile_pipex_exit
	diff test_files/7outfile_original test_files/7outfile_pipex
	diff test_files/7outfile_original_exit test_files/7outfile_pipex_exit

test8:
	< infile/deepthought.txt notexisting | wc > test_files/8outfile_original
	echo $? > test_files/8outfile_original_exit
	./$(NAME) infile/deepthought.txt "notexisting" "wc" test_files/8outfile_pipex
	echo $? > test_files/8outfile_pipex_exit
	diff test_files/8outfile_original test_files/8outfile_pipex
	diff test_files/8outfile_original_exit test_files/8outfile_pipex_exit

test9:
	< infile/deepthought.txt notexisting | cat > test_files/9outfile_original
	echo $? > test_files/9outfile_original_exit
	./$(NAME) infile/deepthought.txt "notexisting" "cat" test_files/9outfile_pipex
	echo $? > test_files/9outfile_pipex_exit
	diff test_files/9outfile_original test_files/9outfile_pipex
	diff test_files/9outfile_original_exit test_files/9outfile_pipex_exit

test10:
	< infile/deepthought.txt grep Now | /usr/bin/cat > test_files/10outfile_original
	echo $? > test_files/10outfile_original_exit
	./$(NAME) infile/deepthought.txt "grep Now" "/usr/bin/cat" test_files/10outfile_pipex
	echo $? > test_files/10outfile_pipex_exit
	diff test_files/10outfile_original test_files/10outfile_pipex
	diff test_files/10outfile_original_exit test_files/10outfile_pipex_exit

test11:
	< /dev/urandom cat | head -1 > test_files/11outfile_original
	echo $? > test_files/11outfile_original_exit
	./$(NAME) /dev/urandom "cat" "head -1" test_files/11outfile_pipex
	echo $? > test_files/11outfile_pipex_exit
	diff test_files/11outfile_original test_files/11outfile_pipex
	diff test_files/11outfile_original_exit test_files/11outfile_pipex_exit

test12:
	< fiwefcen/fileewe_in cat -e | grep gewoon > test_files/12outfile_original
	echo $? > test_files/12outfile_original_exit
	./$(NAME) fiwefcen/fileewe_in "cat -e" "grep gewoon" test_files/12outfile_pipex
	echo $? > test_files/12outfile_pipex_exit
	diff test_files/12outfile_original test_files/12outfile_pipex
	diff test_files/12outfile_original_exit test_files/12outfile_pipex_exit

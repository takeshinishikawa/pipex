# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rtakeshi <rtakeshi@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/05 19:39:57 by rtakeshi          #+#    #+#              #
#    Updated: 2022/02/05 20:00:28 by rtakeshi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	pipex
BONUS	=	pipex_bonus

CFLAGS	=	-Wall -Wextra -Werror -g -ggdb3
RM		=	rm -rf
OBJ_DIR	=	obj

INC 	= 	./inc/pipex.h
SRC_DIR	=	src
SRC 	= $(addprefix $(SRC_DIR)/, pipex.c ft_strlen.c ft_strncmp.c \
	check_args.c ft_split.c ft_lstnew.c ft_lstadd_back.c ft_lstlast.c \
	ft_strnstr.c ft_putstr_fd.c ft_putchar_fd.c ft_strjoin.c \
	free_struct.c init_pipex.c init_pipex_utils.c exec_pipex.c \
	cmd_not_found.c exec_pipex_utils.c infile_error.c permission_denied.c \
	exec_pipex_utils2.c cmd_utils.c)

OBJ		=	$(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

INC_BONUS = ./inc/pipex.h
SRC_BONUS_DIR	=	src_bonus

SRC_BONUS = $(addprefix $(SRC_BONUS_DIR)/, pipex_bonus.c ft_strlen_bonus.c \
	ft_strncmp_bonus.c check_args_bonus.c ft_split_bonus.c ft_lstnew_bonus.c \
	ft_lstadd_back_bonus.c ft_lstlast_bonus.c ft_strnstr_bonus.c \
	ft_putstr_fd_bonus.c ft_putchar_fd_bonus.c ft_strjoin_bonus.c \
	free_struct_bonus.c init_pipex_bonus.c init_pipex_utils_bonus.c \
	exec_pipex_bonus.c cmd_not_found_bonus.c exec_pipex_utils_bonus.c \
	infile_error_bonus.c permission_denied_bonus.c exec_pipex_utils2_bonus.c \
	cmd_utils_bonus.c get_next_line.c get_next_line_utils.c)

OBJ_BONUS	=	$(SRC_BONUS:$(SRC_BONUS_DIR)/%.c=$(OBJ_DIR)/%.o)

all:			$(NAME)

$(NAME):		$(OBJ_DIR) $(OBJ) $(INC)
				gcc $(CFLAGS) $(OBJ) $(INC) -o $(NAME)

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c $(INC)
				gcc $(CFLAGS) -c $< -o $@

bonus:			$(BONUS)

$(BONUS):		$(OBJ_DIR) $(OBJ_BONUS) $(INC_BONUS)
				gcc $(CFLAGS) $(OBJ_BONUS) $(INC_BONUS) -o $(BONUS)

$(OBJ_DIR)/%.o:	$(SRC_BONUS_DIR)/%.c $(INC_BONUS)
				gcc $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
				mkdir $(OBJ_DIR)

clean:
				$(RM) $(OBJ_DIR)

fclean: 		clean
				$(RM) $(NAME) $(BONUS)

re:				fclean all

.PHONY:			all clean fclean re bonus

runleak:	all
	valgrind -s --leak-check=full --trace-children=yes --show-leak-kinds=all --track-origins=yes ./$(NAME) assets/infile "cat" "cat" outfile

runleakbonus:	bonus
	valgrind -s --leak-check=full --trace-children=yes --show-leak-kinds=all --track-origins=yes ./$(BONUS) assets/infile "cat" "cat" "cat" outfile

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbenatta <lbenatta@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/24 12:17:45 by lbenatta          #+#    #+#              #
#    Updated: 2022/09/15 17:05:22 by lbenatta         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lr
CC = gcc

SRC	=	common.h linear_regression_utils.c \
	linear_regression_estimate.c \
	linear_regression_predict.c \
	linear_regression_train.c

OBJ = $(SRC:.c=.o)
CFLAGS = -g -Wall -Wextra -Werror -lm

RM = rm -rf

all: $(NAME)
estim: linear_regression_estimate.c
	@gcc common.h linear_regression_utils.c linear_regression_estimate.c -g -lm
	@./a.out

predict: linear_regression_predict.c
	@gcc common.h linear_regression_utils.c linear_regression_predict.c -g -lm
	@./a.out

train: linear_regression_train.c
	@gcc common.h linear_regression_utils.c linear_regression_train.c -g -lm
	@./a.out

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@

clean:
	$(RM) $(OBJ)
	rm -rf *.o
	rm -rf $(OBJS)

fclean: clean
	rm -f $(NAME)


leaks: $(NAME)
	valgrind ./lr --leak-check=full --show-leak-kinds=all --track-origins=yes

re: fclean all

.PHONY: all clean fclean re

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbenatta <lbenatta@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/24 12:17:45 by lbenatta          #+#    #+#              #
#    Updated: 2022/09/19 14:53:07 by lbenatta         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lr

CC = gcc

CFLAGS = -g -Wall -Wextra -Werror

LDFLAGS = -lm

SRC	= linear_regression_utils.c \
	linear_regression_estimate.c \
	linear_regression_predict.c \
	linear_regression_train.c

OBJS = $(SRC:.c=.o)

INCLUDE = common.h

RM = rm -rf

all: $(NAME)
#all : estim predict train
estim: linear_regression_estimate.c
	@$(CC) $(CFLAGS) common.h linear_regression_utils.c linear_regression_estimate.c $(LDFLAGS)
	@./a.out

pred: linear_regression_predict.c
	@$(CC) $(CFLAGS) common.h linear_regression_utils.c linear_regression_predict.c $(LDFLAGS)
	@./a.out

train: linear_regression_train.c
	#@rm -rf *.o
	@$(CC) $(CFLAGS) common.h linear_regression_utils.c linear_regression_train.c $(LDFLAGS)
	@./a.out

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@

clean:
	$(RM) $(OBJS)
	rm -rf *.o
	rm -rf $(OBJS)

fclean: clean
	rm -f $(NAME)

leaks: $(NAME)
	valgrind ./lr --leak-check=full --show-leak-kinds=all --track-origins=yes

re: fclean all

.PHONY: all clean fclean re

.PHONY: all clean fclean re

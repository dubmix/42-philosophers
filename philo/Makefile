# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pdelanno <pdelanno@student.42berlin.d      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/22 21:42:49 by pdelanno          #+#    #+#              #
#    Updated: 2023/07/22 21:42:56 by pdelanno         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = src/actions.c src/init.c src/philosophers.c src/threading.c src/utils.c

OBJS = ${SRCS:.c=.o}

HEADERS = philosophers.h

CFLAGS = -g -Werror -Wall -Wextra

.c.o:
				@cc ${CFLAGS} -c $^ -o $@

all:			${NAME}

$(NAME):		${OBJS}
						@cc ${OBJS} $(CFLAGS) -o $(NAME)
						@echo "\033[1;5mProgram is ready!\033[0m"

clean:
				@rm -f ${OBJS}

fclean:			clean
						@cd src && rm -f ${NAME}
						@rm -f ${NAME}
						@echo "\033[1mAll clean!\033[0m"

re: fclean all

.PHONY: all clean fclean re

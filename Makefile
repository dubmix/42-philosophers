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

NAME = philosophers

SRCS = src/actions.c src/init.c src/philosophers.c src/threading.c src/utils.c

OBJS = ${SRCS:.c=.o}

HEADERS = philosophers.h

CFLAGS = -g -Werror -Wall -Wextra

.c.o:
				@cc ${CFLAGS} -c $^ -o $@

all:			${NAME}

$(NAME):		${OBJS}
						@cc ${OBJS} $(CFLAGS) -o $(NAME)
						@echo "Program is ready!"

clean:
				@rm -f ${OBJS}

fclean:			clean
						@cd src && rm -f ${NAME}
						@rm -f ${NAME}
						@echo "All clean!"

re: fclean all

.PHONY: all clean fclean re

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hpehliva <hpehliva@student.42heilbronn.de  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/11 11:28:45 by hpehliva          #+#    #+#              #
#    Updated: 2025/03/11 11:28:46 by hpehliva         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = cleanup.c controller.c create_threads.c input.c \
		main.c parsing.c routine.c utils.c

OBJS = $(SRCS:.c=.o)


NAME = philo

CC = cc

CFLAG = -Wall -Wextra -Werror -I.

LIBS = -lpthread

RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
		$(CC) $(CFLAG) -o $(NAME) $(OBJS) $(LIBS)

clean:
		$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
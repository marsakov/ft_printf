#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msakovyc <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/22 20:42:29 by msakovyc          #+#    #+#              #
#    Updated: 2018/05/22 20:42:30 by msakovyc         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = libftprintf.a
TEST = ft_printf.out
SRCS = ft_print_modifiers.c ft_print_unicode.c ft_printf.c ft_prints.c 

OBJS = $(SRCS:.c=.o)

all: $(NAME) 

$(NAME):
	@gcc -c -Wall -Werror -Wextra libft/*.c -I libft/libft.h
	@gcc -c $(SRCS)
	@ar rc $(NAME) *.o

test:
	@gcc -g -L. -lftprintf $(SRCS) main.c -o $(TEST)
 
clean:
	@rm -rf *.o libft/*.o

fclean: clean
	@rm -rf $(NAME)

re: fclean all
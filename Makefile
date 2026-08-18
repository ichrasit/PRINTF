NAME	= libftprintf.a
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
SRCS	= ft_printf.c ft_format_chars.c ft_utils.c ft_format_nums.c ft_format_hex.c
OBJS	= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
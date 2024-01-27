CC = cc
CLANG = -Wall -Wextra -Werror -lmlx -framework OpenGL -framework AppKit
NAME = so_long
SRCS = ft_printf.c print_decimal.c print_hex.c get_next_line_utils.c get_next_line.c event.c maps.c so_long_utils.c main.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)
$(NAME) : $(OBJS)
	$(CC) $(CLANG) $^ -o $@
clean:
	rm -f $(OBJS)
fclean:
	make clean
	rm -f $(NAME)
re:
	make fclean
	make all
.PHONY: clean fclean re
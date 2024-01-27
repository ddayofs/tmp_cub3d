# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: donglee2 <donglee2@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/17 16:31:55 by donglee2          #+#    #+#              #
#    Updated: 2024/01/27 16:40:53 by donglee2         ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
CC = cc
# CFLAGS = -fsanitize=address -g
# CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -L./libft -lft
MLXFLAG = -lmlx -framework OpenGL -framework AppKit -g3 -fsanitize=address

MANDATORY_SRCS = main.c key_hook.c parse.c parse_condition_check.c parse_utils.c\
raycasting.c ft_bfs.c draw_pixel.c ft_init.c ft_queue.c key_hook_utils.c

MANDATORY_OBJS = $(MANDATORY_SRCS:.c=.o)
RM = rm -rf

MAKE = make

LIBFT = libft/libft.a

all: $(NAME)

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $< -g3

$(LIBFT):
	$(MAKE) -C ./libft bonus



$(NAME): $(MANDATORY_OBJS) $(LIBFT) 
	$(CC) $(CFLAGS) -o $(NAME) $(MANDATORY_OBJS) $(LDFLAGS) $(MLXFLAG)

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(BONUS_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(BONUS_NAME) $(BONUS_OBJS) $(LDFLAGS) $(MLXFLAG)
	touch $@

clean:	
	$(RM) $(MANDATORY_OBJS) $(BONUS_OBJS) bonus
	$(MAKE) -C ./libft clean

fclean: clean
	$(RM) $(NAME) $(BONUS_NAME)
	$(RM) $(LIBFT)
	
re: fclean all

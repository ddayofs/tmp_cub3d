# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: donglee2 <donglee2@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/28 16:03:50 by donglee2          #+#    #+#              #
#    Updated: 2023/10/11 19:06:43 by donglee2         ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
MANDATORY_SRCS = ft_atoi.c\
ft_bzero.c\
ft_calloc.c\
ft_isalnum.c\
ft_isalpha.c\
ft_isascii.c\
ft_isdigit.c\
ft_islonger.c\
ft_isprint.c\
ft_isspace.c\
ft_itoa.c\
ft_memchr.c\
ft_memcmp.c\
ft_memcpy.c\
ft_memmove.c\
ft_memset.c\
ft_putchar_fd.c\
ft_putendl_fd.c\
ft_putnbr_fd.c\
ft_putstr_fd.c\
ft_split.c\
ft_strchr.c\
ft_strdup.c\
ft_striteri.c\
ft_strjoin.c\
ft_strlcat.c\
ft_strlcpy.c\
ft_strlen.c\
ft_strmapi.c\
ft_strcmp.c\
ft_strncmp.c\
ft_strnstr.c\
ft_strrchr.c\
ft_strtrim.c\
ft_substr.c\
ft_tolower.c\
ft_toupper.c\

BONUS_SRCS = ft_lstnew.c\
ft_lstadd_front.c\
ft_lstsize.c\
ft_lstlast.c\
ft_lstadd_back.c\
ft_lstdelone.c\
ft_lstclear.c\
ft_lstiter.c\
ft_lstmap.c\
get_next_line_bonus.c\
get_next_line_utils_bonus.c\
ft_printf.c\
ft_printf.c\
ft_putchar.c\
ft_putnbr_base_addr.c\
ft_putnbr_base_ll.c\
ft_putstr_fd_ret_cnt.c\

MANDATORY_OBJS = $(MANDATORY_SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)
ARRC = ar -cr
RM = rm -rf

all: $(NAME)

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(MANDATORY_OBJS)
	$(ARRC) $(NAME) $(MANDATORY_OBJS)

bonus: $(BONUS_OBJS) $(MANDATORY_OBJS)
	$(ARRC) $(NAME) $(MANDATORY_OBJS) $(BONUS_OBJS)
	touch $@

clean:
	$(RM) $(MANDATORY_OBJS) $(BONUS_OBJS) bonus
 
fclean: clean
	$(RM) $(NAME)
 
re: fclean all

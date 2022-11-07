# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/05 14:00:38 by thhusser          #+#    #+#              #
#    Updated: 2022/11/07 12:35:03 by thhusser         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

_NC=`tput sgr0`
_RED=\033[0;31m
_GREEN=\033[0;32m
_YELLOW=\033[0;33m
_BLUE=\033[0;34m
_PURPLE=\033[0;95m
_CYAN=\033[0;36m
_WHITE=\033[0;37m

NAME	=	libft.a

SRCS	=	ft_memset.c \
			ft_bzero.c \
			ft_memcpy.c \
			ft_memccpy.c \
			ft_memmove.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_strlen.c \
			ft_isalpha.c \
			ft_isdigit.c \
			ft_isalnum.c \
			ft_isascii.c \
			ft_isprint.c \
			ft_toupper.c \
			ft_tolower.c \
			ft_strchr.c \
			ft_strrchr.c \
			ft_strncmp.c \
			ft_strlcpy.c \
			ft_strlcat.c \
			ft_strnstr.c \
			ft_atoi.c \
			ft_calloc.c \
			ft_strdup.c \
			ft_substr.c \
			ft_strjoin.c \
			ft_strtrim.c \
			ft_split.c \
			ft_itoa.c \
			ft_strmapi.c \
			ft_putchar_fd.c \
			ft_putstr_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_lstnew.c \
			ft_lstadd_front.c \
			ft_lstadd_back.c \
			ft_lstlast.c \
			ft_lstsize.c \
			ft_lstdelone.c \
			ft_lstclear.c \
			ft_lstiter.c \
			ft_lstmap.c \
			ft_strncpy.c \
			ft_strcat.c \
			ft_strcpy.c \
			ft_strncat.c \
			ft_strcmp.c \
			ft_strstr.c \
			ft_memdel.c \
			ft_memalloc.c \
			ft_putnbr.c \
			ft_putstr.c \
			ft_putchar.c \
			ft_strnew.c \
			ft_strclr.c \
			ft_strdel.c \
			ft_striter.c \
			ft_striteri.c \
			ft_strmap.c \
			ft_strequ.c \
			ft_strnequ.c \
			ft_putendl.c \
			get_next_line.c \
			ft_isspace.c \
			ft_long_atoi.c \
			ft_is_nbr.c \
			ft_print_list.c \
			ft_del_list.c \
			ft_split_charset.c \
			ft_del_line.c \

OBJS	=	${SRCS:.c=.o}

CFLAGS	=	-Wall -Wextra -Werror

RM		=	rm -f

HEADER	=	-I libft/libft.h

.c.o:
			@printf "$(_WHITE)Generating libft objects... %-33.33s\r$(_NC)" $@
			@gcc ${CFLAGS} ${HEADER} -c $< -o $(<:.c=.o)

${NAME}:	${OBJS}
			@echo ""
			@gcc $(FLAGS) -c $(SRCS)
			@ar rcs ${NAME} ${OBJS}
			@echo "$(_GREEN)Generating $(NAME)$(_NC)"

all:		${NAME}

clean:
ifneq ($(wildcard $(OBJS)),)
		@${RM} $(OBJS);
		@echo "$(_GREEN)Deletes objects files libft$(_NC)"
endif

fclean:		clean
ifneq ($(wildcard $(NAME)),)
		@${RM} ${NAME};
		@echo "$(_GREEN)Delete $(NAME)$(_NC)"
endif

re:			fclean all

.PHONY:		all clean fclean re bonus

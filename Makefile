# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alilin <alilin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/07 12:30:25 by thhusser          #+#    #+#              #
#    Updated: 2023/01/18 20:08:32 by alilin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

_NC     = `tput sgr0`
_RED    = \033[0;31m
_GREEN  = \033[0;32m
_YELLOW = \033[0;33m
_BLUE   = \033[0;34m
_PURPLE = \033[0;95m
_CYAN   = \033[0;36m
_WHITE  = \033[0;37m

NAME    = ft_ping
RM      = rm      -rf
CC      = clang
FLAGS   = -Wall -Wextra -Werror -g
DIR_INC = -I ./includes/

SRCS 	:= 	ft_ping.c \
			ft_getopt.c \
			ft_handleopt.c \
			utils.c \
			ft_display.c \

DIR_SRCS 	= ./srcs

DIR_OBJ 	= obj

PATH_LIBFT = ./libft
DIR_INC += -I $(PATH_LIBFT)

OBJS        := $(addprefix ${DIR_OBJ}/, ${SRCS:.c=.o})

DEPS        =  $(OBJS:.o=.d)

all: $(NAME)

-include $(DEPS)

$(DIR_OBJ)/%.o:	$(DIR_SRCS)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(FLAGS) $(DIR_INC) -o $@ -c $< -MMD

$(NAME): $(OBJS)
	make -C $(PATH_LIBFT)
	@$(CC) $(FLAGS) $(DIR_INC) $(OBJS) -o $(NAME) -L $(PATH_LIBFT) -lft
	@printf "$(_GREEN)Generating $(NAME) $(_NC)\n"

clean:
	make -C $(PATH_LIBFT) clean
	@$(RM) $(DIR_OBJ)
	@printf "$(_GREEN)Deletes objects files $(NAME) $(_NC)\n"

fclean:		clean
	make -C $(PATH_LIBFT) fclean
	@$(RM) $(NAME)
	@printf "$(_GREEN)Delete $(NAME) $(_NC)\n"

re:	fclean all
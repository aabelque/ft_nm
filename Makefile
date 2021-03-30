# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aabelque <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/04 13:38:41 by aabelque          #+#    #+#              #
#    Updated: 2021/03/29 16:14:43 by aabelque         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKE = make

H_DIR = include/
C_DIR = srcs/
O_DIR = objs/

NAME = ft_nm

CC = gcc
DEBUG = -g3
CFLAG = -Wall -Wextra -Werror -Wpadded

SRC = ft_nm.c
SRC += nm_utils.c
SRC += libc.c
SRC += nm_64.c
SRC += nm_32.c
SRC += fat32.c
SRC += fat64.c
SRC += swap.c
SRC += ar.c

OBJS = $(addprefix $(O_DIR),$(SRC:.c=.o))

all: $(NAME)
	
$(NAME): $(OBJS) $(H_DIR)
	@$(CC) $(DEBUG) $(CFLAGS) -o $(NAME) $(OBJS)
	@tput dl; tput el1; tput cub 100; echo "\033[33mBuilt ft_nm:\033[0m \033[32;1;4m$(notdir $@)\033[0m"

$(OBJS): $(O_DIR)%.o: $(C_DIR)%.c
	@mkdir $(O_DIR) 2> /dev/null || echo "" > /dev/null
	@$(CC) $(DEBUG) $(CFLAGS) -o $@ -c $< -fPIC -I$(H_DIR)

norme:
	@norminette $(C_DIR)
	@norminette $(H_DIR)
	@echo "\033[3;32m[ ✔ ] Norme is done.\033[0m"

clean:
	@rm -rf $(O_DIR) 2> /dev/null || echo "" > /dev/null

fclean: clean
	@rm -rf $(NAME) 2> /dev/null || echo "" > /dev/null
	@echo "\033[33mRemoved ft_nm: \033[32;1;4m$(NAME)\033[0m"

re: fclean all

.PHONY: all clean fclean re

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aabelque <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/04 13:38:41 by aabelque          #+#    #+#              #
#    Updated: 2021/03/31 20:05:26 by aabelque         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OS = $(shell uname -s)
MAKE = make

H_DIR = include/
C_DIR_MAC = srcs/srcs_macos/
C_DIR_LINUX = srcs/srcs_linux/
O_DIR = objs/
O_DIR_MAC = objs/objs_mac/
O_DIR_LINUX = objs/objs_linux/

NAME = ft_nm

CC = gcc
DEBUG = -g3
CFLAG = -Wall -Wextra -Werror -Wpadded

SRC_LINUX = 

SRC_MAC = ft_nm.c
SRC_MAC += nm_utils.c
SRC_MAC += libc.c
SRC_MAC += nm_64.c
SRC_MAC += nm_32.c
SRC_MAC += fat32.c
SRC_MAC += fat64.c
SRC_MAC += swap.c
SRC_MAC += ar.c

all: $(NAME)

ifeq ($(OS), Darwin)

OBJS_MAC = $(addprefix $(O_DIR_MAC),$(SRC_MAC:.c=.o))
	
$(NAME): $(OBJS_MAC) $(H_DIR)
	@$(CC) $(DEBUG) $(CFLAGS) -o $(NAME) $(OBJS_MAC)
	@tput dl; tput el1; tput cub 100; echo "\033[33mBuilt ft_nm:\033[0m \033[32;1;4m$(notdir $@)\033[0m"

$(OBJS_MAC): $(O_DIR_MAC)%.o: $(C_DIR_MAC)%.c
	@mkdir -p $(O_DIR_MAC) 2> /dev/null || echo "" > /dev/null
	@$(CC) $(DEBUG) $(CFLAGS) -o $@ -c $< -fPIC -I$(H_DIR)

endif

ifeq ($(OS), Linux)
	
OBJS_LINUX = $(addprefix $(O_DIR_LINUX),$(SRC_LINUX:.c=.o))

$(NAME): $(OBJS_LINUX) $(H_DIR)
	@$(CC) $(DEBUG) $(CFLAGS) -o $(NAME) $(OBJS_LINUX)
	@tput dl; tput el1; tput cub 100; echo "\033[33mBuilt ft_nm:\033[0m \033[32;1;4m$(notdir $@)\033[0m"

$(OBJS_MAC): $(O_DIR_LINUX)%.o: $(C_DIR_LINUX)%.c
	@mkdir -p $(O_DIR_LINUX) 2> /dev/null || echo "" > /dev/null
	@$(CC) $(DEBUG) $(CFLAGS) -o $@ -c $< -fPIC -I$(H_DIR)

endif

# norme:
# 	@norminette $(C_DIR_MAC)
# 	@norminette $(H_DIR)
# 	@echo "\033[3;32m[ ✔ ] Norme is done.\033[0m"

clean:
	@rm -rf $(O_DIR) 2> /dev/null || echo "" > /dev/null

fclean: clean
	@rm -rf $(NAME) 2> /dev/null || echo "" > /dev/null
	@echo "\033[33mRemoved ft_nm: \033[32;1;4m$(NAME)\033[0m"

re: fclean all

.PHONY: all clean fclean re

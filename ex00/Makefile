# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bducrocq <bducrocq@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/29 16:05:24 by cfatrane          #+#    #+#              #
#    Updated: 2023/03/21 02:05:58 by bducrocq         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

# Binary 

NAME = btc

# Path

SRC_PATH = ./srcs/
SRC_EXT = cpp

OBJ_PATH = ./objs/

CPPFLAGS = -I./includes/

HEADER =	./includes/BitcoinExchange.hpp

# Name

SRC_NAME =	main.cpp BitcoinExchange.cpp

OBJ_NAME = $(SRC_NAME:.cpp=.o)

# Files

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))

OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))

# Flags

CC = c++ $(STDCPP) $(CFLAGS) $(SANITIZE) $(LLDBFLAG)

CFLAGS = -Wall -Wextra -Werror
SANITIZE =# -fsanitize=address
LLDBFLAG = #-g3
STDCPP = -std=c++98

# Rules

all: $(NAME) 


$(NAME): $(OBJ)
ifeq ($(shell uname -s), Linux)
	@echo "\033[34mCreation of $(NAME) on linux ...\033[0m"
	@$(CC) $(OBJ) -o $@
	@echo "\033[32m$(NAME) created\n\033[0m"
else
	@echo "\033[34mCreation of $(NAME) ...\033[0m"
	@$(CC) $(OBJ) -o $@
	@echo "\033[32m$(NAME) created\n\033[0m"
endif

$(OBJ_PATH)%.o: $(SRC_PATH)%.$(SRC_EXT) $(HEADER) ./Makefile
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	$(CC) $(CPPFLAGS) -o $@ -c $<

clean:
	@echo "\033[33mRemoval of .o files of $(NAME) ...\033[0m"
	@rm -f $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || true
	@echo "\033[31mFiles .o deleted\n\033[0m"

fclean: clean
	@echo "\033[33mRemoval of $(NAME)...\033[0m"
	@rm -rf $(NAME)
	@echo "\033[31mBinary $(NAME) deleted\n\033[0m"

re: fclean all


git:
	@git add .
	@printf "Message of the commit: " && read msg && git commit -m "$$msg"
	@git push

.PHONY: all, clean, fclean, re

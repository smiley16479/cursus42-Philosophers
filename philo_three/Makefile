# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user42 <user42@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/09 23:20:17 by adtheus           #+#    #+#              #
#    Updated: 2021/03/14 17:46:38 by user42           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_three

SRC_DIR = .
OBJ_DIR = obj

SRC = 			main.c \
				phisiology.c

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:%.c=%.o))

CFLAG = -Wall -Wextra -Werror #-g3 -fsanitize=address #

LFLAG = -lpthread

all		: $(NAME)

show	:
	@echo "SRC_DIR : $(SRC_DIR)\n"
	@echo "CFLAG : $(CFLAG)\n"
	@echo "SRC :$(foreach file, $(SRC),\n\t$(file))\n"
	@echo "OBJ :$(foreach file, $(OBJ),\n\t$(file))\n"

## -c = definit les fichiers sources a compiler
## -o = change le nom du fichier d'output
## $@ = la cible de la regle
## $< = la premiere dependance de la regle
## $^ = les dependances de la regle

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@gcc $(CFLAG) $(LFLAG) -c $< -o $@

$(NAME)	: $(OBJ)
	@gcc $(OBJ) $(CFLAG) $(LFLAG) -o $@


debug : $(NAME)
	@./$(NAME)

clean	:
	@rm -f $(OBJ)

fclean	: clean
	@rm -f $(NAME)
	@rm -rf $(OBJ_DIR)

re		: fclean all

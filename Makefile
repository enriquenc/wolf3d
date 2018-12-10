#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmaslyan <tmaslyan@student.unit.ua>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/10 15:30:58 by tmaslyan          #+#    #+#              #
#    Updated: 2018/12/10 15:30:59 by tmaslyan         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = wolf3d

FLAGS = -Wall -Wextra -Werror

INCLUDES =	-I /Library/Frameworks/SDL2.framework/Versions/A/Headers\
			-F /Library/Frameworks/ -framework SDL2

SRC_DIR = ./src/

SRC_FILES = main.c

SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	gcc $(OBJ) -o $(NAME) $(INCLUDES)

%.o: %.cpp
	gcc $(FLAGS) -o $@ -c $<

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
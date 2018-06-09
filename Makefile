# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pribault <pribault@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/09 10:39:10 by pribault          #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2018/06/09 15:32:29 by pribault         ###   ########.fr        #
=======
#    Updated: 2018/06/09 14:38:49 by lvasseur         ###   ########.fr        #
>>>>>>> master
#                                                                              #
# **************************************************************************** #

NAME =	ft_gkrellm
CC =	clang++
FLAGS =	-Wall -Wextra -Werror

SRC_DIR =	src
OBJ_DIR =	.obj
INC_DIR =	include

<<<<<<< HEAD
SRC =	ft_gkrellm.cpp Terminal.cpp Window.cpp Log.cpp TerminalMonitor.cpp\
		IMonitorModule.cpp IMonitorDisplay.cpp term.cpp
OBJ =	$(sort $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(SRC)))
INC =	ft_gkrellm.hpp IMonitorModule.hpp IMonitorDisplay.hpp Terminal.hpp\
		Window.hpp Log.hpp TerminalMonitor.hpp
=======
SRC =	main.cpp Terminal.cpp Window.cpp Log.cpp CPU.cpp
OBJ =	$(sort $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(SRC)))
INC =	IMonitorModule.hpp IMonitorDisplay.hpp Terminal.hpp\
		Window.hpp Log.hpp
>>>>>>> master
INCLUDE =	$(sort $(patsubst %.hpp, $(INC_DIR)/%.hpp, $(INC)))

.PHONY: all clean fclean re sdl2

all: $(NAME)

$(OBJ_DIR):
	mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(INCLUDE) | $(OBJ_DIR)
	$(CC) $(FLAGS) -I $(INC_DIR) -o $@ -c $<

$(NAME): $(OBJ)
	echo $(OBJ)
	$(CC) $(FLAGS) -o $(NAME) $(OBJ) -lncurses -lSDL2

clean:
	rm -f $(OBJ)
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

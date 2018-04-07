##
## EPITECH PROJECT, 2018
## arcade
## File description:
## Makefile
##

SRC	=	Pacman.cpp	\
		Map.cpp		\
		Player.cpp	\
		Ghost.cpp	\
		Timer.cpp

OBJ	=	$(SRC:.cpp=.o)
DEPS	=	$(SRC:.cpp=.d)

HEADER	=	$(addprefix ../../include/game/pacman/,	\
		Pacman.hpp				\
		Player.hpp				\
		Ghost.hpp				\
		Timer.hpp)

NAME	=	../lib_arcade_pacman.so

CXX	=	g++

$(NAME):	CXXFLAGS	=	-shared -std=c++14 -MMD

$(OBJ):	CXXFLAGS	=	-I../../include -fPIC -std=c++14 -MMD

all:	$(NAME)

$(NAME):	$(OBJ) $(HEADER)
	$(CXX) $(OBJ) -o $(NAME) $(CXXFLAGS)

clean:
	@rm -f $(OBJ) $(DEPS)

fclean:	clean
	@rm -f $(NAME)

re:		fclean
	@make all

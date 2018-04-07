##
## EPITECH PROJECT, 2018
## arcade
## File description:
## Makefile
##

SRC	=	Nibbler.cpp

OBJ	=	$(SRC:.cpp=.o)

HEADER	=	../../include/game/Nibbler.hpp

NAME	=	../lib_arcade_nibbler.so

CXX	=	g++

$(NAME):	CXXFLAGS	=	-shared -std=c++14

$(OBJ):	CXXFLAGS	=	-I../../include/ -fPIC -std=c++14

all:	$(NAME)

$(NAME):	$(OBJ) $(HEADER)
	$(CXX) $(OBJ) -o $(NAME) $(CXXFLAGS)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:		fclean all
##
## EPITECH PROJECT, 2018
## arcade
## File description:
## Makefile
##

SRC	=	ASfml.cpp

OBJ	=	$(SRC:.cpp=.o)

HEADER	=	../../include/lib/ASfml.hpp	\
			../../include/Graphic.hpp

NAME	=	../lib_arcade_sfml.so

CXX	=	g++

$(NAME):	CXXFLAGS	=	-lsfml-graphics -lsfml-window -lsfml-system -shared -std=c++14

$(OBJ):	CXXFLAGS	=	-I../../include/ -fPIC -std=c++14

all:	$(NAME)

$(NAME):	$(OBJ) $(HEADER)
	$(CXX) $(OBJ) -o $(NAME) $(CXXFLAGS)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:		fclean all
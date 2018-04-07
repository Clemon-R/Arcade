##
## EPITECH PROJECT, 2018
## arcade
## File description:
## Makefile
##

SRC	=	ACurses.cpp

OBJ	=	$(SRC:.cpp=.o)

HEADER	=	../../include/lib/ACurses.hpp	\
			../../include/Graphic.hpp

NAME	=	../lib_arcade_ncurses.so

CXX	=	g++

$(NAME):	CXXFLAGS	=	-lcurses -shared -std=c++14

$(OBJ):	CXXFLAGS	=	-I../../include/ -fPIC -std=c++14

all:	$(NAME)

$(NAME):	$(OBJ) $(HEADER)
	$(CXX) $(OBJ) -o $(NAME) $(CXXFLAGS)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:		fclean all
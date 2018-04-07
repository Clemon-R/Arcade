##
## EPITECH PROJECT, 2018
## arcade
## File description:
## Makefile
##

SRC	=	ASdl.cpp

OBJ	=	$(SRC:.cpp=.o)

HEADER	=	../../include/lib/ASdl.hpp	\
			../../include/Graphic.hpp

NAME	=	../lib_arcade_sdl2.so

CXX	=	g++

$(NAME):	CXXFLAGS	=	-shared -std=c++14 -lSDL2 -lSDL2main -lSDL2_ttf $(sdl2-config --libs)

$(OBJ):	CXXFLAGS	=	-I../../include/ -fPIC -std=c++14 $(sdl2-config --cflags)

all:	$(NAME)

$(NAME):	$(OBJ) $(HEADER)
	$(CXX) $(OBJ) -o $(NAME) $(CXXFLAGS)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:		fclean all
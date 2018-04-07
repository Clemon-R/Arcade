##
## EPITECH PROJECT, 2018
## arcade
## File description:
## Makefile
##

SRC_NO_MAIN	=	$(addprefix src/,	\
		launcher/Launcher.cpp	\
		)	\
		src/Exception.cpp

SRC_TESTS	=	$(addprefix tests/,	\
				ut_libs.cpp)

SRC	=	$(SRC_NO_MAIN)	\
		src/main.cpp

HEADER	=	$(addprefix include/,	\
			Graphic.hpp	\
			Launcher.hpp	\
			Exception.hpp	\
			)

OBJ_TESTS	=	$(SRC_TESTS:.cpp=.o)

OBJ_NO_MAIN	=	$(SRC_NO_MAIN:.cpp=.o)

OBJ	=	$(SRC:.cpp=.o)

NAME	=	arcade

CXX	=	g++

CXXFLAGS	=	-Iinclude -ldl -std=c++14

PATH_ACURSES	=	lib/acurses/

PATH_ASFML	=	lib/asfml/

PATH_ASDL	=	lib/asdl/

PATH_CENTIPEDE	=	games/pacman/

PATH_NIBBLER	=	games/nibbler/

all:	games graphicals core

core:	$(NAME)

graphicals:
	@make -C $(PATH_ACURSES)
	@make -C $(PATH_ASFML)
	@make -C $(PATH_ASDL)

games:
	@make -C $(PATH_CENTIPEDE)
	@make -C $(PATH_NIBBLER)

$(NAME):	$(OBJ) $(HEADER)
	$(CXX) $(OBJ) -o $(NAME) $(CXXFLAGS)

clean:
	@make clean -C $(PATH_ACURSES)
	@make clean -C $(PATH_ASFML)
	@make clean -C $(PATH_CENTIPEDE)
	@make clean -C $(PATH_NIBBLER)
	@make clean -C $(PATH_ASDL)
	rm -f $(OBJ)
	rm -f $(OBJ_TESTS)

fclean:	clean
	@make fclean -C $(PATH_ACURSES)
	@make fclean -C $(PATH_ASFML)
	@make fclean -C $(PATH_CENTIPEDE)
	@make fclean -C $(PATH_NIBBLER)
	@make fclean -C $(PATH_ASDL)
	rm -f $(NAME)

re:		fclean
	make all

tests_run:	$(OBJ_NO_MAIN) $(OBJ_TESTS)
	$(CXX) $(OBJ_NO_MAIN) $(OBJ_TESTS) -o tests_unit $(CXXFLAGS) --coverage -lcriterion
	./tests_unit


.PHONY:	games graphicals core

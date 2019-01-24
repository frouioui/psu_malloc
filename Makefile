##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile for compilation
##

## ------------- UNIT TESTS ------------- ##
CC	=	gcc -fPIC $(INCLUDE) -g3

UT_DIR	=	./tests/

UT_SRC	=

UT	=	units

## ------------- SHARED LIB ------------- ##
LIB_DIR	= 	./src/

LIB_SRC	= 	$(LIB_DIR)lists.c	\
			$(LIB_DIR)malloc.c	\
			$(LIB_DIR)node.c	\
			$(LIB_DIR)page.c	\

LIB_NAME	=	libmy_malloc.so

LIB_FLAG	=

## ---------------- SRC ----------------- ##

SRC_DIR	= ./src/

SRC	=	$(SRC_DIR)lists.c	\
		$(SRC_DIR)malloc.c	\
		$(SRC_DIR)node.c	\
		$(SRC_DIR)page.c	\

MAIN	=	$(SRC_DIR)main.c

## ---------------- FLAGS ----------------- ##
HEADER	=	-L. -lmy_malloc.so

INCLUDE	=	-I./include/

CFLAGS	=	-W -Wall -Wextra -Werror -pedantic $(HEADER)

LDFLAGS	=	-lcriterion -lgcov -coverage

OBJ	=	$(SRC:.c=.o) $(MAIN:.c=.o)

LIB_OBJ	=	$(LIB_SRC:.c=.o) $(LIB_FLAG)

NAME	=	exec

all:	$(NAME)

$(NAME): lib

lib: $(LIB_OBJ)
	$(CC) -fPIC -shared -o $(LIB_NAME) $(LIB_OBJ)

gdb:
	gcc -o $(NAME) $(SRC) $(MAIN) -g3 $(INCLUDE)

tests_run:
	gcc -o $(UT) $(UT_SRC) $(SRC) $(CFLAGS) $(LDFLAGS)
	./$(UT)

clean:
	rm -f $(OBJ) *.gc*
	rm -f $(LIB_DIR)*.o
	rm -f ./include/*.gch

fclean: 	clean
	rm -f $(NAME) $(UT) a.out *.so

re: 	fclean all

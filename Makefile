##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile for compilation
##

## ------------- UNIT TESTS ------------- ##
CC	=	gcc

UT_DIR	=	./tests/

UT_SRC	=

UT	=	units

## ------------- SHARED LIB ------------- ##
LIB_SRC	= lib.c

LIB_NAME	=	libmy.so

LIB_FLAG	=

## ---------------- SRC ----------------- ##

SRC_DIR	= ./src/

SRC	=

MAIN	= main.c

## ---------------- FLAGS ----------------- ##
HEADER	=	-L. -lmy.so

INCLUDE	=	-I./include/

CFLAGS	=	-W -Wall -Wextra -pedantic $(HEADER)

LDFLAGS	=	-lcriterion -lgcov -coverage

OBJ	=	$(SRC:.c=.o) $(MAIN:.c=.o)

LIB_OBJ	=	$(LIB_SRC:.c=.o) $(LIB_FLAG)

NAME	=	exec

all:	$(NAME)

$(NAME): $(OBJ)
	# export LD_LIBRARY_PATH=$PWD
	$(CC) -o $(NAME) $(OBJ) -ldl

lib: $(LIB_OBJ)
	$(CC) -fPIC -shared -o $(LIB_NAME) $(LIB_OBJ)

gdb:
	$(CC) -o $(NAME) $(SRC) $(MAIN) -g3 -ldl

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

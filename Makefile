##
## EPITECH PROJECT, 2019
## [C++ Pool] rush3
## File description:
## Makefile of the whole project
##

LIB_NAME = libmy.so

BINARY_NAME = exec

CC	=	gcc -g3

PATH_SRC = .

SRC = $(PATH_SRC)/main.c

PATH_LIB = ./src

LIB_SRC =	$(PATH_LIB)/source.c

CFLAGS	=	-W -Wextra

LIB_OBJS	=	$(LIB_SRC:.c=.o)

OBJS = $(SRC:.c=.o)

all: $(BINARY_NAME)

$(BINARY_NAME):
	$(CC) $(SRC) -o $(BINARY_NAME) -L. -lmy -ldl

lib: $(LIB_OBJS)
	$(CC) -fPIC -Wall -Wextra $(LIB_SRC) -shared -o $(LIB_NAME)

clean:
	rm -f $(OBJS) *.gc*

fclean: clean
	rm -f $(BINARY_NAME)

re: fclean all
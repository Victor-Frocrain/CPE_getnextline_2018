##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile
##

SRC	=	../get_next_line.c	\
		test_getnextline.c

OBJ	=	$(SRC:%.c=%.o)

CFLAGS	=	-Wshadow -I ../

NAME	=	unit_tests

CC	=	gcc

all:	$(NAME)

$(NAME):	$(OBJ)
		$(CC) -o $(NAME) $(OBJ) --coverage -lcriterion

clean:
	rm -f $(OBJ)
	rm -f *.gcno *.gcda

fclean:	clean
	rm -f $(NAME)

re:	fclean all

##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## make build
##

SRC	=	*.c\
		lib/my/*.c\

NAME	=	navy

ERROR = -W -Wall -Wextra

all:
	gcc -o $(NAME) $(SRC) $(ERROR) -lm
clean:
	rm -f $(CRITO) $(CRITA) unit-tests

fclean:
	rm -f $(NAME)

re:	fclean all

tests_run:
	gcc -o unit-tests ./lib/my/*.c ./tests/*.c $(SRC) -lcriterion --coverage
	./unit-tests

CC = cc
CFLAGS = -Werror -Wextra -Wall
NAME = 9nbola
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
INCLUDE = $(wildcard *.h)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

%.c: %.o $(INCLUDE)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

.PHONY: clean

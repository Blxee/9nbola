CC = cc
CFLAGS = -Werror -Wextra -Wall
LDFLAGS = -lncurses
NAME = 9nbola
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
INCLUDE = $(wildcard *.h)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(LDFLAGS)

run: $(NAME)
	./$(NAME)

install: $(NAME)
	cp $(NAME) $(HOME)/.local/bin/

%.o: %.c $(INCLUDE)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

.PHONY: clean

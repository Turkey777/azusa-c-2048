CC=clang

LIBS=-lncurses

NAME = 2048
TARGET = main
$(NAME): $(TARGET).c
	$(CC) $(LIBS) $^ -o $@

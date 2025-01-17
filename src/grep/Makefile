CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
SRC = s21_grep.c
TARGET = s21_grep
all: $(TARGET)
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)
clean:
	rm -f $(TARGET)
install: all
	cp $(TARGET) /usr/local/bin/
uninstall:
	rm -f /usr/local/bin/$(TARGET)
.PHONY: all clean install uninstall

CC=gcc
LDFKAGS=-Wall -Werror -Wextra -D_GNU_SOURCE

SOURCES1=grep.c

EXECUTABLE1=s21_grep

all: s21_grep

rebuild:
	rm -rf s21_grep
	make

clear:
	rm -rf *.o 

s21_grep:
	$(CC) $(SOURCES1) $(LDFKAGS) -o $(EXECUTABLE1)

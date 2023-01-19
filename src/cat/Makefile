CC=gcc
LDFKAGS=-Wall -Werror -Wextra -D_GNU_SOURCE

SOURCES1=cat.c

EXECUTABLE1=s21_cat

all: s21_cat

rebuild:
	rm -rf s21_cat
	make

clear:
	rm -rf *.o 

s21_cat:
	$(CC) $(SOURCES1) $(LDFKAGS) -o $(EXECUTABLE1)

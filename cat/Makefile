
CC=gcc
CFLAGS=-Wall -Werror -Wextra
EXECUTABLE_1=s21_cat
SOURCES1=s21_cat_flags.c s21_cat.c s21_cat_function.c
OBJECTS=$(SOURCES1:.c=.o)

all: $(SOURCES1) $(EXECUTABLE) s21_cat
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

c.o:
	$(CC) $(CFLAGS) $< -o $@

s21_cat: $(SOURCES1)
	$(CC) $(CFLAGS) $(SOURCES1) -o $(EXECUTABLE_1)

lint:
	cp ../../materials/linters/.clang-format .
	clang-format -n *.c *.h *.txt
	clang-format -i *.c *.h *.txt
	clang-format -n *.c *.h *.txt
	rm -rf .clang-format

clean:
	rm -rf *.o s21_cat
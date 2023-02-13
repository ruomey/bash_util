CC=gcc
CFLAGS=-Wall -Werror -Wextra
EXECUTABLE_1=s21_grep
SOURCES1=s21_grep.c
OBJECTS=$(SOURCES1:.c=.o)

all: $(SOURCES1) $(EXECUTABLE) s21_grep
        
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

c.o:
	$(CC) $(CFLAGS) $< -o $@

s21_grep: $(SOURCES1)
	$(CC) $(CFLAGS) $(SOURCES1) -o $(EXECUTABLE_1)

lint:
	cp ../../materials/linters/.clang-format .
	clang-format -n *.c *.txt
	clang-format -i *.c *.txt
	clang-format -n *.c *.txt
	rm -rf .clang-format

clean:
	rm -rf *.o s21_grep


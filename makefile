# Compiler
CC = gcc

# Compiler flags
CFLAGS = -w -g

# Target executable
TARGET = driver

# Source files
SRCS = lexer.c parser.c driver.c

driver:
	make clean
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)


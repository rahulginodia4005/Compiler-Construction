# Compiler
CC = gcc

# Compiler flags
CFLAGS = -g

# Target executable
TARGET = driver

# Source files
SRCS = lexer.c parser.c driver.c

driver:
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)

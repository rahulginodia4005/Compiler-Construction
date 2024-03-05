# Compiler
CC = gcc

# Target executable
TARGET = driver_exe

# Source files
SRCS = lexer.c parser.c driver.c

# Object files
OBJS = $(SRCS:.c=.o)

driver: $(TARGET)
    ./$(TARGET)

$(TARGET): $(OBJS)
    $(CC) -o $@ $^

lexer.o: lexer.c
    $(CC) -c lexer.c

parser.o: parser.c
    $(CC) -c parser.c

driver.o: driver.c
    $(CC) -c driver.c

clean:
    rm -f *.o
    rm $(TARGET)
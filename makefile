CC = gcc
CFLAGS = -Wall -g

SRCS = driver.c parser.c lexer.c
OBJS = $(SRCS:.c=.o)
TARGET = myprogram

$(TARGET): $(OBJS)
    $(CC) $(CFLAGS) -o $@ $^

%.o: %.c
    $(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean
clean:
    $(RM) $(TARGET) $(OBJS)

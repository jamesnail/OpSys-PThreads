CC = gcc
# compiler

CFLAGS = -g -Wall
# -g = debugging info
# -Wall = turns on warnings

TARGET = threads
# target executable

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

clean:
	$(RM) $(TARGET)
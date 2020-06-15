CC = gcc
CFLAGS = -g -Wall
TARGET = phase

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

clean:
	$(RM) $(TARGET)
	$(RM) *~
	$(RM) -r *.dSYM

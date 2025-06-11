CC = gcc
CFLAGS = -Wall -Wextra -O2
TARGET = newfetch
SRC = newfetch.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)

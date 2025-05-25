# Nome del file eseguibile
TARGET = ball

# File sorgenti
SRC = main.c

# Comando del compilatore
CC = gcc

# Flag per ottenere le opzioni di SDL2
CFLAGS = $(shell sdl2-config --cflags)
LDFLAGS = $(shell sdl2-config --libs)

# Regola principale
all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC) $(CFLAGS) $(LDFLAGS)

# Pulizia dei file compilati
clean:
	rm -f $(TARGET)
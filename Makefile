# Nome del file eseguibile
TARGET = ball

# File sorgenti
SRC = main.c

# Comando del compilatore
CC = gcc

# Flag per SDL2 (hardcoded per MSYS2 64bit)
CFLAGS = -I/mingw64/include/SDL2 -D_REENTRANT
LDFLAGS = -L/mingw64/lib -lmingw32 -lSDL2main -lSDL2 -mwindows

# Regola principale
all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC) $(CFLAGS) $(LDFLAGS)

# Pulizia dei file compilati
clean:
	rm -f $(TARGET)

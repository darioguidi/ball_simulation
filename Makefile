# Nome del file eseguibile
TARGET = ball

# File sorgenti
SRC = main.c

# Comando del compilatore
CC = gcc

# Flag per SDL2 (per MSYS2/MinGW64)
CFLAGS = -I/mingw64/include/SDL2 -D_REENTRANT
LDFLAGS = -L/mingw64/lib -lmingw32 -lSDL2main -lSDL2 -lm -mwindows

# Regola principale
all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET).exe $(SRC) $(LDFLAGS)

# Pulizia dei file compilati
clean:
	del /Q $(TARGET).exe 2>NUL || true

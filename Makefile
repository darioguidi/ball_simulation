# Nome del file eseguibile
TARGET = ball

# File sorgenti
SRC = main.c

# Comando del compilatore
CC = gcc

# Flag per SDL2
CFLAGS =
LDFLAGS =

# Controllo del sistema operativo
ifeq ($(OS),Windows_NT)
    # Windows
    CFLAGS += -I/mingw64/include/SDL2 -D_REENTRANT
    LDFLAGS += -L/mingw64/lib -lmingw32 -lSDL2main -lSDL2 -lm -mwindows
    EXECUTABLE = $(TARGET).exe
    RM = del /Q
else
    # Linux/macOS
    CFLAGS += $(shell sdl2-config --cflags)
    LDFLAGS += $(shell sdl2-config --libs) -lm
    EXECUTABLE = $(TARGET)
    RM = rm -f
endif

# Regola principale
all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(SRC) $(LDFLAGS)

# Pulizia dei file compilati
clean:
	$(RM) $(EXECUTABLE)


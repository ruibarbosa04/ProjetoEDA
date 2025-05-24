# Compilador
CC = gcc

# Flags de compilação
CFLAGS = -Wall -Wextra -g

# Arquivos de código-fonte e headers
SOURCES = $(wildcard *.c)
HEADERS = $(wildcard *.h)

# Objetos correspondentes
OBJECTS = $(SOURCES:.c=.o)

# Nome do executável e da biblioteca
TARGET = programa
LIB_NAME = funcoesLib.a

# Objetos da biblioteca (ajuste esses nomes se mudar os arquivos)
LIB_OBJECTS = funcoesListas.o funcoesGrafos.o funcoes.o

# Regra principal
all: $(LIB_NAME) $(TARGET)

# Regra para o executável (linka tudo)
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

# Regra para criar a biblioteca estática
$(LIB_NAME): $(LIB_OBJECTS)
	ar rcs $(LIB_NAME) $(LIB_OBJECTS)

# Regra para compilar .c em .o (inclui headers automaticamente)
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Limpar os arquivos gerados
clean:
	rm -f $(OBJECTS) $(TARGET) $(LIB_NAME)

# Alvos que não são arquivos reais
.PHONY: all clean

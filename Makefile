# Makefile para o projeto ca-palavras

# Compilador e flags
CC = gcc
CFLAGS = -Wall -g

# Diretórios e arquivos
SRC = trie.c avl.c jogo.c main.c
HEADERS = trie.h avl.h
OBJECTS = $(SRC:.c=.o)
TARGET = ca-palavras

default: $(TARGET)

# Regra para compilar o binário principal
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

# Regra para compilar os arquivos fonte
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c -o $@ $<

# Regra para limpeza
clean:
	rm -f $(OBJECTS) $(TARGET)

# Regra para rodar o programa
run: $(TARGET)
	./$(TARGET)

.PHONY: default clean run
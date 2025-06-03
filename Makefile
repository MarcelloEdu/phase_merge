# Nome do executável final
EXEC = programa

# Lista de arquivos-fonte
SRC = main.c run.c utils.c merge.c
OBJ = $(SRC:.c=.o)

# Flags de compilação
CFLAGS = -Wall -Wextra -Werror

# Compilador
CC = gcc

# Alvo padrão
all: $(EXEC)

# Linkagem final
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Regra genérica para compilar .c em .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpeza dos arquivos gerados
clean:
	rm -f $(EXEC) *.o run*.txt saida.txt

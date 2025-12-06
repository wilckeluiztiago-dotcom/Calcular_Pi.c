CC = gcc
CFLAGS = -Wall -Wextra -O3 -Iinclude
LDFLAGS = -lm

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Lista de arquivos fonte
SRCS = $(wildcard $(SRC_DIR)/*.c)
# Lista de arquivos objeto
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Nome do executável
TARGET = $(BIN_DIR)/pi_calc

# Regra padrão
all: directories $(TARGET)

# Criação do executável
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# Compilação dos objetos
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Cria diretórios necessários
directories:
	mkdir -p $(OBJ_DIR)
	mkdir -p $(BIN_DIR)

# Limpeza
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Regra para rodar
run: all
	./$(TARGET)

.PHONY: all clean run directories

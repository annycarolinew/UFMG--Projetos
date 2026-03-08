CC = g++
CFLAGS = -std=c++11 -Wall -Wextra -Wpedantic -Wformat-security -Wconversion -Werror -Iinclude

# Caminhos
BIN_DIR = bin
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj

# Listas de arquivos
ARQ_SCRS = $(wildcard $(SRC_DIR)/*.cpp)
ARQ_INCS = $(wildcard $(INC_DIR)/*.hpp)
ARQ_OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(ARQ_SCRS))

# Executável
TARGET = $(BIN_DIR)/tp3.out

all: $(TARGET) $(TEST_DIR)

# Compilando
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(ARQ_INCS) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -I$(INC_DIR) -o $@

# Linkando
$(TARGET): $(ARQ_OBJS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

# Criar diretórios
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Limpar
clean:
	rm -rf $(OBJ_DIR)/*.o $(TARGET)
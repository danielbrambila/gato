# Nombre del ejecutable
TARGET = tres_en_raya

# Compilador y banderas
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

# Directorios
SRC_DIR = .
OBJ_DIR = obj
BIN_DIR = bin

# Archivos fuente y objetos
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# Bibliotecas SDL2
SDL2_LIBS = `sdl2-config --cflags --libs`

# Reglas
all: $(BIN_DIR)/$(TARGET)

$(BIN_DIR)/$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(SDL2_LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $< $(SDL2_LIBS)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean
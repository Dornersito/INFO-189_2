# Compilador y opciones
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

# Directorios
SRC_DIR = .
OBJ_DIR = obj
EXTERNAL_DIR = funciones_externas

# Archivos de origen y destino
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))
EXTERNAL_SRCS = $(wildcard $(EXTERNAL_DIR)/*.cpp)
EXTERNAL_TARGETS = $(patsubst $(EXTERNAL_DIR)/%.cpp,$(EXTERNAL_DIR)/%,$(EXTERNAL_SRCS))

# Nombre del ejecutable
TARGET = ej

all: $(TARGET) $(EXTERNAL_TARGETS)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(EXTERNAL_DIR)/%: $(EXTERNAL_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

.PHONY: clean

clean:
	rm -f $(TARGET) $(OBJS) $(EXTERNAL_TARGETS)

# Nombre del programa
TARGET = ej

# Compilador y opciones de compilación
CXX = g++
CXXFLAGS = -std=c++11 -Wall

# Directorios de búsqueda de archivos fuente y objetos
SRCDIR = .
OBJDIR = obj

# Lista de archivos fuente y objetos generados
SOURCES := $(wildcard $(SRCDIR)/*.cpp)
OBJECTS := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SOURCES))

# Regla para compilar los objetos
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Regla principal para construir el ejecutable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Regla para limpiar los archivos generados
clean:
	rm -rf $(OBJDIR) $(TARGET)

.PHONY: clean

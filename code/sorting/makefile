# Variables de compilación
CXX = g++
CXXFLAGS = -std=c++11 -Wall -O2
TARGET = sorting_test

# Archivos fuente (Asegúrate de que los nombres coincidan con tus archivos)
SRCS = sorting.cpp \
       algorithms/mergesort.cpp \
       algorithms/quicksort.cpp \
       algorithms/sort.cpp

# Regla principal
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

# Limpieza
clean:
	rm -f $(TARGET)

# Ejecutar el generador de arreglos
setup:
	python3 scripts/array_generator.py

# Ejemplo de prueba para sorting
test: all
	./$(TARGET) 1000 aleatorio data/array_input/1000_aleatorio_a.txt
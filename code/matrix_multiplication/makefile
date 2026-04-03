# Variables de compilación
CXX = g++
CXXFLAGS = -std=c++11 -Wall -O2
TARGET = matrix_test

# Archivos fuente
SRCS = matrix_multiplication.cpp \
       algorithms/naive.cpp \
       algorithms/strassen.cpp

# Regla principal: Compila el ejecutable
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

# Regla para limpiar archivos temporales y el ejecutable
clean:
	rm -f $(TARGET)

# Regla para ejecutar el generador de matrices antes de probar
setup:
	python3 scripts/matrix_generator.py

# Ejemplo de como correr una prueba rápida
test: all
	./$(TARGET) 16 naive data/matrix_input/16_densa_D0_a_1.txt data/matrix_input/16_densa_D0_a_2.txt
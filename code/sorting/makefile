# Variables de compilación
CXX = g++
CXXFLAGS = -std=c++11 -Wall -O2
TARGET = sorting_test

# Archivos fuente
# Asegúrate de que algorithms/sort.cpp sea el que usa std::sort
SRCS = sorting.cpp \
       algorithms/mergesort.cpp \
       algorithms/quicksort.cpp \
       algorithms/sort.cpp

# Parámetros del experimento
SIZES = 10000000 100000 1000 10 
TYPES = aleatorio ascendente descendente
DOMAINS = D1 D7
SAMPLES = a b c
ALGORITHMS = mergesort quicksort sort

# Regla principal
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

# Limpieza
clean:
	rm -f $(TARGET)

# Ejecutar el generador de arreglos
setup:
	python3 scripts/matrix_generator.py

# Prueba rápida (Corregida con el dominio D1)
test: all
	@mkdir -p measurements/sorting
	./$(TARGET) 1000 sort_stl data/array_input/1000_aleatorio_D1_a.txt

run_all: all
	@for n in $(SIZES); do \
		for t in $(TYPES); do \
			for d in $(DOMAINS); do \
				for m in $(SAMPLES); do \
					for alg in $(ALGORITHMS); do \
						echo "Procesando: n=$$n, tipo=$$t, dom=$$d, muestra=$$m, alg=$$alg"; \
						./$(TARGET) $$n $$alg data/array_input/$${n}_$${t}_$${d}_$${m}.txt; \
					done; \
				done; \
			done; \
		done; \
	done
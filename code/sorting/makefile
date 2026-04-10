# Variables de compilación
CXX = g++
CXXFLAGS = -std=c++11 -Wall -O2
TARGET = sorting_test

# Archivos fuente
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
	rm -rf data/array_output/*
	rm -rf data/measurements/*
	rm -rf data/plots/*

# Ejecutar el generador de arreglos
inputs:
	python3 scripts/array_generator.py

# Prueba rapida
test: all
	@mkdir -p data/measurements
	./$(TARGET) 1000 sort data/array_input/1000_aleatorio_D1_a.txt

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

graficos:
	@echo "Generando gráficos..."
	@python3 scripts/plot_generator.py
	@echo "Gráficos generados en data/plots/"
# Variables de compilación
CXX = g++
CXXFLAGS = -std=c++11 -Wall -O2
TARGET = matrix_test

# Archivos fuente
SRCS = matrix_multiplication.cpp \
       algorithms/naive.cpp \
       algorithms/strassen.cpp

# Las variables deben de ser iguales a la del scrip para general los input si no, no va a funcinar
SIZES = 16 64 256 1024
TYPES = dispersa diagonal densa
DOMAINS = D0 D10
SAMPLES = a b c

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)
	rm -rf data/matrix_output/*
	rm -rf data/measurements/*
	rm -rf data/plots/*

inputs:
	@echo "Generando matrices de entrada..."
	@python3 scripts/matrix_generator.py
	@echo "Matrices generadas en data/matrix_input/"

test: all
	@mkdir -p data/measurements
	./$(TARGET) 16 naive dispersa D0 a data/matrix_input/16_dispersa_D0_a_1.txt data/matrix_input/16_dispersa_D0_a_2.txt

# Ejecuta todas las combinaciones generadas
run_all: all
	@mkdir -p data/measurements data/matrix_output
	@for n in $(SIZES); do \
		for t in $(TYPES); do \
			for d in $(DOMAINS); do \
				for m in $(SAMPLES); do \
					echo "Procesando: n=$$n, tipo=$$t, dominio=$$d, muestra=$$m"; \
					./$(TARGET) $$n naive $$t $$d $$m data/matrix_input/$${n}_$${t}_$${d}_$${m}_1.txt data/matrix_input/$${n}_$${t}_$${d}_$${m}_2.txt; \
					./$(TARGET) $$n strassen $$t $$d $$m data/matrix_input/$${n}_$${t}_$${d}_$${m}_1.txt data/matrix_input/$${n}_$${t}_$${d}_$${m}_2.txt; \
				done \
			done \
		done \
	done
	@echo "--- Todas las mediciones han finalizado ---"

graficos:
	@echo "Generando gráficos..."
	@python3 scripts/plot_generator.py
	@echo "Gráficos generados en data/plots/"
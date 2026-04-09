# Variables de compilación
CXX = g++
CXXFLAGS = -std=c++11 -Wall -O2
TARGET = matrix_test

# Archivos fuente
SRCS = matrix_multiplication.cpp \
       algorithms/naive.cpp \
       algorithms/strassen.cpp

# Variables que coinciden con tu script de Python
SIZES = 16 64 256 1024
TYPES = dispersa diagonal densa
DOMAINS = D0 D10
SAMPLES = a b c

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)

Setup:
	@echo "Generando matrices de entrada..."
	@python3 scripts/matrix_generator.py
	@echo "Matrices generadas en data/matrix_input/"

# Ejecuta todas las combinaciones generadas por tu script
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
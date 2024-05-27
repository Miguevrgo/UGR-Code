# Directorios
GEN_DIR = Generador
ALG_DIR = Algoritmo
INST_DIR = Instancias
OUT_DIR = Salidas
GRAPH_DIR = Graficos

# Archivos fuente
GEN_SOURCES = $(wildcard $(GEN_DIR)/*.cpp)
ALG_SOURCES = $(wildcard $(ALG_DIR)/*.cpp)

# Ejecutables
CREA_PUNTOS_EXEC = $(GEN_DIR)/creacion_puntos
CREA_MATRICES_EXEC = $(GEN_DIR)/creacion_matrices
ALG_EXEC = $(ALG_DIR)/viajante_bb

# Compilador y banderas
CXX = g++
CXXFLAGS = -std=c++20 -O3

# Variables de cantidad de archivos
TAM = 14
NUM = 1

all: generate run graph

# Regla para compilar CreacionPuntos
$(CREA_PUNTOS_EXEC): $(GEN_DIR)/CreacionPuntos.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

# Regla para compilar CreacionMatrices
$(CREA_MATRICES_EXEC): $(GEN_DIR)/CreacionMatrices.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

# Regla para compilar ViajanteBB
$(ALG_EXEC): $(ALG_DIR)/ViajanteBB.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

# Regla para ejecutar el generador y crear instancias
generate: $(CREA_PUNTOS_EXEC) $(CREA_MATRICES_EXEC)
	@echo "Generando instancias..."
	@mkdir -p $(INST_DIR)
	@for size in $(shell seq 3 $(TAM)); do \
	    for inst in $(shell seq 1 $(NUM)); do \
	        puntos_file=$(INST_DIR)/puntos_$${size}_$${inst}.txt; \
	        matriz_file=$(INST_DIR)/matriz_$${size}_$${inst}.txt; \
	        $(CREA_PUNTOS_EXEC) $${size} $${puntos_file} 50; \
	        $(CREA_MATRICES_EXEC) $${puntos_file} $${matriz_file}; \
	    done; \
	done
	@echo "Instancias generadas en $(INST_DIR)"

# Regla para ejecutar el algoritmo con las instancias
run: $(ALG_EXEC)
	@echo "Ejecutando algoritmo..."
	@mkdir -p $(OUT_DIR)
	@for size in $(shell seq 3 $(TAM)); do \
	    for inst in $(shell seq 1 $(NUM)); do \
			for cota in $(shell seq 1 3); do \
				mkdir -p $(OUT_DIR)/Cota$${cota}; \
				matriz_file=$(INST_DIR)/matriz_$${size}_$${inst}.txt; \
				resultado_file=$(OUT_DIR)/Cota$${cota}/resultado_$${size}_$${inst}.txt; \
				$(ALG_EXEC) $${matriz_file} 1 $${cota} > $${resultado_file}; \
			done; \
	    done; \
	done
	@echo "Resultados guardados en $(OUT_DIR)"

# Regla para ejecutar los tiempos
time: $(ALG_EXEC)
	@echo "Ejecutando algoritmo..."
	@mkdir -p $(OUT_DIR)
	@for cota in $(shell seq 1 3); do \
		rm -f $(OUT_DIR)/Cota$${cota}_tiempos.txt; \
		for size in $(shell seq 3 $(TAM)); do \
			matriz_file=$(INST_DIR)/matriz_$${size}_1.txt; \
			resultado_file=$(OUT_DIR)/Cota$${cota}/resultado_$${size}_1.txt; \
			$(ALG_EXEC) $${matriz_file} 1 $${cota} 2 >> Salidas/Cota$${cota}_tiempos.txt; \
		done; \
		./eficiencia.sh Salidas/Cota$${cota}_tiempos.txt Salidas/Cota$${cota}_grafico_tiempos.png; \
	done
	@echo "Resultados guardados en $(OUT_DIR)"

# Regla para graficar los resultados y la comparación de nodos desarrollados
graph:
	@echo "Generando gráficos..."
	@mkdir -p $(GRAPH_DIR)
	@for size in $(shell seq 3 $(TAM)); do \
	    for inst in $(shell seq 1 $(NUM)); do \
	        puntos_file=$(INST_DIR)/puntos_$${size}_$${inst}.txt; \
	        for cota in $(shell seq 1 3); do \
	            resultado_file=$(OUT_DIR)/Cota$${cota}/resultado_$${size}_$${inst}.txt; \
	            grafico_file=$(GRAPH_DIR)/grafico_$${size}_$${inst}_cota$${cota}.png; \
	            ./graph.sh $${puntos_file} $${resultado_file} $${grafico_file}; \
	        done; \
	    done; \
	    comparacion_file=$(GRAPH_DIR)/comparacion_nodos_$${size}.png; \
	    python3 comparar_nodos.py $(OUT_DIR) $${size} $${comparacion_file}; \
	done
	@echo "Gráficos generados en $(GRAPH_DIR)"

compile: $(CREA_PUNTOS_EXEC) $(CREA_MATRICES_EXEC) $(ALG_EXEC)
	@echo "Todos los archivos han sido compilados."

clean:
	@echo "Limpiando archivos compilados y resultados..."
	@rm -f $(CREA_PUNTOS_EXEC) $(CREA_MATRICES_EXEC) $(ALG_EXEC)
	@rm -rf $(INST_DIR)/*
	@rm -rf $(OUT_DIR)/*
	@rm -rf $(GRAPH_DIR)/*

.PHONY: all generate run graph clean

import matplotlib.pyplot as plt
import numpy as np
import os

def cargar_datos(directorio, algoritmo):
    """
    Extrae promedios de tiempo y memoria de los archivos del algoritmo.
    """
    tiempos_medios = []
    memorias_medias = []
    tamanos = []
    
    # Listar archivos en data/measurements
    for filename in os.listdir(directorio):
        # Buscamos archivos como 'naive_1024_metricas.txt'
        if filename.startswith(algoritmo) and filename.endswith("_metricas.txt"):
            try:
                # Extraer el n del nombre: algoritmo_N_metricas.txt
                parts = filename.split("_")
                n_val = int(parts[1]) 
                
                with open(os.path.join(directorio, filename), 'r') as f:
                    lineas = f.readlines()
                    if lineas:
                        # Cada línea tiene: [tiempo] [memoria]
                        datos_fila = [linea.strip().split() for linea in lineas]
                        tiempos = [float(d[0]) for d in datos_fila]
                        memorias = [float(d[1]) for d in datos_fila]
                        
                        tiempos_medios.append(np.mean(tiempos))
                        memorias_medias.append(np.mean(memorias))
                        tamanos.append(n_val)
            except (ValueError, IndexError):
                continue

    # Ordenar para que las líneas del gráfico no salgan zigzagueantes
    if not tamanos:
        return [], [], []
    
    sorted_data = sorted(zip(tamanos, tiempos_medios, memorias_medias))
    return zip(*sorted_data)

def generar_graficos():
    # Rutas actualizadas a tu estructura de carpetas
    dir_mediciones = "data/measurements"
    dir_salida = "data/plots"
    
    if not os.path.exists(dir_salida):
        os.makedirs(dir_salida)

    algoritmos = ["naive", "strassen"]
    colores = {'naive': 'blue', 'strassen': 'red'}
    
    # --- GRAFICO TIEMPOS ---
    plt.figure(figsize=(10, 6))
    for algo in algoritmos:
        n, t, m = cargar_datos(dir_mediciones, algo)
        if n:
            plt.plot(n, t, marker='o', label=f'Algoritmo: {algo}', color=colores[algo])

    plt.title("Comparación de Tiempos: Multiplicación de Matrices")
    plt.xlabel("Dimensión de la Matriz (n)")
    plt.ylabel("Tiempo (segundos)")
    plt.xscale('log', base=2) 
    plt.yscale('log')
    plt.grid(True, which="both", ls="-", alpha=0.5)
    plt.legend()
    plt.savefig(os.path.join(dir_salida, "tiempo_matrices.png"))

    # --- GRAFICO MEMORIA ---
    plt.figure(figsize=(10, 6))
    for algo in algoritmos:
        n, t, m = cargar_datos(dir_mediciones, algo)
        if n:
            plt.plot(n, m, marker='s', ls='--', label=f'Memoria: {algo}', color=colores[algo])

    plt.title("Consumo de Memoria: VmPeak")
    plt.xlabel("Dimensión de la Matriz (n)")
    plt.ylabel("Memoria (KB)")
    plt.xscale('log', base=2)
    plt.grid(True, which="both", ls="-", alpha=0.5)
    plt.legend()
    plt.savefig(os.path.join(dir_salida, "memoria_matrices.png"))
    
    print(f"Gráficos guardados en la carpeta: {dir_salida}")

if __name__ == "__main__":
    generar_graficos()
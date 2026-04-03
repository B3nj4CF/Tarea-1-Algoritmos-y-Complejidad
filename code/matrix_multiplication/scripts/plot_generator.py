import matplotlib.pyplot as plt
import numpy as np
import os

def cargar_datos(directorio, algoritmo):
    """
    Busca archivos que empiecen con el nombre del algoritmo y extrae los tiempos.
    """
    tiempos = []
    tamanos = []
    
    # Listar archivos en la carpeta de mediciones
    for filename in os.listdir(directorio):
        if filename.startswith(algoritmo) and filename.endswith(".txt"):
            # Extraer el tamaño 'n' del nombre del archivo (ej: merge_n100.txt)
            # Esto depende de cómo nombraste los archivos en sorting.cpp
            parts = filename.replace(".txt", "").split("_")
            try:
                # Intentamos obtener el valor numérico de n
                n_val = int(parts[-1].replace("n", "")) 
                
                # Leer el tiempo dentro del archivo
                with open(os.path.join(directorio, filename), 'r') as f:
                    lineas = f.readlines()
                    if lineas:
                        # Promedio de las mediciones en el archivo
                        promedio = np.mean([float(x.strip()) for x in lineas])
                        tiempos.append(promedio)
                        tamanos.append(n_val)
            except ValueError:
                continue

    # Ordenar por tamaño de n para que el gráfico no salga cruzado
    sorted_data = sorted(zip(tamanos, tiempos))
    if not sorted_data:
        return [], []
    return zip(*sorted_data)

def generar_grafico():
    # Rutas según el enunciado
    dir_mediciones = "measurements/sorting"
    dir_salida = "plots/sorting"
    
    # Crear carpeta de plots si no existe
    if not os.path.exists(dir_salida):
        os.makedirs(dir_salida)

    plt.figure(figsize=(10, 6))

    # Lista de algoritmos a graficar
    algoritmos = ["merge", "quick", "std_sort"]
    colores = {'merge': 'blue', 'quick': 'green', 'std_sort': 'red'}

    for algo in algoritmos:
        n, t = cargar_datos(dir_mediciones, algo)
        if n:
            plt.plot(n, t, marker='o', label=f'Algoritmo: {algo}', color=colores[algo])

    plt.title("Comparación de Tiempos: Ordenamiento")
    plt.xlabel("Tamaño del Arreglo (n)")
    plt.ylabel("Tiempo (segundos)")
    plt.xscale('log') # Escala logarítmica recomendada por los tamaños 10^1 a 10^7
    plt.grid(True, which="both", ls="-", alpha=0.5)
    plt.legend()

    # Guardar en formato PNG como pide la tarea
    path_png = os.path.join(dir_salida, "comparativa_sorting.png")
    plt.savefig(path_png)
    print(f"Gráfico guardado en: {path_png}")

if __name__ == "__main__":
    generar_grafico()
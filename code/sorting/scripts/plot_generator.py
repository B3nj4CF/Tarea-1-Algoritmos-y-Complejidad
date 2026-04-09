import matplotlib.pyplot as plt
import pandas as pd
import glob
import os

def generar_graficos():
    # Configuracion de rutas
    data_path = "data/measurements/"
    output_path = "data/plots/"
    
    if not os.path.exists(output_path):
        os.makedirs(output_path)

    # Listas para guardar los promedios
    resultados = []

    # Buscamos todos los archivos .txt en la carpeta de mediciones
    archivos = glob.glob(f"{data_path}*.txt")

    for archivo in archivos:
        # Extraer info del nombre del archivo: algoritmo_N_metricas.txt, n es la dimension del arrey
        nombre_base = os.path.basename(archivo)
        partes = nombre_base.split('_')
        
        algoritmo = partes[0]
        try:
            dimension = int(partes[1])
        except ValueError:
            continue # Saltar si el formato no coincide

        # Leer datos (Tiempo, Memoria)
        df = pd.read_csv(archivo, sep=' ', names=['tiempo', 'memoria'], header=None)
        
        # Promediar las muestras para ese N
        tiempo_promedio = df['tiempo'].mean()
        memoria_promedio = df['memoria'].mean() # Ya está en KB

        resultados.append({
            'Algoritmo': algoritmo,
            'N': dimension,
            'Tiempo': tiempo_promedio,
            'Memoria': memoria_promedio
        })

    # Crear DataFrame principal
    final_df = pd.DataFrame(resultados).sort_values(by='N')

    # --- Grafico de Tiempo ---
    plt.figure(figsize=(10, 6))
    for algo in final_df['Algoritmo'].unique():
        subset = final_df[final_df['Algoritmo'] == algo]
        plt.plot(subset['N'], subset['Tiempo'], marker='o', label=algo)

    plt.xscale('log') # Escala logarítmica porque N crece de 10 en 10
    plt.yscale('log')
    plt.title('Comparación de Tiempo de Ejecución')
    plt.xlabel('Tamaño del arreglo (N)')
    plt.ylabel('Tiempo promedio (segundos)')
    plt.legend()
    plt.grid(True, which="both", ls="-", alpha=0.5)
    plt.savefig(f"{output_path}comparativa_tiempo.png")
    plt.close()

    # --- Grafico de Memoria ---
    plt.figure(figsize=(10, 6))
    for algo in final_df['Algoritmo'].unique():
        subset = final_df[final_df['Algoritmo'] == algo]
        # hay que convertir KB a MB para que sea más legible y dfacil de entender
        plt.plot(subset['N'], subset['Memoria'] / 1024, marker='s', label=algo)

    plt.xscale('log')
    plt.title('Uso Máximo de Memoria RAM (RSS)')
    plt.xlabel('Tamaño del arreglo (N)')
    plt.ylabel('Memoria Promedio (MB)')
    plt.legend()
    plt.grid(True, which="both", ls="-", alpha=0.5)
    plt.savefig(f"{output_path}comparativa_memoria.png")
    plt.close()

    print(f"Gráficos generados exitosamente en la carpeta '{output_path}'")

if __name__ == "__main__":
    generar_graficos()
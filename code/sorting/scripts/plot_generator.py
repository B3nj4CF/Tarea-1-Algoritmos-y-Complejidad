import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import pandas as pd
import glob
import os

def generar_graficos():
    data_path = "data/measurements/"
    output_path = "data/plots/"
    
    if not os.path.exists(output_path):
        os.makedirs(output_path)

    resultados = []
    archivos = glob.glob(f"{data_path}*.txt")

    print(f"DEBUG: Se encontraron {len(archivos)} archivos.")

    for archivo in archivos:
        nombre_base = os.path.basename(archivo)
        # formato, mergesort_10_metricas.txt
        partes = nombre_base.split('_')
        
        try:
            algoritmo = partes[0]
            dimension = int(partes[1])
        except (ValueError, IndexError):
            print(f"DEBUG: Saltando {nombre_base} por formato incompatible.")
            continue

        # Leer datos (Tiempo y Memoria)
        try:
            #  r'\s+' es para manejar cualquier espacio generado por C++
            df = pd.read_csv(archivo, sep=r'\s+', names=['tiempo', 'memoria'], header=None)
            
            if df.empty:
                continue
            
            # Promediar las muestras
            tiempo_prom = df['tiempo'].mean()
            # Si la memoria es 0, usar un valor mínimo para que el gráfico no falle
            memoria_prom = max(df['memoria'].mean(), 0.1) 

            resultados.append({
                'Algoritmo': algoritmo.upper(),
                'N': dimension,
                'Tiempo': tiempo_prom,
                'Memoria': memoria_prom
            })
            print(f"DEBUG: Procesado {algoritmo} N={dimension}")
        except Exception as e:
            print(f"DEBUG: Error en {nombre_base}: {e}")

    if not resultados:
        print("Error: No hay resultados para graficar.")
        return

    final_df = pd.DataFrame(resultados).sort_values(by='N')

    # --- Gráfico de Tiempo ---
    plt.figure(figsize=(10, 6))
    for algo in final_df['Algoritmo'].unique():
        subset = final_df[final_df['Algoritmo'] == algo]
        plt.plot(subset['N'], subset['Tiempo'], marker='o', label=algo)

    plt.xscale('log')
    plt.yscale('log')
    plt.title('Comparación de Tiempo de Ejecución (Ordenamiento)')
    plt.xlabel('Cantidad de elementos (N)')
    plt.ylabel('Segundos (promedio)')
    plt.legend()
    plt.grid(True, which="both", ls="-", alpha=0.3)
    plt.tight_layout()
    plt.savefig(f"{output_path}comparativa_tiempo.png")
    plt.close()

    # --- Gráfico de Memoria ---
    plt.figure(figsize=(10, 6))
    for algo in final_df['Algoritmo'].unique():
        subset = final_df[final_df['Algoritmo'] == algo]
        # Convertimos KB a MB
        plt.plot(subset['N'], subset['Memoria'] / 1024, marker='s', label=algo)

    plt.xscale('log')
    plt.title('Uso de Memoria RAM (RSS)')
    plt.xlabel('Cantidad de elementos (N)')
    plt.ylabel('Megabytes (MB)')
    plt.legend()
    plt.grid(True, which="both", ls="-", alpha=0.3)
    plt.tight_layout()
    plt.savefig(f"{output_path}comparativa_memoria.png")
    plt.close()

    print(f"¡Éxito! Gráficos generados en: {output_path}")

if __name__ == "__main__":
    generar_graficos()
import numpy as np
import os

def generar_arreglo(dimension, tipo, dominio):
    if dominio == "D1":
        valores = np.arange(10)
    elif dominio == "D7":
        valores = np.arange(10**7 + 1)
    else:
        raise ValueError("Dominio no reconocido")
    
    if tipo == "ascendente":
        return np.sort(np.random.choice(valores, dimension, replace=True))
    elif tipo == "descendente":
        return np.sort(np.random.choice(valores, dimension, replace=True))[::-1]
    elif tipo == "aleatorio":
        return np.random.choice(valores, dimension, replace=True)
    else:
        raise ValueError("Tipo de ordenamiento no reconocido")

def guardar_arreglo(nombre_archivo, arreglo):
    folder = "../sorting/data/array_input"
    os.makedirs(folder, exist_ok=True) 
    with open(os.path.join(folder, nombre_archivo), "w") as f:
        f.write(" ".join(map(str, arreglo)))


def generar_archivos():
    N = [10**1, 10**3, 10**5, 10**7] 
    T = ["ascendente", "descendente", "aleatorio"]
    D = ["D1", "D7"]
    M = ["a", "b", "c"]
    
    for dimension in N:
        for t in T:
            for d in D:
                for m in M:
                    nombre_archivo = f"{dimension}_{t}_{d}_{m}.txt"
                    arreglo = generar_arreglo(dimension, t, d)
                    guardar_arreglo(nombre_archivo, arreglo)
                    print(f"Generado: {nombre_archivo}")

if __name__ == "__main__":
    generar_archivos()


#Notas, se ajusto la ruta de la carpeta para guardar loas que areglos ya que no funcionaba la ruta anterior, se cambio a "../sorting/data/array_input" y se agrego os.makedirs para crear la carpeta si no existe.

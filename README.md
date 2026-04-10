# TAREA 1 INF221 2026-1

## Estructura del Repositorio

Este repositorio contiene la documentación, el código fuente y las instrucciones necesarias para la realización de la Tarea 1 de la asignatura *INF221 Algoritmos y Complejidad*.

**Entrega:** archivo `.zip` vía aula.usm.cl

A continuación, se describe la estructura del repositorio:

```bash
├── assignment_statement
├── code
├── report
└── README.md
```

### `assignment_statement`
Contiene el enunciado de la tarea, así como los archivos fuente del enunciado en formato LaTeX (.tex).

### `code`
Contiene la plantilla de los archivos que deberán estar presentes en la entrega de la tarea. En ella, se deben implementar los algoritmos solicitados, los cuales se detallan a continuación:
- `matrix_multiplication`: Algoritmo de Strassen y versión Naive.
- `sorting`: std::sort, merge sort, quick sort.

### `report`
En esta carpeta se encuentra la plantilla en LaTeX para la elaboración del mini-informe correspondiente a la tarea.

***Para obtener información más detallada sobre el contenido de cada carpeta, se recomienda revisar los archivos README ubicados dentro de ellas.***


## Notas Personales
1. Los Makefiles están diseñados para que solo haya que ejecutar comandos precisos: make inputs, make clean, make run_all y make graficos. Lo ideal sería ejecutarlos en ese orden para ambos casos (ordenamiento y multiplicación).
2. Algunos códigos son una combinación de varios encontrados en internet y en la bibliografía. Debido a que para arreglos de 10**7 se hacían pesados, se modificaron cosas para que funcionen; eso mismo fue extrapolado a la multiplicación de matrices.
3. No quedó bien claro cómo se tenía que hacer el mini-informe, así que se pasó la carpeta report a Overleaf en internet y desde ahí se trabajó el Latex, se intentó ser lo más claro posible y mantenerlo dentro de los márgenes.
4. Los inputs se envían vacíos para poder comprimirlos y que se puedan enviar por Aula. 
5. Se modificaron los generadores de los inputs, ya que había errores en la ruta de donde se guardaban.
6. Es necesario tener las librerías usadas para que no haya fallos.
7. Se usó Arch Linux como sistema, así que ojo con eso, por favor, porque puede que en Windows (WSL) no funcione, no lo sé. 
8. Se intentó que el código quedara ordenado y limpio a la vista.
9. Hay un grafico en el informe que tiene un nombre de VMpeak eso era lo que usaba antes para ver la memoria pero luego se cambio por otra forma.
10. Mi Pc exploto... porfa proxima tarea con menor tanano de entradas y mas entendibles.